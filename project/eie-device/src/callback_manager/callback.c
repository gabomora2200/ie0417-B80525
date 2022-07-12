#include <stdio.h>
#include <stdlib.h>

#include "eie_device/callback_manager/callback.h"

callback * callback_create(char *feature_id,  eie_callback_execute_t clbk_fn){
    callback * clbk = (callback *)calloc(1, sizeof(callback));
    if(clbk == NULL) {
        fprintf(stderr, "Failed to allocate callback\n");
        return NULL;
    }
    clbk->feature_id = feature_id;
    clbk->clbk_fn = clbk_fn;
    return clbk;
}

void callback_destroy(callback * clbk){
    free(clbk);
}