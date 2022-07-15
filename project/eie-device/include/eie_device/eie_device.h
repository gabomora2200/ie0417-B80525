#ifndef EIE_DEVICE_H
#define EIE_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>

/*****************************/
/*     Structs and enums     */
/*****************************/

/**
 * @brief 
 * 
 */
typedef void(*eie_callback_execute_t)(void *payload, int payloadlen);

/**
 * @brief This structure contain the basic data of the thing 
 * 
 */
struct device;

typedef enum {
    OK, 
    ERROR
} eie_status;

/*****************************/
/*         Functions         */
/*****************************/

/**
 * @brief Create a device object
 * 
 * @param cfg_json thing config structure in json format
 * @param namespace type of device
 * @return device* 
 */
struct device *eie_device_create(char *cfg_json);


/**
 * @brief 
 * 
 * @param dev 
 * @return eie_status 
 */
eie_status eie_device_destroy(struct device *dev);

/**
 * @brief 
 * 
 * @param dev 
 * @param clbk 
 * @return eie_status 
 */
eie_status eie_device_register_callback(struct device * dev, char * feature_id, eie_callback_execute_t clbk_fn);

/**
 * @brief 
 * 
 * @param dev 
 * @param feature_id 
 * @param data 
 * @return eie_status 
 */
eie_status eie_device_update_feature(struct device * dev, char * feature_id, char * data);

/**
 * @brief 
 * 
 * @param dev 
 * @param feature_id 
 * @return eie_status 
 */
eie_status eie_device_modify_config(struct device * dev, char * feature_id);

#ifdef __cplusplus
}
#endif


#endif //EIE_DEVICE_H