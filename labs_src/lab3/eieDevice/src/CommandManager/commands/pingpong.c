#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#include "pingpong.h"

static void command_pingpong_execute(char *name, char *req_msg, char *resp_msg){
    cJSON *payload = cJSON_Parse(req_msg);
    resp_msg = cJSON_Print(payload);
    cJSON_Delete(payload)
}

struct PingPongOps command_pingpong_ops = {
    .execute = command_pingpong_execute,
};

struct Command * command_pingpong_create(const char *name)
{
    struct PingPongInfo info = {};
    struct CommandPingPongState *state =
        calloc(1, sizeof(struct CommandPingPongState));
    if (state == NULL) {
        fprintf(stderr, "Failed to allocate ping pong command state\n");
        return NULL;
    }
    info.name = name;
    return command_create(&info, &command_pingpong_execute, state);
}