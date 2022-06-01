#include "eieDevice/TransportServer/transport_server.h"
#include "eieDevice/TransportServer/server.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <czmq.h>

void transport_server(){

    int ret;
    struct server_data rdata = {};
    const uint32_t sleep_ms = 1000;

    ret = pthread_create(&(rdata.tid), NULL, &server_fn, &rdata);

    if(ret != 0){
        //fprintf(stderr, "Failed to create thread: [%s]", stderr(ret));
    }

    while(!zsys_interrupted) {
        zclock_sleep(sleep_ms);
    }

    pthread_kill(rdata.tid, SIGINT);
    pthread_join(rdata.tid, NULL);

}