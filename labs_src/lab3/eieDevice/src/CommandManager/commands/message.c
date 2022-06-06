#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#include "message.h"

static void command_message_execute(char *name, char *req_msg, char *resp_msg){
  cJSON *payload = cJSON_Parse(req_msg);
   
  cJSON *item = cJSON_CreateString("Hola");
  cJSON_AddItemToObject(payload, "output", item);
  cJSON_Delete(item);
   
  resp_msg = cJSON_Print(payload);
  cJSON_Delete(payload);
}

struct CommandOps command_message_ops = {
  .execute = command_message_execute,
};

struct Command * command_message_create(const char *name)
{
  return command_create((char *)name, &command_message_ops);
}