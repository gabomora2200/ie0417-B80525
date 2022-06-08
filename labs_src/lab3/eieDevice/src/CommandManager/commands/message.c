#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include <string.h>

#include "message.h"

static void command_message_execute(char *name, char *req_msg, char *resp_msg){
  cJSON *hola = cJSON_CreateObject();
  cJSON *test = NULL;
  test = cJSON_CreateString("Hi!");
  cJSON_AddItemToObject(hola, "output", test);
  strcpy(resp_msg, cJSON_Print(hola));
  cJSON_Delete(hola);
}

struct CommandOps command_message_ops = {
  .execute = command_message_execute,
};

struct Command * command_message_create(const char *name)
{
  return command_create((char *)name, &command_message_ops);
}