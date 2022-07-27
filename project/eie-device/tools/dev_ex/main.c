#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <linux/limits.h>
#include <time.h>

#include "eie_device/eie_device.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                    

void config_clbk1(char *payload, int payloadlen){
    printf("From config callback\nPayload is: %s\n", payload);
}

int main(int argc, char **argv) {
    eie_status ret = OK;
    char cfg_json[] = "{\"namespace\":\"sensor\",\"features\":{\"ft_1\":{\"properties\":{\"configuration\":{\"ON\":true},\"status\":{\"value\":0}}},\"ft_2\":{\"properties\":{\"configuration\":{\"ON\":true},\"status\":{\"value\":0}}}}}";
    // char data_update[] = "{\"value\":9}";

    struct device * dev = eie_device_create(cfg_json);

    if(dev == NULL){
        printf("Error: device is null\n");
    }

    eie_callback_execute_t clbkfn = (eie_callback_execute_t)config_clbk1;
    ret = eie_device_register_callback(dev, "ft_1", clbkfn);
    if(ret == ERROR){
        printf("Error: impossible to register callback\n");
    }

    ret = eie_device_register_callback(dev, "ft_2", clbkfn);
    if(ret == ERROR){
        printf("Error: impossible to register callback\n");
    }

    for(int i= 0; i<10; i++){
        int x = rand();
        int length = snprintf( NULL, 0, "%d", x );
        char *value = (char *)malloc( length + 1 );
        snprintf( value, length + 1, "%d", x );

        char data_update_2[] = "{\"value\":";
        char data_to_send[100];

        strcpy(data_to_send, data_update_2);
        strcat(data_to_send, value);
        strcat(data_to_send, "}");

        ret = eie_device_update_feature(dev, "ft_1", data_to_send);
        if(ret == ERROR){
            printf("Error: impossible to update feature\n");
        }

        sleep(5);

        x = rand();
        length = snprintf( NULL, 0, "%d", x );
        value = (char *)malloc( length + 1 );
        snprintf( value, length + 1, "%d", x );

        char data_to_send_2[100];

        strcpy(data_to_send_2, data_update_2);
        strcat(data_to_send_2, value);
        strcat(data_to_send_2, "}");

        ret = eie_device_update_feature(dev, "ft_2", data_to_send_2);
        if(ret == ERROR){
            printf("Error: impossible to update feature\n");
        }
        
        sleep(5);

    }

    

    ret = eie_device_destroy(dev);
    if(ret == ERROR){
        printf("Error: impossible to destroy device\n");
    }
    return ret;
}