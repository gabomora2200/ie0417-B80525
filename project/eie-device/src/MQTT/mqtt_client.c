#include "MQTTClient.h"
#include <eie_device/mqtt_client/mqtt_client.h>
#include <string.h>

#define ADDRESS     "tcp://172.17.0.1:1883"
#define CLIENTID    "eieDevice"
#define QOS         1
#define TIMEOUT     10000L
#define STR_MAX_SIZE  1000


static void conn_lost_cb(void *context, char *cause)
{
    printf("Connection lost\n");
    printf("Cause: %s\n", cause);
}

/*static void msg_delivered_cb(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
}*/

static int msg_arrived_cb(void *context, char *topicName, int topicLen, MQTTClient_message *message)
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

    return MQTTCLIENT_SUCCESS;

}

static MQTTClient_message MQTT_create_message(char * message){
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = message;
    pubmsg.payloadlen = strlen(message);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    return pubmsg;

}

MQTTClient *MQTT_client_create(callback_manager *clbk_mgr)
{
    MQTTClient* client = (MQTTClient *)malloc(sizeof(MQTTClient));
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_create(client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    int callback = MQTTClient_setCallbacks(*client, NULL, conn_lost_cb, msg_arrived_cb, NULL);
    if (callback != MQTTCLIENT_SUCCESS){
        printf("Message fail to hanled\n");
        return NULL;
    }
    int connection = MQTTClient_connect(*client, &conn_opts);
    if (connection != MQTTCLIENT_SUCCESS){
        printf("Message fail to connect\n");
        return NULL;
    }
    return client;
}


void MQTT_client_destroy(MQTTClient* client){
    int disconnect = MQTTClient_disconnect(*client, 10000);
    if (disconnect != MQTTCLIENT_DISCONNECTED){
        printf("Client fail to disconnect\n");
    }
    MQTTClient_destroy(client);
}


int MQTT_publish(MQTTClient* client, char *topic, char* message){
    MQTTClient_deliveryToken token;
    MQTTClient_message pubmsg = MQTT_create_message(message);
    int status = MQTTClient_publishMessage(*client, "device/create", &pubmsg, &token);
    if (status != MQTTCLIENT_SUCCESS){
        printf("Fail to publish message\n");
        return 0;
    }
    int completion = MQTTClient_waitForCompletion(*client, token, TIMEOUT);
    if (completion != MQTTCLIENT_SUCCESS){
        printf("Message fail to complete\n");
        return 0;
    }
    return 1;
}

int MQTT_subscribe(MQTTClient* client, char *topic){

    int status = MQTTClient_subscribe(*client, topic, QOS);
    if (status != MQTTCLIENT_SUCCESS){
        printf("Client fail to subscribe\n");
        return 0;
    }
    return 1;
}



/*
MQTTClient *MQTT_client_create(){

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

    ret = snprintf(msg, STR_MAX_SIZE, "Hello!: Num A: Num B:");

    pubmsg.payload = msg;
    pubmsg.payloadlen = strlen(msg);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    MQTT_suscribe("devices/create");

    MQTT_publish("devices/send", pubmsg);

    

}*/