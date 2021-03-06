#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "eie_device/eie_device.h"
#include "eie_device/callback_manager/callback_manager.h"
#include "eie_device/mqtt_client/mqtt_client.h"
#include "eie_device/parser/parser.h"
#include "MQTTClient.h"


static char tp_dev_dis_rsp[] = "eie-manager/config/device_discovery/response";
static char tp_dev_dis_req[] = "eie-manager/config/device_discovery/request";

// char tp_thing[] = "eie-manager/sensor:0";

struct device{
    char thing_id[100];
    char policy[100];
    char namespace[100];
    callback_manager * clkb_mgr;
    MQTTClient * mqtt_client;
};


// Create device definition 
struct device *eie_device_create(char *cfg_json){
    struct device * dev = malloc(sizeof(struct device));
    
    // correlation_id random generation
    time_t t;
    srand((unsigned) time(&t));
    int x = rand();
    int length = snprintf( NULL, 0, "%d", x );
    char *correlation_id = malloc( length + 1 );
    snprintf( correlation_id, length + 1, "%d", x );

    // add correlation_id into cfg_json
    char *parsed_cfg_json;
    parsed_cfg_json = cfg_to_send(cfg_json, correlation_id, dev->namespace);

    /** Creat the callback manager */
    dev->clkb_mgr = callback_manager_create();
    dev->mqtt_client = MQTT_client_create(dev->clkb_mgr, correlation_id, dev->thing_id);

    // Device discovery sequence
    MQTT_subscribe(dev->mqtt_client, tp_dev_dis_rsp);

    MQTT_publish(dev->mqtt_client, tp_dev_dis_req, parsed_cfg_json); 

    
    while(1){
        sleep(2);
        if(strlen(dev->thing_id) >= 1 ){
            break;
        }
        else{
            printf("THING_ID not found!\n");
            MQTT_publish(dev->mqtt_client, tp_dev_dis_req, parsed_cfg_json);
        }
    }

    printf("THING_ID: %s\n", dev->thing_id);

    char tp_device_ditto[100];

    strcpy(tp_device_ditto, "eie-manager/");
    strcat(tp_device_ditto, dev->thing_id);
    
    printf("Topic of Ditto: %s\n", tp_device_ditto);

    MQTT_subscribe(dev->mqtt_client, tp_device_ditto);

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
    int ret;
    char topic[100];
    strcpy(topic, "eie-manager/");
    strcat(topic, dev->thing_id);
    strcat(topic, "/things/twin/commands/modify");

    char* payload;
    payload = update_feature_parser(dev->thing_id, dev->policy, feature_id, data);
    ret = MQTT_publish(dev->mqtt_client, topic, payload);
    if(ret == 0){
        return ERROR;
    }
    return OK;
}

eie_status eie_device_modify_config(struct device * dev, char * feature_id){
    return OK;
}