#ifndef CALLBACK_H
#define CALLBACK_H

#ifdef __cplusplus
extern "C" {
#endif



#include "eie_device/eie_device.h"

/** Callback structure */
typedef struct {
    /** Feature id */
    char *feature_id;
    
    /** Callback operation */
    eie_callback_execute_t clbk_fn;
} callback;


/**
 * @brief 
 * 
 * @param feature_id 
 * @param ops 
 * @return callback* 
 */
callback * callback_create(char *feature_id,  eie_callback_execute_t clbk_fn);


/**
 * @brief 
 * 
 * @param clbk 
 */
void callback_destroy(callback * clbk);

#ifdef __cplusplus
}
#endif
#endif //CALLBACK_H