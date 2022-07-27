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
    dev->mqtt_client = MQTT_client_create(dev->clkb_mgr, correlation_id, (void *)dev->thing_id);

    // // Device discovery sequence
    MQTT_subscribe(dev->mqtt_client, tp_dev_dis_rsp);

    //MQTT_publish(dev->mqtt_client, tp_dev_dis_req, parsed_cfg_json);

    //sleep(2);
    printf("thing_id: %s\n", dev->thing_id);
    strcpy(dev->thing_id, "sensor:0");

    // while(1){
    //     sleep(5); 

    //     if(strcmp(dev->thing_id, "")) {
    //         MQTT_publish(dev->mqtt_client, tp_dev_dis_req, cfg_json);
    //         continue;
    //     }
    //     else {
    //         break;
    //     }
    // }

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
    
    char* payload;
    payload = update_feature_parser(dev->thing_id, dev->policy, feature_id, data);
    //ret = MQTT_publish(dev->mqtt_client, "eie-manager/sensor:0", "{\"topic\":\"/sensor/0/things/twin/commands/modify\",\"path\":\"/features/ft_1/properties/status\",\"value\":{\"value\":9}}");
    ret = MQTT_publish(dev->mqtt_client, topic, payload);
    if(ret == 0){
        return ERROR;
    }
    return OK;
}

eie_status eie_device_modify_config(struct device * dev, char * feature_id){
    return OK;
}