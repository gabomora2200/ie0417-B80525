#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <eieDevice/external/uthash.h>
#include <eieDevice/CommandManager/command_manager.h>
/**
Command manager structure declaration (not exposed)
struct CommandManager {
    struct CommandManagerConfig cfg;
    cJSON *cfg_cjson;
    struct CommandFactory *sf;
};*/

static void execute(const char *name, void *priv, const char *req_msg, char *resp_msg){
    cJSON *payload = cJSON_Parse(req_msg);

    if (name == "message"){
        cJSON *item = cJSON_CreateString("Hola");
        cJSON_AddItemToObject(payload, "output", item);
        cJSON_Delete(item);
    }
    if (name == "ping_pong"){}

    if (name == "status"){  ///////Arreglar para sustituir keys/values

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
    }

    resp_msg = cJSON_Print(payload);
    cJSON_Delete(payload)
}
