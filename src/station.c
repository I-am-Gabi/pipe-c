//
// Created by Gabriela on 19/05/16.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../include/package.h"


void interface_station(int station_current) {
    int station_to = station_current;
    FILE * input;
    char answer[50];

    fprintf(stderr, "Do you want send a message? [y/n] ");
    input = fopen("/dev/tty", "a+");
    fscanf(input, "%s", answer);
    fclose(input);

    if (!strcmp(answer, "y")) {
        fprintf(stderr, "You are in the station %d. \nWhere you want to send the package? ", station_current);
        input = fopen("/dev/tty", "a+");
        fscanf(input, "%d", &station_to);
        fclose(input);
    }

    // package to transfer from station 0
    struct Package package_send = { BUSY, station_current, station_to, "package sending..." };
    write(1, &package_send, PACKAGE_LEN);
}

int main(int argc, char **argv) {

    int station_id = atoi(argv[1]);

    // package to receive
    struct Package package_receive;

    // check if the station is the station0
    if (!strcmp(argv[1], "0"))
        interface_station(station_id);

    while (1) {
        // read standard input
        read(0, &package_receive, PACKAGE_LEN);
        fprintf(stderr, "station [%s] received : %s from : %d -> to: %d\n",
                argv[1], package_receive.content, package_receive.transmitters, package_receive.receptors);

        if (package_receive.tk == FREE)
            interface_station(station_id);

        // the package find the receptor
        if (package_receive.receptors == station_id)
            package_receive.tk = ACK;
        // the package returns to the transmitter
        else if (package_receive.transmitters == station_id && package_receive.tk == ACK)
            package_receive.tk = FREE;

        // sleep 1 second
        sleep(1);

        // write standard output
        write(1, &package_receive, PACKAGE_LEN);
    }
}