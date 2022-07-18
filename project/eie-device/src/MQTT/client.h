#ifndef CLIENT_H
#define CLIENT_H

#include "MQTTClient.h"
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
void Setup();


/**
 * @brief 
 * 
 * @param dev 
 * @return eie_status 
 */


void TearDown();


void MQTT_publish(char *topic, MQTTClient_message pubmsg)

void MQTT_suscribe(char *topic)

/**
 * @brief 
 * 
 * @param dev 
 * @param feature_id 
 * @return eie_status 
 *
eie_status eie_device_modify_config(struct device * dev, char * feature_id);*/

#endif //EIE_DEVICE_H