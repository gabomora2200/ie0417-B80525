#ifndef CLIENT_H
#define CLIENT_H

#include "MQTTClient.h"
#include <eie_device/eie_device.h>
#include <eie_device/callback_manager/callback_manager.h>
#include <stdlib.h>
#include <stdio.h>

/*****************************/
/*     Structs and enums     */
/*****************************/

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
//void Setup();


/**
 * @brief 
 * 
 * @param dev 
 * @return eie_status 
 */

MQTTClient *MQTT_client_create(callback_manager *clbk_mgr);

void MQTT_client_destroy(MQTTClient* client);

int MQTT_publish(MQTTClient* client, char *topic, char * mesaage);

int MQTT_subscribe(MQTTClient* client, char *topic);


/**
 * @brief 
 * 
 * @param dev 
 * @param feature_id 
 * @return eie_status 
 *
eie_status eie_device_modify_config(struct device * dev, char * feature_id);*/

#endif //EIE_DEVICE_H