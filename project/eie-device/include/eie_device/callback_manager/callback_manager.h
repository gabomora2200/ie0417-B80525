#ifndef CALLBACK_MANAGER_H
#define CALLBACK_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "eie_device/eie_device.h"

/** Callback manager structure declaration */
typedef struct  {
    /** Head entry for the Callback hash table */
    struct CallbackHashEntry *callback_ht;
} callback_manager;


/**
 * @brief 
 * 
 * @return callback_manager* 
 */
callback_manager *callback_manager_create(void);

/**
 * @brief 
 * 
 * @param clbk_mgr 
 * @param feature_id 
 * @param clbk_fn 
 * @return int 
 */
int callback_manager_add_clbk(callback_manager *clbk_mgr, char * feature_id, eie_callback_execute_t clbk_fn);


/**
 * @brief 
 * 
 * @param clbk_mgr 
 * @param feature_id 
 * @param payload 
 * @param payloadlen 
 * @return int 
 */
int callback_manager_clbk_execute(callback_manager *clbk_mgr, 
    char * feature_id, char * payload, int payloadlen);


/**
 * @brief 
 * 
 * @param clbk_mgr 
 * @param feature_id 
 * @return int 
 */
int callback_manager_delete_clbk_feature(callback_manager *clbk_mgr, char * feature_id);

/**
 * @brief 
 * 
 * @param clbk_mgr 
 */
void callback_manager_destroy(callback_manager *clbk_mgr);

#ifdef __cplusplus
}
#endif
#endif //CALLBACK_MANAGER_H