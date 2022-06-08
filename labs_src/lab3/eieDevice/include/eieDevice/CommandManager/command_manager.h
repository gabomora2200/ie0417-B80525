#ifndef COMMANDMANAGER_H_
#define COMMANDMANAGER_H_

#include <cjson/cJSON.h>
#include <eieDevice/CommandManager/command.h>


/**
 * Creates a command manager
 *
 * The command manager is in charge of dealing with the lifecycle
 * of the command devices. It creates the commands from a JSON
 * config file and stores them in a hash table for name-based access.
 *
 * @param cfg Command manager configuration structure.
 *
 * @return Pointer to a command manager structure.
 */
struct CommandManager *command_manager_create(void);

/**
 * Gets a command from its name
 *
 * @param smgr Pointer to a command manager structure.
 * @param name Name of the command to get.
 *
 * @return Pointer to a command structure.
 */
struct Command *command_manager_command_get(struct CommandManager *smgr,
                                         const char *name);

/**
 * Creates a command read command from a command name.
 * It should be destroyed using the command_destroy API.
 *
 * @param smgr Pointer to a command manager structure.
 * @param name Name of the command.
 *
 * @return Pointer to a command structure.
 */
void cmd_create_exec(
    struct CommandManager *smgr,
    const char *name,
    char *req_msg,
    char *resp_msg);

/**
 * Destroys a command manager
 *
 * Cleans up all the internal resources in the command manager,
 * including the command instances.
 *
 * @param smgr Pointer to a command manager structure.
 */
void command_manager_destroy(struct CommandManager *smgr);





#endif // MANAGER_H_
