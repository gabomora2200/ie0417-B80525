#ifndef CLIENT_H
#define CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "MQTTClient.h"
#include <eie_device/eie_device.h>
#include <eie_device/callback_manager/callback_manager.h>
#include <stdlib.h>
#include <stdio.h>

/*****************************/
/*         Functions         */
/*****************************/

/**
 * @brief 
 * 
 * @param clbk_mgr 
 * @param cor_id 
 * @param thing_id 
 * @return MQTTClient* 
 */
MQTTClient *MQTT_client_create(callback_manager *clbk_mgr, char *cor_id, char *thing_id);

/**
 * @brief 
 * 
 * @param client 
 */
void MQTT_client_destroy(MQTTClient* client);

/**
 * @brief 
 * 
 * @param client 
 * @param topic 
 * @param message 
 * @return int 
 */
int MQTT_publish(MQTTClient* client, char *topic, char *message);

/**
 * @brief 
 * 
 * @param client 
 * @param topic 
 * @return int 
 */
int MQTT_subscribe(MQTTClient* client, char *topic);


#ifdef __cplusplus
}
#endif

#endif //EIE_DEVICE_H