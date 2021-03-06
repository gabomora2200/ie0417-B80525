#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <eieDevice/external/uthash.h>

#include "factory.h"
#include "message.h"
#include "pingpong.h"
#include "status.h"

typedef struct Command * (*command_create_fn)(const char *name);


/** Command constructor information structure */
struct CommandCtorInfo {
    const char *name;
    command_create_fn create_fn;
};

/** Command constructor structure */
struct CommandConstructor {
    struct CommandCtorInfo info;
    UT_hash_handle hh;
};

/** Command factory structure */
struct CommandFactory {
    /** Head entry for the constructor hash table */
    struct CommandConstructor *ctor_ht;
};

/** Global array with the supported command constructors info */
static struct CommandCtorInfo ctors_info[] = {
  {"message", command_message_create},
  {"ping_pong", command_pingpong_create},
  {"status", command_status_create},
  {"", NULL}
};



/** Add constructor to the factory's hash table */ //****************
static int ctor_ht_add(struct CommandFactory *sf, struct CommandCtorInfo *info) {
    struct CommandConstructor *ctor =
        malloc(sizeof(struct CommandConstructor));
    if (ctor == NULL) {
        fprintf(stderr, "Failed to allocate command ctor for type: %s\n", info->name);
        return -ENOMEM;
    }
    ctor->info = *info;
    HASH_ADD_KEYPTR(hh, sf->ctor_ht, info->name, strlen(info->name), ctor);
    return 0;
}

/** Creates the factory's hash table and populates it with the global array info */ //****************
static int ctor_ht_create(struct CommandFactory *sf) {
    int ret;
    sf->ctor_ht = NULL;

    // Create ctors from info array and add them to hash table
    for (int i=0;; i++) {
        struct CommandCtorInfo *info = &ctors_info[i];
        // The last info struct should have type == ""
        if ((strlen(info->name) == 0) ||
            (info->create_fn == NULL)) break;

        ret = ctor_ht_add(sf, info);
        if (ret) {
            fprintf(stderr, "Failed to add command ctor for name: %s\n", info->name);
            return ret;
        }
    }
    return 0;
}

/** Destroys the factory's constructor hash table */ //***********************
static void ctor_ht_destroy(struct CommandFactory *sf)
{
    struct CommandConstructor *ctor, *tmp;
    HASH_ITER(hh, sf->ctor_ht, ctor, tmp) {
        HASH_DEL(sf->ctor_ht, ctor);
        free(ctor);
    }
}

struct CommandFactory *command_factory_create(void)
{
    struct CommandFactory *sf =
        (struct CommandFactory *)calloc(1, sizeof(struct CommandFactory));
    if (sf == NULL) {
        fprintf(stderr, "Failed to allocate command factory\n");
        return NULL;
    }
    ctor_ht_create(sf);
    return sf;
}

struct Command *command_factory_command_create(struct CommandFactory *sf,
                                            const char *name)
{
    struct CommandConstructor *ctor = NULL;
    HASH_FIND(hh, sf->ctor_ht, name, strlen(name), ctor);
    if (ctor == NULL) {
        fprintf(stderr, "Command ctor not found for name: %s\n", name);
        return NULL;
    }
    return ctor->info.create_fn(name);
}

void command_factory_destroy(struct CommandFactory *sf)
{
    ctor_ht_destroy(sf);
    free(sf);
}


