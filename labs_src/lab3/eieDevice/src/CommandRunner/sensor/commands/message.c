#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#include "message.h"

static char* command_message_execute(char *name, char *req_msg, char *resp_msg){
  cJSON *payload = cJSON_Parse(req_msg);
   
  cJSON *item = cJSON_CreateString("Hola");
  cJSON_AddItemToObject(payload, "output", item);
  cJSON_Delete(item);
   
  resp_msg = cJSON_Print(payload);
  cJSON_Delete(payload)
}

struct CommandOps command_message_ops = {
  .execute = command_message_execute,
};

struct Command * command_message_create(const char *name)
{
    struct MessageInfo info = {};
    struct CommandMessageState *state =
        calloc(1, sizeof(struct CommandMessageState));
    if (state == NULL) {
        fprintf(stderr, "Failed to allocate command message state\n");
        return NULL;
    }
    info.name = name;
    return command_create(&info, &command_message_ops, state);
}