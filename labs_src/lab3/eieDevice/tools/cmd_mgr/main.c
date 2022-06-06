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
    
    // struct Command *cmd = NULL;
    struct CommandManager *cmd_mgr = NULL;

    cmd_mgr = command_manager_create();




    if (cmd_mgr == NULL) {
        fprintf(stderr, "Failed to create command manager\n");
        return -1;
    }

    char *commands[3] = {"message", "status", "ping_pong"};

    // for (int i = 0; i<3 ; i++ ){
        // cmd = command_manager_command_get(cmd_mgr, commands[i]);
        
        // struct cmd_ptr *ptr = malloc(sizeof(struct cmd_ptrn *));
        // ptr->cmd = cmd;

        char req[] = {"{\"args1\":\"Hola\"}"};
        char *resp = malloc(sizeof(char *));

        cmd_create_exec(cmd_mgr, commands[2], req, resp);
        // cmd_exec_fn(ptr, req, resp);
        printf("\nResultado: %s\n", resp);
    // }


    return ret;
}
