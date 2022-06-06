#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <eieDevice/external/uthash.h>
#include <eieDevice/CommandManager/command_manager.h>
#include <eieDevice/CommandManager/command.h>
#include "commands/factory.h"

/** Entry structure to support adding commands to an UT hash table */
struct CommandHashEntry {
    struct Command *cmd;
    UT_hash_handle hh;
};

/** Command manager structure declaration (not exposed) */
struct CommandManager {
    struct CommandFactory *sf;
    /** Head entry for the command hash table */
    struct CommandHashEntry *command_ht;
};

/** Add command to the manager's command hash table */
static int command_ht_add(struct CommandManager *smgr, struct Command *cmd)
{
    struct CommandHashEntry *entry =
        malloc(sizeof(struct CommandHashEntry));
    if (entry == NULL) {
        fprintf(stderr, "Failed to allocate command hash entry\n");
        return -ENOMEM;
    }
    printf("%s: command name=%s", __func__, cmd->name);
    entry->cmd = cmd;
    HASH_ADD_KEYPTR(hh, smgr->command_ht, cmd->name, strlen(cmd->name), entry);
    return 0;
}

/** Creates the manager's command hash table and populates it with cJSON */
static int command_ht_create(struct CommandManager *smgr)
{
    int ret;

    // Init head entry for command hash table
    smgr->command_ht = NULL;

    char *names[3] = {"message", "status", "ping_pong"};
    // Iterate over config array to create commands
    for(int i = 0; i < 3; i++)
    {
        struct Command *cmd = NULL;
        char *name = names[i];
    
        // Create command and add it to hash table
        cmd = command_factory_command_create(smgr->sf, name);
        if (cmd == NULL) {
            fprintf(stderr, "Failed to create command with name: %s\n",
                name);
            return -1;
        }
        ret = command_ht_add(smgr, cmd);
        if (ret) {
            // fprintf(stderr, "Failed to add command with type: %s, name: %s\n",
            //         cmd->info.type, cmd->info.name);
            return ret;
        }
    }

    return 0;
}

/** Destroys the manager's command hash table */
static void command_ht_destroy(struct CommandManager *smgr)
{
    struct CommandHashEntry *entry, *tmp;
    HASH_ITER(hh, smgr->command_ht, entry, tmp) {
        HASH_DEL(smgr->command_ht, entry);
        free(entry);
    }
}

struct CommandManager *command_manager_create()
{
    int ret;
    struct CommandManager *smgr =
        (struct CommandManager *)calloc(1, sizeof(struct CommandManager));
    if (smgr == NULL) {
        fprintf(stderr, "Failed to allocate command manager\n");
        return NULL;
    }

    smgr->sf = command_factory_create();
    if (smgr->sf == NULL) {
        fprintf(stderr, "Failed to create command factory\n");
        return NULL;
    }

    ret = command_ht_create(smgr);
    if (ret) {
        fprintf(stderr, "Failed to create command hash table with ret=%d\n", ret);
        return NULL;
    }

    return smgr;
}

struct Command *command_manager_command_get(struct CommandManager *smgr,
                                         const char *name)
{
    struct CommandHashEntry *entry = NULL;
    HASH_FIND(hh, smgr->command_ht, name, strlen(name), entry);
    if (entry == NULL) {
        fprintf(stderr, "Command entry not found for name: %s\n", name);
        return NULL;
    }
    return entry->cmd;
}

struct cmd_ptr {
    struct Command *cmd;
};

/** Command read command execute function */
static void cmd_exec_fn(void *data, char *req_msg, char *resp_msg)
{
    struct cmd_ptr *cmd_data = data;
    struct Command *cmd = cmd_data->cmd;
    resp_msg = command_execute(cmd, req_msg);
    //printf("Command read command: [%s]: %s: %f %s\n",
    //       cmd->info.type, cmd->info.name, val, cmd->info.unit);
    // return resp_msg;
}

void cmd_create_exec(
    struct CommandManager *smgr,
    const char *name,
    char *req_msg,
    char *resp_msg)
{
    struct cmd_ptr *cmd_data = malloc(sizeof(struct cmd_ptr));
    if (cmd_data == NULL) {
        fprintf(stderr, "Failed to allocate sensor read command data\n");
        // return NULL;
    }
    struct Command * cmd = command_manager_command_get(smgr, name);
    // if (cmd == NULL) return NULL;
    cmd_data->cmd = cmd;

    cmd_exec_fn(cmd_data, req_msg, req_msg);
}


void command_manager_destroy(struct CommandManager *smgr)
{
    command_ht_destroy(smgr);
    command_factory_destroy(smgr->sf);
    //cjson_handle_destroy(smgr->cfg_cjson);
    free(smgr);
}