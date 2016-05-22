//
// Created by Gabriela on 19/05/16.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../include/package.h"


/**
 * Interface to handle with the communication between the client and the stations.
 * PS.: I used %30[^] to accepted an input with more than one word.
 */
void interface_station(int station_current, struct Package *package_data) {
    int station_to = station_current;
    FILE * input;
    char answer[50];
    char content[MSG_LEN];

    fprintf(stderr, "Do you want send a message? [y/n] ");
    input = fopen("/dev/tty", "a+");
    fscanf(input, "%30[^\n]", answer);

    if (!strcmp(answer, "y")) {
        fprintf(stderr, "You are in the station %d. \nWhere you want to send the package? ", station_current);
        input = fopen("/dev/tty", "a+");
        fscanf(input, "%d", &station_to);

        fprintf(stderr, "What is the content package? ");
        input = fopen("/dev/tty", "a+");
        fscanf(input, "%30[^\n]", content);

        package_data->tk = BUSY;
        package_data->transmitters = station_current;
        package_data->receptors = station_to;
        strcpy(package_data->content, content);
    }

    fclose(input);
}

/**
 * Protocol to define the rules of communication.
 */
void protocol(int station_id, struct Package *package_data) {
    if (package_data->tk == FREE)
        interface_station(station_id, package_data);

    // the package find the receptor
    if (package_data->receptors == station_id) {
        package_data->tk = ACK;
        fprintf(stderr, "The package arrived at the destination!\n");
    }
    // the package returns to the transmitter
    else if (package_data->transmitters == station_id && package_data->tk == ACK) {
        package_data->tk = FREE;
    }
}

int main(int argc, char **argv) {

    int station_id = atoi(argv[1]);

    // package to receive
    struct Package package_data;

    // check if the station is the station0
    if (!strcmp(argv[1], "0")) {
        interface_station(station_id, &package_data);

        // write standard output
        write(1, &package_data, PACKAGE_LEN);
    }

    while (1) {
        // read standard input
        read(0, &package_data, PACKAGE_LEN);
        fprintf(stderr, "station [%s] received : [%s] from : %d -> to: %d\n",
                argv[1], package_data.content, package_data.transmitters, package_data.receptors);

        // ring protocol
        protocol(station_id, &package_data);

        // sleep 1 second
        sleep(1);

        // write standard output
        write(1, &package_data, PACKAGE_LEN);
    }
}