#include "MQTTClient.h"
#include "client.h"
#include <string.h>

#define ADDRESS     "tcp://172.17.0.1:1883"
#define CLIENTID    "eieDevice"
#define QOS         1
#define TIMEOUT     10000L
#define STR_MAX_SIZE  1000


MQTTClient client;
//MQTTClient_deliveryToken token;
/*
void Setup()
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    int callback = MQTTClient_setCallbacks(client, NULL, conn_lost_cb, msg_arrived_cb, msg_delivered_cb);
    int connection = MQTTClient_connect(client, &conn_opts);
}*/

void conn_lost_cb(void *context, char *cause)
{
    printf("Connection lost\n");
    printf("Cause: %s\n", cause);
}

void msg_delivered_cb(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
}

int msg_arrived_cb(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    char* payload;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payload = (char *)message->payload;
    for(int i=0; i < message->payloadlen; i++) {
        putchar(*payload++);
    }
    putchar('\n');
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

}


void TearDown(){
    int disconnect = MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
}


void MQTT_publish(char *topic, MQTTClient_message pubmsg){
    MQTTClient_deliveryToken token;
    int status = MQTTClient_publishMessage(client, "device/create", &pubmsg, &token);
    int completion = MQTTClient_waitForCompletion(client, token, TIMEOUT);

}

void MQTT_suscribe(char *topic){

    int status = MQTTClient_subscribe(client, topic, QOS);
    
}


void MQTT_client(){

    //Setup();

    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    int callback = MQTTClient_setCallbacks(client, NULL, conn_lost_cb, msg_arrived_cb, msg_delivered_cb);
    int connection = MQTTClient_connect(client, &conn_opts);

    int ret = 0;
    
    MQTTClient_message pubmsg = MQTTClient_message_initializer;

    char msg[STR_MAX_SIZE];

    ret = snprintf(msg, STR_MAX_SIZE, "Hello!: Num A: %d, Num B: %d");

    pubmsg.payload = msg;
    pubmsg.payloadlen = strlen(msg);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    MQTT_suscribe("devices/create");

    MQTT_publish("devices/send", pubmsg);

    

}