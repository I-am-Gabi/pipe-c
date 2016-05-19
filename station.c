//
// Created by Gabriela on 19/05/16.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define MSG_LEN 50

int main(int argc, char **argv) {
    char data_received[MSG_LEN];
    memset(data_received, 0, MSG_LEN-1);

    char data_send[MSG_LEN] = { "data sending..." };

    // check if the station is the station0
    if (!strcmp(argv[1], "0"))
        write(1, data_send, strlen(data_send));

    while (1) {
        // read standard input
        read(0, data_received, sizeof(data_received) + 1);
        fprintf(stderr, "station [%s] received : %s \n", argv[1], data_received);

        // sleep 1 second
        sleep(1);

        // write standard output
        write(1, data_send, strlen(data_send));
    }
}