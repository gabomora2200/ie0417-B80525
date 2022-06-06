#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#include "message.h"

static void command_status_execute(char *name, char *req_msg, char *resp_msg){
    cJSON *payload = cJSON_Parse(req_msg);
    status = cJSON_GetStringValue(payload)
    cJSON_DeleteItemFromObject(payload, "args1")
    if (status == "carga"){
        cJSON *item = cJSON_CreateString("50");
        cJSON_ReplaceItemInObject(payload, "Output", item);
    } else {
        cJSON *item = cJSON_CreateString("Active");
        cJSON_ReplaceItemInObject(payload, "Output", item);
    }
    cJSON_Delete(item);
    resp_msg = cJSON_Print(payload);
    cJSON_Delete(payload)
}

struct StatusOps command_status_ops = {
  .execute = command_status_execute,
};

struct Command * command_status_create(const char *name)
{
    struct StatusInfo info = {};
    struct CommandStatusState *state =
        calloc(1, sizeof(struct CommandStatusState));
    if (state == NULL) {
        fprintf(stderr, "Failed to allocate status command state\n");
        return NULL;
    }
    info.name = name;
    return command_create(&info, &command_status_execute, state);
}