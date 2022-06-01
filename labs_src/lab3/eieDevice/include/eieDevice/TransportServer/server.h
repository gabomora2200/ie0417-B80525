#ifndef SERVER_H
#define SERVER_H


/* Includes
 * This is the list of includes need in transport_server
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <czmq.h>


/**
 * @brief This Struct is the command header, before processing
 * 
 */
struct cmd_request{
    char cmd_name[100]; /*!< Command Name */ 
    uint32_t payload_size; /*!< Payload size */
    char payload; /*!< Payload (Binary Buffer) */
};

/**
 * @brief This Struct is the command header, after processing
 * 
 */
typedef struct cmd_final_request
{
    char cmd_name[100]; /*!< Command Name */ 
    uint32_t payload_size; /*!< Payload size */
    char * payload; /*!< Payload (Binary Buffer) */
}cmd_final_request;




struct rep_cmd_message{
    uint32_t response;
};

struct rep_cmd_ping_pong{
    
};


/* Server thread data */
struct server_data {
    pthread_t tid;
    zsock_t *server;
};

/**
 * @brief Server function, implements the logic for 
 * receive and response requests
 * 
 * @param arg 
 * @return void* 
 */
void* server_fn(void *);


/**
 * @brief Process the request and return a struct pointer to the request data;
 * 
 * @return cmd_final_request* 
 */
cmd_final_request * process_request(struct cmd_request *);

#endif // SERVER_H