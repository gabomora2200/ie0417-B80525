#ifndef COMMANDMANAGER_H_
#define COMMANDMANAGER_H_

//#include <eieDevice/CommandRunner/command/command.h>

struct command_info(const char *name, void *priv,
                     void (*command_fn)(const char *name, void *priv, const char *req_msg, char *resp_msg));


/**
 * Creates a command factory
 *
 * The command factory is in charge of abstracting the construction
 * of different types of commands. The correct command type is going
 * to be instantiated internally according to the desired type
 * and the generic command structure is returned.
 *
 * @return Pointer to a command factory structure.
 */
struct CommandFactory *command_factory_create(void);

/**
 * Creates a command according to the factory logic
 *
 * @param sf   Command factory structure.
 * @param type Command type to be created.
 * @param name Name of the command to create.
 *
 * @return Pointer to a command factory structure.
 */
struct Command *command_factory_command_create(struct CommandFactory *sf,
                                            const char *type, const char *name);

/**
 * Destroys the command factory
 *
 * @param sf Command factory structure.
 */
void command_factory_destroy(struct CommandFactory *sf);

#endif // COMMANDMANAGER_H_
