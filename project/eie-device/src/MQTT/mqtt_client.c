#include "MQTTClient.h"
#include <eie_device/mqtt_client/mqtt_client.h>
#include <eie_device/parser/parser.h>
#include <eie_device/eie_device.h>
#include <string.h>

#define ADDRESS     "tcp://172.17.0.1:1883"
#define CLIENTID    "eieDevice"
#define QOS         0
#define TIMEOUT     10000L
#define STR_MAX_SIZE  1000

typedef struct{
    // correlation id ptr
    char *correlation_id;
    // callback manager
    callback_manager *clbk_mgr;
    // thing_id
    char *thing_id;
} context_s;


static void conn_lost_cb(void *context, char *cause)
{
    printf("Connection lost\n");
    printf("Cause: %s\n", cause);
}


static int msg_arrived_cb(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    context_s *ctx = (context_s *)context;

    char* payload;
    char data[1000];
    char thing_id[100];
    char feature_id[100];

    char corr_id[100]; 

    payload = (char *)message->payload;

    // checking if callback is for device_descovery
    if(strcmp(topicName, "eie-manager/config/device_discovery/response") == 0){
        // Parsing payload:
        payload_extract(payload, thing_id, corr_id);

        if(strcmp(corr_id, ctx->correlation_id) == 0){
            strcpy(ctx->thing_id, thing_id);
        } 
       
        MQTTClient_freeMessage(&message);
        MQTTClient_free(topicName);
        return 1;
    } else {
        // Parsing message
        callback_resp_parser(payload, thing_id, feature_id, data);

        // executing callback manager 
        callback_manager_clbk_execute(ctx->clbk_mgr, feature_id, data, strlen(data));
    }

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return 1;
}

static MQTTClient_message MQTT_create_message(char * message){
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = message;
    pubmsg.payloadlen = strlen(message);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    return pubmsg;

}

MQTTClient *MQTT_client_create(callback_manager *clbk_mgr, char *cor_id, char *thing_id)
{
    context_s * ctx = (context_s *)malloc(sizeof(context_s));

    ctx->clbk_mgr = clbk_mgr;
    ctx->correlation_id = (char *)malloc(strlen(cor_id));
    strcpy(ctx->correlation_id, cor_id);
    
    ctx->thing_id = thing_id;

    char client_id[100];

    strcpy(client_id, CLIENTID);
    strcat(client_id, cor_id);
    
    MQTTClient* client = (MQTTClient *)malloc(sizeof(MQTTClient));
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_create(client, ADDRESS, client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    int callback = MQTTClient_setCallbacks(*client, (void *)ctx, conn_lost_cb, msg_arrived_cb, NULL);
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
    if (disconnect != MQTTCLIENT_SUCCESS){
        printf("Client fail to disconnect\n");
    }
    MQTTClient_destroy(client);
}


int MQTT_publish(MQTTClient* client, char *topic, char* message){
    MQTTClient_deliveryToken token;
    MQTTClient_message pubmsg = MQTT_create_message(message);
    int status = MQTTClient_publishMessage(*client, topic, &pubmsg, &token);
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

