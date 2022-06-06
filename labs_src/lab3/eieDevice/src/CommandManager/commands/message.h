#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <eieDevice/CommandManager/command.h>

// void command_message_execute(const char *name, char *req_msg, char *resp_msg);

struct Command * command_message_create(const char *name);

#endif // MESSAGE_H_
