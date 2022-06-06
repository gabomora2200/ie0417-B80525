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
    printf("%s: command name=%s, type=%s\n", __func__, cmd->info.name, cmd->info.type);
    entry->cmd = cmd;
    HASH_ADD_KEYPTR(hh, smgr->command_ht, cmd->info.name, strlen(cmd->info.name), entry);
    return 0;
}

/** Creates the manager's command hash table and populates it with cJSON */
static int command_ht_create(struct CommandManager *smgr)
{
    int ret;
    //cJSON *commands = NULL;
    int num_commands = 0;

    //commands = cJSON_GetObjectItem(smgr->cfg_cjson, "commands");
    // if (commands == NULL) {
    //     //fprintf(stderr, "Failed to read commands array: %s\n", cJSON_GetErrorPtr());
    //     return -1;
    // }

    // Init head entry for command hash table
    smgr->command_ht = NULL;

    // Iterate over config array to create commands
    //num_commands = cJSON_GetArraySize(commands);
    for(int i = 0; i < num_commands; i++)
    {
        struct Command *cmd = NULL;
        //cJSON *command, *obj;
        char *name, *type;
        //command = cJSON_GetArrayItem(commands, i);

        // Read type and name from JSON
        //obj = cJSON_GetObjectItem(command, "type");
        // if (obj == NULL) {
        //     fprintf(stderr, "Failed to read command type: %s\n", cJSON_GetErrorPtr());
        //     return -1;
        // }
        // //type = cJSON_GetStringValue(obj);

        // //obj = cJSON_GetObjectItem(command, "name");
        // if (obj == NULL) {
        //     fprintf(stderr, "Failed to read command name: %s\n", cJSON_GetErrorPtr());
        //     return -1;
        // }
        //name = cJSON_GetStringValue(obj);

        // Create command and add it to hash table
        cmd = command_factory_command_create(smgr->sf, type, name);
        if (cmd == NULL) {
            fprintf(stderr, "Failed to create command with type: %s, name: %s\n",
                    type, name);
            return -1;
        }
        ret = command_ht_add(smgr, cmd);
        if (ret) {
            fprintf(stderr, "Failed to add command with type: %s, name: %s\n",
                    cmd->info.type, cmd->info.name);
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

/** Command read command private data */
struct cmd_ptr {
    struct Command *cmd;
};

/** Command read command execute function */
char* cmd_exec_fn(void *data, char* req_msg)
{
    struct cmd_ptr *cmd_data = data;
    struct Command *cmd = cmd_data->cmd;
    char *resp_msg = command_execute(cmd, req_msg);
    //printf("Command read command: [%s]: %s: %f %s\n",
    //       cmd->info.type, cmd->info.name, val, cmd->info.unit);
    return resp_msg;
}


void command_manager_destroy(struct CommandManager *smgr)
{
    command_ht_destroy(smgr);
    command_factory_destroy(smgr->sf);
    //cjson_handle_destroy(smgr->cfg_cjson);
    free(smgr);
}