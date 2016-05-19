//
// Created by Gabriela on 19/05/16.
//

#ifndef REDIRECTFLUX_PACKAGE_H
#define REDIRECTFLUX_PACKAGE_H

#define MSG_LEN 50

#define PACKAGE_LEN sizeof(struct Package)

typedef enum { FREE, ACK, BUSY} token;

struct Package {
    token tk;
    int   transmitters;
    int   receptors;
    char  content[MSG_LEN];
};

#endif //REDIRECTFLUX_PACKAGE_H
