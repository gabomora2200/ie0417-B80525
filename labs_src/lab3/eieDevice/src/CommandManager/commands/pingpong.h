#ifndef PINGPONG_H_
#define PINGPONG_H_

#include <eieDevice/CommandManager/command.h>

/**
 * Create a ping pong command struct.
 *
 * @param name Command Name.
 *
 * @return Structure of type command.
 */
struct Command * command_pingpong_create(const char *name);

#endif // PINGPONG_H_
