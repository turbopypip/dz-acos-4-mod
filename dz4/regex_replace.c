#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Buffer {
    char *data;
    size_t len;
    size_t cap;
} Buffer;

static int reserve(Buffer *buf, size_t extra)
{
    if (extra > (size_t)-1 - buf->len - 1) {
        return -1;
    }
    size_t need = buf->len + extra + 1;
    if (need <= buf->cap) {
        return 0;
    }

    size_t new_cap = buf->cap == 0 ? 64u : buf->cap;
    while (new_cap < need) {
        if (new_cap > (size_t)-1 / 2) {
            new_cap = need;
            break;
        }
        new_cap *= 2;
    }

    char *new_data = realloc(buf->data, new_cap);
    if (new_data == NULL) {
        return -1;
    }
    buf->data = new_data;
    buf->cap = new_cap;
    return 0;
}

static int append_mem(Buffer *buf, const char *s, size_t n)
{
    if (reserve(buf, n) != 0) {
        return -1;
    }
    memcpy(buf->data + buf->len, s, n);
    buf->len += n;
    buf->data[buf->len] = '\0';
    return 0;
}

static int append_str(Buffer *buf, const char *s)
{
    return append_mem(buf, s, strlen(s));
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <regex> <text> <replacement>\n", argv[0]);
        return 1;
    }

    regex_t regex;
    int rc = regcomp(&regex, argv[1], REG_EXTENDED);
    if (rc != 0) {
        char err[256];
        regerror(rc, &regex, err, sizeof(err));
        fprintf(stderr, "regcomp failed: %s\n", err);
        return 1;
    }

    const char *text = argv[2];
    const char *replacement = argv[3];
    const char *cursor = text;
    Buffer out = {0};
    regmatch_t match;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (append_mem(&out, cursor, (size_t)match.rm_so) != 0 ||
            append_str(&out, replacement) != 0) {
            free(out.data);
            regfree(&regex);
            return 1;
        }

        if (match.rm_so == match.rm_eo) {
            if (*cursor == '\0') {
                break;
            }
            if (append_mem(&out, cursor, 1) != 0) {
                free(out.data);
                regfree(&regex);
                return 1;
            }
            cursor += 1;
        } else {
            cursor += match.rm_eo;
        }
    }

    if (append_str(&out, cursor) != 0) {
        free(out.data);
        regfree(&regex);
        return 1;
    }

    puts(out.data == NULL ? "" : out.data);
    free(out.data);
    regfree(&regex);
    return 0;
}

