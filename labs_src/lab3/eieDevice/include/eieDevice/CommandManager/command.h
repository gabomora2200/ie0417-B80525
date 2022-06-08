#ifndef COMMAND_H_
#define COMMAND_H_

/** Command operations to implement specific command types */
struct CommandOps
{
    const char *name;
    void (*execute)(char *name, char *req_msg, char *resp_msg);
};


/** Command structure */
struct Command {
    /** Command information */
    char *name;
    /** Command private data*/
    void *priv;
    /** Command operations */
    struct CommandOps *ops;

};

/**
 * Creates a command
 *
 * A command can be read according to a custom operation
 * and holds generic information about its name, type and
 * measurement unit.
 *
 * @param name Command name.
 * @param ops  Command operations.
 *
 * @return Pointer to a command manager structure.
 */
struct Command *command_create(char *name,
                             struct CommandOps *ops);

/**
 * Reads the command
 *
 * @param cmd Command structure.
 * @param req_msg Request message
 * @param resp_msg response message.
 *
 * @return Value representing the command measurement.
 */
void command_execute(struct Command *cmd, char *req_msg, char *resp_msg);

/**
 * Destroys the command
 *
 * @param cmd Command structure.
 */
void command_destroy(struct Command *cmd);

#endif // COMMAND_H_
