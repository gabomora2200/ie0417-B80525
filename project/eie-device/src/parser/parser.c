#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <cjson/cJSON.h>
#include <eie_device/eie_device.h> //Arreglar esta referencia
#include <eie_device/parser/parser.h> //Arreglar esta referencia


char *update_feature_parser(char *thing_id, char *policy, char *feature_id, char *data){

    cJSON *json = cJSON_CreateObject();
    char str[100];
    strcpy(str, thing_id);
    char* tmp = str;

    char *topic = (char *)malloc((strlen(policy) + strlen(thing_id) + 1000));

    //strcpy(topic, policy);
    for(int i = 0; i <= strlen(str); i++)
    {
        if(*tmp == ':')  
        {
            *tmp = '/';
        }
        tmp++;
    }
    strcat(topic, str);
    strcat(topic, "/things/twin/commands/modify");

    char *path = (char *)malloc(strlen(feature_id) + 1000);

    strcpy(path, "/features/");
    strcat(path, feature_id);
    strcat(path, "/properties/status");

    cJSON_AddStringToObject(json, "topic", topic);
    cJSON_AddStringToObject(json, "path", path);
    cJSON_AddStringToObject(json, "value", data);
    
    char* string = malloc(strlen(cJSON_Print(json)));
    strcpy(string, cJSON_Print(json));
    cJSON_Delete(json);
    
    return string;
}

//char * body = '{"topic": "<<dev->policy>>/<<dev->thing_id>>/things/twin/commands/modify",
//  "path": "/features/<<temp_sensor>>/properties/status", 
//  "value": <<false>>}';

//Extraer datos
void callback_resp_parser(char *payload, char *thing_id, char *feature_id, char *data){

    cJSON *json = cJSON_Parse(payload);
    cJSON *thing = cJSON_GetObjectItemCaseSensitive(json, "topic");
    cJSON *feature = cJSON_GetObjectItemCaseSensitive(json, "path");
    cJSON *value = cJSON_GetObjectItemCaseSensitive(json, "value");
    //thing_id = thing->valuestring;
    //feature_id = feature->valuestring;
    strcpy(data, value->valuestring);
    char * token_1 = strtok(thing->valuestring, "/");
    for(int i = 0; i <= 2; i++) {
        if (i == 0){
            token_1 = strtok(NULL, "/");
        }
    }
    strcpy(thing_id, token_1);
    char * token_2 = strtok(feature->valuestring, "/");
    for(int j = 0; j <= 2; j++) {
        if (j == 0){
            token_2 = strtok(NULL, "/");
        }
    }
    strcpy(feature_id, token_2);

    cJSON_Delete(json);

}

//Agrega el correlation
char *cfg_to_send(char *cfg_json, char *correlation_id, char *namespace){
    cJSON *json = cJSON_Parse(cfg_json);
    cJSON *nmsp = cJSON_GetObjectItemCaseSensitive(json, "namespace");

    strcpy(namespace, nmsp->valuestring);

    cJSON_AddStringToObject(json, "correlation_id", correlation_id);

    char *json_data = cJSON_Print(json);

    char *new_cfg_json = malloc(strlen(json_data));
    strcpy(new_cfg_json, json_data);
    return new_cfg_json;
}

//'{"correlation_id": "hola", "namespace":"sensor","features":{"ft_1":{"properties":{"configuration":{"ON":true},"status":{"value":0}}}}}';

//Extrae el thing y el correlation
void payload_extract(char *payload, char *thing_id, char *correlation_id){
    cJSON *json = cJSON_Parse(payload);
    cJSON *thing = cJSON_GetObjectItemCaseSensitive(json, "thing_id");
    cJSON *cor_id = cJSON_GetObjectItemCaseSensitive(json, "correlation_id");
    strcpy(thing_id, thing->valuestring);
    strcpy(correlation_id, cor_id->valuestring);
    cJSON_Delete(json);
}
