#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include <string.h>

#include "status.h"

static void command_status_execute(char *name, char *req_msg, char *resp_msg){
    printf("\nEntrada: %s", req_msg);
    cJSON *payload = cJSON_Parse(req_msg);
    const cJSON *status = cJSON_GetObjectItemCaseSensitive(payload, "args1");
    
    printf("%s", status->valuestring);
    // cJSON_DeleteItemFromObject(payload, "args1");
    char c1[] = "carga";
    // status = "/0";
    if (strcmp(status->valuestring, c1)){
        cJSON *item = cJSON_CreateString("50");
        cJSON_ReplaceItemInObject(payload, "Output", item);
        cJSON_Delete(item);
    } else {
        cJSON *item = cJSON_CreateString("Active");
        cJSON_ReplaceItemInObject(payload, "Output", item);
        cJSON_Delete(item);
    }
    resp_msg = cJSON_Print(payload);
    cJSON_Delete(payload);
}

struct CommandOps command_status_ops = {
  .execute = command_status_execute,
};

struct Command * command_status_create(const char *name)
{
    return command_create((char *)name, &command_status_ops);
}