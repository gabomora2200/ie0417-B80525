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
// #include "eieDevice/TransportServer/transport_server.h"

#include "eieDevice/CommandManager/command_manager.h"
#include "eieDevice/CommandManager/command.h"



int main(int argc, char **argv) {

    int ret = 0;
    struct CommandManager *cmd_mgr = NULL;
    cmd_mgr = command_manager_create();

    if (cmd_mgr == NULL) {
        fprintf(stderr, "Failed to create command manager\n");
        return -1;
    }

    char *commands[3] = {"message", "status", "ping_pong"};
    for (int i = 0; i<3 ; i++ ){

        char req[] = {"{\"args1\":\"carga\"}"};
        char *resp = malloc(sizeof(char *));

        cmd_create_exec(cmd_mgr, commands[i], req, resp);
        printf("\nResultado: %s\n", resp);
    }


    return ret;
}
