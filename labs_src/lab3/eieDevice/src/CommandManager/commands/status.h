#ifndef STATUS_H_
#define STATUS_H_

#include <eieDevice/CommandManager/command.h>

/**
 * Create a status command struct.
 *
 * @param name Command Name.
 *
 * @return Structure of type command.
 */
struct Command * command_status_create(const char *name);

#endif // STATUS_H_
