#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "eie_device/callback_manager/callback_manager.h"
#include "eie_device/callback_manager/callback.h"
#include <external/uthash.h>


/** Entry structure to support adding Callbacks to an UT hash table */
struct CallbackHashEntry {
    callback *clbk;
    UT_hash_handle hh;
};


/** Add Callback to the manager's Callback hash table */
static int callback_ht_add(callback_manager *clbk_mgr, callback *clbk)
{
    struct CallbackHashEntry *entry =
        malloc(sizeof(struct CallbackHashEntry));
    if (entry == NULL) {
        fprintf(stderr, "Failed to allocate callback hash entry\n");
        return -ENOMEM;
    }
    printf("%s: callback-feature id=%s\n", __func__, clbk->feature_id);
    entry->clbk = clbk;
    HASH_ADD_KEYPTR(hh, clbk_mgr->callback_ht, clbk->feature_id, strlen(clbk->feature_id), entry);
    return 0;
}

/** Deletes a single  */
static int callback_ht_del_item(callback_manager *clbk_mgr, const char *feature_id)
{
    struct CallbackHashEntry *entry = NULL;
    HASH_FIND(hh, clbk_mgr->callback_ht, feature_id, strlen(feature_id), entry);

    if(entry == NULL){
        return 1;
    }

    HASH_DEL(clbk_mgr->callback_ht, entry);
    return 0;
}

/** Destroys the manager's Callback hash table */
static void callback_ht_destroy(callback_manager *clbk_mgr)
{
    struct CallbackHashEntry *entry, *tmp;
    HASH_ITER(hh, clbk_mgr->callback_ht, entry, tmp) {
        HASH_DEL(clbk_mgr->callback_ht, entry);
        callback_destroy(entry->clbk);
        free(entry);
    }
}


callback_manager *callback_manager_create(void){
    
    callback_manager *clbk_mgr = 
        (callback_manager *)calloc(1, sizeof(callback_manager));
    
    if (clbk_mgr == NULL) {
        fprintf(stderr, "Failed to allocate callback manager\n");
        return NULL;
    }

    clbk_mgr->callback_ht = NULL;
    
    return clbk_mgr;
}


int callback_manager_add_clbk(callback_manager *clbk_mgr, char * feature_id, eie_callback_execute_t clbk_fn){
    // Checks that this callback wasn't registered before
    struct CallbackHashEntry *entry = NULL;
    HASH_FIND(hh, clbk_mgr->callback_ht, feature_id, strlen(feature_id), entry);

    if(entry != NULL){
        printf("The feature: %s already has a registered callback function\n", feature_id);
        return 1;
    }
    
    callback * clbk = callback_create(feature_id, clbk_fn);

    int ret;
    ret = callback_ht_add(clbk_mgr, clbk);
    if(ret){
        printf("Failed to add callback to hash table");
        return ret;
    }
    return 0;
}


int callback_manager_clbk_execute(callback_manager *clbk_mgr, char * feature_id, 
        char * payload, int payloadlen)
{
    struct CallbackHashEntry *entry = NULL;
    HASH_FIND(hh, clbk_mgr->callback_ht, feature_id, strlen(feature_id), entry);

    if(entry == NULL){
        printf("The feature: %s, doesn't have a registered callback function\n", feature_id);
        return 1;
    }

    entry->clbk->clbk_fn(payload, payloadlen);

    return 0;
}


int callback_manager_delete_clbk_feature(callback_manager *clbk_mgr, char * feature_id){
    callback_ht_del_item(clbk_mgr, feature_id);
    return 0;
}


void callback_manager_destroy(callback_manager *clbk_mgr){
    callback_ht_destroy(clbk_mgr);
    free(clbk_mgr);
}
