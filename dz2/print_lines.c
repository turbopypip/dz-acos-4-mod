#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static int parse_positive_int(const char *s, int *out)
{
    char *end = NULL;
    errno = 0;
    long value = strtol(s, &end, 10);
    if (errno != 0 || end == s || *end != '\0' || value < 1 || value > INT_MAX) {
        return -1;
    }
    *out = (int)value;
    return 0;
}

static int write_all(int fd, const char *buf, size_t len)
{
    while (len > 0) {
        ssize_t written = write(fd, buf, len);
        if (written < 0) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }
        buf += written;
        len -= (size_t)written;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        dprintf(STDERR_FILENO, "Usage: %s <file> <start-line> <line-count>\n", argv[0]);
        return 1;
    }

    int start_line = 0;
    int line_count = 0;
    if (parse_positive_int(argv[2], &start_line) != 0 ||
        parse_positive_int(argv[3], &line_count) != 0) {
        dprintf(STDERR_FILENO, "start-line and line-count must be positive integers\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        dprintf(STDERR_FILENO, "open failed: %s\n", strerror(errno));
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) != 0) {
        dprintf(STDERR_FILENO, "fstat failed: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    long page_size = sysconf(_SC_PAGESIZE);
    size_t buf_size = page_size > 0 ? (size_t)page_size : 4096u;
    if (st.st_size > 0 && (off_t)buf_size > st.st_size) {
        buf_size = (size_t)st.st_size;
    }
    if (buf_size == 0) {
        close(fd);
        return 0;
    }

    char *buf = malloc(buf_size);
    if (buf == NULL) {
        close(fd);
        return 1;
    }

    int current_line = 1;
    int printed_lines = 0;
    int should_print = start_line == 1;
    while (printed_lines < line_count) {
        ssize_t got = read(fd, buf, buf_size);
        if (got < 0) {
            if (errno == EINTR) {
                continue;
            }
            dprintf(STDERR_FILENO, "read failed: %s\n", strerror(errno));
            free(buf);
            close(fd);
            return 1;
        }
        if (got == 0) {
            break;
        }

        size_t segment_start = 0;
        for (size_t i = 0; i < (size_t)got && printed_lines < line_count; ++i) {
            if (buf[i] == '\n') {
                if (should_print &&
                    write_all(STDOUT_FILENO, buf + segment_start, i - segment_start + 1) != 0) {
                    free(buf);
                    close(fd);
                    return 1;
                }
                if (should_print) {
                    ++printed_lines;
                }
                ++current_line;
                should_print = current_line >= start_line && printed_lines < line_count;
                segment_start = i + 1;
            }
        }

        if (should_print && segment_start < (size_t)got &&
            write_all(STDOUT_FILENO, buf + segment_start, (size_t)got - segment_start) != 0) {
            free(buf);
            close(fd);
            return 1;
        }
    }

    free(buf);
    close(fd);
    return 0;
}

