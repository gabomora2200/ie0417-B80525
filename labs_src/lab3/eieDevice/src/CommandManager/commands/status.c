#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include <string.h>

#include "status.h"

static void command_status_execute(char *name, char *req_msg, char *resp_msg){
    cJSON *payload = cJSON_Parse(req_msg);
    const cJSON *status = cJSON_GetObjectItemCaseSensitive(payload, "arg1");
    if (strcmp(status->valuestring, "carga")){
        cJSON *hola = cJSON_CreateObject();
        cJSON *test = NULL;
        test = cJSON_CreateString("active");
        cJSON_AddItemToObject(hola, "output", test);
        strcpy(resp_msg, cJSON_Print(hola));
        cJSON_Delete(hola);
    } else {
        cJSON *hola = cJSON_CreateObject();
        cJSON *test = NULL;
        test = cJSON_CreateString("50\%");
        cJSON_AddItemToObject(hola, "output", test);
        strcpy(resp_msg, cJSON_Print(hola));
        cJSON_Delete(hola);
    }
    cJSON_Delete(payload);
}

struct CommandOps command_status_ops = {
  .execute = command_status_execute,
};

struct Command * command_status_create(const char *name)
{
    return command_create((char *)name, &command_status_ops);
}