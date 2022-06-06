#ifndef STATUS_H_
#define STATUS_H_

#include <eieDevice/CommandManager/command.h>

// void command_status_execute(const char *name, char *req_msg, char *resp_msg);

struct Command * command_status_create(const char *name);

#endif // STATUS_H_
