#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <linux/limits.h>

// #include <eieDevice/CommandRunner/version.h>
// #include <eieDevice/CommandRunner/command.h>
// #include <eieDevice/CommandRunner/command_runner.h>
// #include <eieDevice/CommandRunner/sensor/sensor.h>
// #include <eieDevice/CommandRunner/sensor/manager.h>
#include "eieDevice/TransportServer/transport_server.h"



int main(int argc, char **argv) {

    int ret = 0;
    
    transport_server();

    return ret;
}
