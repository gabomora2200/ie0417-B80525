#include "eie_device/eie_device.h"


// Create device definition 
thing* create_device(char *cfg_json){
    thing * device = malloc(sizeof(thing));
    device->thing_id = 20;
    return device;
}