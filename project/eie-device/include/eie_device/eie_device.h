#ifndef EIE_DEVICE_H
#define EIE_DEVICE_H

#include <stdlib.h>
#include <stdio.h>

/*****************************/
/*     Structs and enums     */
/*****************************/
/**
 * @brief This structure contain the basic data of the thing 
 * 
 */
typedef struct {
    int thing_id;
    char * namespace;
} device;

/**
 * @brief 
 * 
 */
typedef struct
{
    char * feature_id;
    void * clbk_fn;
} feature_clbk;


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
device * create_device(char *cfg_json, char * namespace);


/**
 * @brief Destroy Device "object"
 * 
 * @param dev  Device object
 * @return int Fail or pass
 */
int destroy_device(device *dev);

/**
 * @brief 
 * 
 * @param clbk_fn 
 * @param feature_id 
 * @return int 
 */
int register_callback(feature_clbk * clbk);

/**
 * @brief update a feature
 * 
 * @param feature_id 
 * @param data 
 * @return int 
 */
int update_feature(char * feature_id, char * data);

/**
 * @brief Add or delete a feature
 * 
 * @param feature_id 
 * @return int 
 */
int modify_config(char * feature_id);

#endif //EIE_DEVICE_H