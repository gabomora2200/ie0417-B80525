#ifndef PINGPONG_H_
#define PINGPONG_H_

#include <eieDevice/CommandManager/command.h>

// void command_pingpong_execute(const char *name, char *req_msg, char *resp_msg);

struct Command * command_pingpong_create(const char *name);

#endif // PINGPONG_H_
