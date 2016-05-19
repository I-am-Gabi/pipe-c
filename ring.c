//
// Created by Gabriela on 19/05/16.
//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define NSTATIONS 5

// STDOUT_FILENO    1
// STDIN_FILENO	    0

// return the station id
int station(int n) {
    return n % NSTATIONS;
}

// close the file descriptor of a station
void close_station(int fd[NSTATIONS]) {
    // closes up input side current station pip
    close(fd[0]);

    // closes up output side current station pip
    close(fd[1]);
}

// close all file descriptors
void close_all(int fd[NSTATIONS][2]) {
    for (int station_i = 0; station_i < NSTATIONS; ++station_i)
        close_station(fd[station_i]);
}

// set the pipe
void make_pipe(int fd[NSTATIONS][2]) {
    for (int station_i = 0; station_i < NSTATIONS; ++station_i) {
        // make the pipe
        if (pipe(fd[station_i]) == -1)
            fprintf(stderr, "Pipe failed");
    }
}

int main() {
    int station_i;
    int fd[NSTATIONS][2];

    make_pipe(fd);

    for (station_i = 0; station_i < NSTATIONS; ++station_i) {
        switch (fork()) {
            case -1:
                perror("fork error");
                abort();
            case 0:
                // bind output standard
                dup2(fd[station(station_i)][1], STDOUT_FILENO);

                // bind input standard
                if (station_i == 0)
                    dup2(fd[station(NSTATIONS - 1)][0], STDIN_FILENO);
                else
                    dup2(fd[station(station_i - 1)][0], STDIN_FILENO);

                // current station
                char current_station[3];
                sprintf(current_station, "%d", station_i);

                // close all file descriptor
                close_all(fd);

                // fprintf(stderr, "station : %s\n", current_station);

                // execute station
                execl("./station", "./station", current_station, NULL);

                // error
                perror("error exec");

                // child end
                exit(0);
            default:break;
        }
    }

    // closes all file descriptors
    close_all(fd);

    // wait for the children
    for (station_i = 0; station_i < NSTATIONS; ++station_i)
        wait(0);

    // parent end
    exit(0);
}


