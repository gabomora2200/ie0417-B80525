#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include <string.h>

#include "pingpong.h"

static void command_pingpong_execute(char *name, char *req_msg, char *resp_msg){

    cJSON_Minify(req_msg);
    cJSON *payload = cJSON_Parse(req_msg);
    cJSON *copy_item = cJSON_Duplicate(payload, 1);
    strcpy(resp_msg, cJSON_Print(copy_item));
    cJSON_Delete(copy_item);   
    cJSON_Delete(payload);
}

struct CommandOps command_pingpong_ops = {
    .execute = command_pingpong_execute,
};

struct Command * command_pingpong_create(const char *name)
{
    return command_create((char *)name, &command_pingpong_ops);
}