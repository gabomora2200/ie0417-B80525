#ifndef EIE_DEVICE_H
#define EIE_DEVICE_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief This structure contain the basic data of the thing 
 * 
 */
typedef struct {
    int thing_id;
    features feat;
} device;

/**
 * @brief feature structure
 * 
 */
typedef struct
{
    /* data */
} features;


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
 */
void destroy_device(device *dev);

/**
 * @brief 
 * 
 * @param clbk_fn 
 * @param feature_name 
 * @param json_data 
 * @return int 
 */
int register_callback(void * clbk_fn, char * feature_name, char * json_data);



#endif //EIE_DEVICE_H