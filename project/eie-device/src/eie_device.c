#include "eie_device/eie_device.h"


// Create device definition 
device * create_device(char *cfg_json,  char * namespace){
    device * dev = malloc(sizeof(device));
    dev->thing_id = 20;
    return dev;
}

// Destroy a device
int destroy_device(device *dev){
    return 1;
}

//Register a Callback
int register_callback(feature_clbk * clbk){
    return 1;
}

// Update status feature
int update_feature(char * feature_id, char * data){
    return 1;
}