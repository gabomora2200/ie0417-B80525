#include "eie_device/eie_device.h"
#include "eie_device/callback_manager/callback_manager.h"
#include "eie_device/mqtt_client/mqtt_client.h"
#include "MQTTClient.h"


struct device{
    int thing_id;
    char * namespace;
    char * device_topic;
    callback_manager * clkb_mgr;
    MQTTClient * mqtt_client;
};


// Create device definition 
struct device *eie_device_create(char *cfg_json){
    struct device * dev = malloc(sizeof(struct device));
    
    /** Creat the callback manager */
    dev->clkb_mgr = callback_manager_create();
    dev->mqtt_client = MQTT_client_create(dev->clkb_mgr);

    return dev;
}

// Destroy a device
eie_status eie_device_destroy(struct device *dev){
    callback_manager_destroy(dev->clkb_mgr);
    free(dev);
    return OK;
}

//Register a Callback
eie_status eie_device_register_callback(struct device * dev, char * feature_id,
        eie_callback_execute_t clbk_fn){
    int ret;
    ret = callback_manager_add_clbk(dev->clkb_mgr, feature_id, clbk_fn);
    if(ret){
        return ERROR;
    }
    return OK;
}

// Update status feature
eie_status eie_device_update_feature(struct device * dev, char * feature_id, char * data){
    return OK;
}

eie_status eie_device_modify_config(struct device * dev, char * feature_id){
    return OK;
}