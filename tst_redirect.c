//
// Created by Gabriela on 12/05/16.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/fcntl.h>

/**
 * Method to execute a command ls -lR in the root directory and sent
 * the output of the command or error output to directory/out file.
 */
void execute()
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("ls: Fork error\n");
        _exit(1);
    }
    else if (pid == 0) {
        int fd = creat("directory/out", 0644);
        dup2(fd, STDOUT_FILENO); /* standard output file descriptor */
        dup2(fd, STDERR_FILENO); /* standard error file descriptor */
        close(fd);

        if (execlp("ls", "ls", "-lR", ".", 0) < 0) {
            fprintf(stderr, "ls: %s No such file or directory\n", ".");
            exit(1);
        }
    }
    else {
        waitpid(pid, 0, 0);
    }
}

int main() {
    execute();
    return 0;
}

