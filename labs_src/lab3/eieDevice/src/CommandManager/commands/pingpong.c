#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#include "pingpong.h"

static void command_pingpong_execute(char *name, char *req_msg, char *resp_msg){
    cJSON *payload = cJSON_Parse(req_msg);
    resp_msg = cJSON_Print(payload);
    cJSON_Delete(payload);
}

struct CommandOps command_pingpong_ops = {
    .execute = command_pingpong_execute,
};

struct Command * command_pingpong_create(const char *name)
{
    return command_create((char *)name, &command_pingpong_ops);
}