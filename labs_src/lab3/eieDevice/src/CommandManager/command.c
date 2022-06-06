#include <stdio.h>
#include <stdlib.h>

#include <eieDevice/CommandManager/command.h>

struct Command *command_create(char *name,
                             struct CommandOps *ops)
{
    struct Command *cmd =
        (struct Command *)calloc(1, sizeof(struct Command));
    if (cmd == NULL) {
        fprintf(stderr, "Failed to allocate command\n");
        return NULL;
    }
    cmd->name = name;
    cmd->ops = ops;
    return cmd;
}

char* command_execute(struct Command *cmd, char *req_msg)
{
    char *resp_msg = NULL;
    if (cmd->ops && cmd->ops->execute) {
        cmd->ops->execute(cmd->name, req_msg, resp_msg);
    }
    return resp_msg;
}

void command_destroy(struct Command *cmd)
{
    free(cmd);
}