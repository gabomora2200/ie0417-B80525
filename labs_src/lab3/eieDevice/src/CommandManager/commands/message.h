#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <eieDevice/CommandManager/command.h>

/**
 * Create a message command struct.
 *
 * @param name Command Name.
 *
 * @return Structure of type command.
 */
struct Command * command_message_create(const char *name);

#endif // MESSAGE_H_
