#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static int wait_child(pid_t pid)
{
    int status = 0;
    while (waitpid(pid, &status, 0) < 0) {
        if (errno == EINTR) {
            continue;
        }
        perror("waitpid");
        return -1;
    }
    return WIFEXITED(status) && WEXITSTATUS(status) == 0 ? 0 : -1;
}

static int run_one(const char *command)
{
    int fds[2];
    if (pipe(fds) != 0) {
        perror("pipe");
        return -1;
    }

    pid_t command_pid = fork();
    if (command_pid < 0) {
        perror("fork");
        close(fds[0]);
        close(fds[1]);
        return -1;
    }
    if (command_pid == 0) {
        close(fds[0]);
        if (dup2(fds[1], STDOUT_FILENO) < 0) {
            _exit(127);
        }
        close(fds[1]);
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        _exit(127);
    }

    pid_t wc_pid = fork();
    if (wc_pid < 0) {
        perror("fork");
        close(fds[0]);
        close(fds[1]);
        (void)wait_child(command_pid);
        return -1;
    }
    if (wc_pid == 0) {
        close(fds[1]);
        if (dup2(fds[0], STDIN_FILENO) < 0) {
            _exit(127);
        }
        close(fds[0]);
        execlp("wc", "wc", "-c", (char *)NULL);
        _exit(127);
    }

    close(fds[0]);
    close(fds[1]);

    int ok = 0;
    if (wait_child(command_pid) != 0) {
        ok = -1;
    }
    if (wait_child(wc_pid) != 0) {
        ok = -1;
    }
    return ok;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s \"command args...\" [\"command args...\"]...\n", argv[0]);
        return 1;
    }

    int result = 0;
    for (int i = 1; i < argc; ++i) {
        if (run_one(argv[i]) != 0) {
            result = 1;
        }
    }
    return result;
}

