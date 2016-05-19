//
// Created by Gabriela on 19/05/16.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../include/package.h"

int main(int argc, char **argv) {

    // package to receive
    struct Package package_receive;

    // check if the station is the station0
    if (!strcmp(argv[1], "0")) {
        // package to transfer from station 0
        struct Package package_send = { FREE, 0, 4, "data sending..." };
        write(1, &package_send, PACKAGE_LEN);
    }

    while (1) {
        // read standard input
        read(0, &package_receive, PACKAGE_LEN);
        fprintf(stderr, "station [%s] received : %s \n", argv[1], package_receive.content);

        // sleep 1 second
        sleep(1);

        // write standard output
        write(1, &package_receive, PACKAGE_LEN);
    }
}