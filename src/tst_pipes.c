//
// Created by Gabriela on 12/05/16.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <string.h>

char *cmd_1[] = { "ps", 0, 0 };
char *cmd_2[] = { "grep", "emacs", 0 };

void execute_command(int pfd[]) {
    int pid = fork();

    switch (pid) {
        case 0: // child
            // closes up output side of pipe
            close(pfd[1]);
            dup2(pfd[0], 0);

            // run grep command
            execlp(cmd_2[0], cmd_2[0], cmd_2[1], cmd_2[2]);
            perror(cmd_2[0]);
            break;
        case -1:
            perror("fork");
            exit(1);
        default:break;
    }
}

void execute() {
    pid_t  pid;
    int fd[2], status;

    // make the pipe
    if (pipe(fd) == -1)
        fprintf(stderr, "Pipe failed");

    pid = fork();

    switch (pid) {
        case -1: // error
            perror("ls: Fork error\n");
            _exit(1);

        case 0: // child process
            // closes up input side of pipe
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);

            // run ps command
            execlp(cmd_1[0], cmd_1[0], cmd_1[1], cmd_1[2]);
            perror(cmd_1[0]);

            exit(0);

        default: // parent process
            execute_command(fd);

            close(fd[0]);
            close(fd[1]);

            waitpid (pid, &status, 0);
    }
}

int main(int argc, char **argv) {
    execute();
    return 0;
}