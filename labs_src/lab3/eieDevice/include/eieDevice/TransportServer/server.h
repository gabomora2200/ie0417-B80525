#ifndef SERVER_H
#define SERVER_H


/* Includes
 * This is the list of includes need in command
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <czmq.h>


#include "eieDevice/CommandManager/command_manager.h"


/**
 * Struct to request a command.
 *
 * @param cmd_name Command name.
 * @param payload_size Command payload size.
 * @param payload Data itself.
 *
 * @return Request a command
 */
struct cmd_request{
    char cmd_name[100]; /*!< Command Name */ 
    uint32_t payload_size; /*!< Payload size */
    char payload; /*!< Payload (Binary Buffer) */
};

/**
 * Struct to request to final command.
 *
 * @param cmd_name Command name.
 * @param payload_size Command payload size.
 * @param payload Data itself.
 *
 * @return Request a command
 */
typedef struct cmd_final_request
{
    char * cmd_name; /*!< Command Name */ 
    uint32_t payload_size; /*!< Payload size */
    char * payload; /*!< Payload (Binary Buffer) */
}cmd_final_request;



/* Server thread data */
struct server_data {
    pthread_t tid;
    zsock_t *server;
};

/**
 * Function to request method from server 
 * 
 * @param arg Pointer to server data
 * @return void* 
 */
void* server_fn(void *);


/**
 * Function to request final command.
 *
 * @param cmd_request Command request struct.
 *
 * @return Returns a Command
 */
cmd_final_request * process_request(struct cmd_request *);

#endif // SERVER_H