#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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
    if (argc != 2) {
        dprintf(STDERR_FILENO, "Usage: %s <file>\n", argv[0]);
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

    if (lseek(fd, st.st_size / 2, SEEK_SET) == (off_t)-1) {
        dprintf(STDERR_FILENO, "lseek failed: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    char buf[4096];
    int done = 0;
    while (!done) {
        ssize_t got = read(fd, buf, sizeof(buf));
        if (got < 0) {
            if (errno == EINTR) {
                continue;
            }
            dprintf(STDERR_FILENO, "read failed: %s\n", strerror(errno));
            close(fd);
            return 1;
        }
        if (got == 0) {
            break;
        }

        size_t to_write = (size_t)got;
        for (size_t i = 0; i < (size_t)got; ++i) {
            if (buf[i] == '\n') {
                to_write = i + 1;
                done = 1;
                break;
            }
        }
        if (write_all(STDOUT_FILENO, buf, to_write) != 0) {
            close(fd);
            return 1;
        }
    }

    close(fd);
    return 0;
}

