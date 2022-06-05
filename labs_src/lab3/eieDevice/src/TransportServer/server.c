#include "eieDevice/TransportServer/server.h"

#include "string.h"



void* server_fn(void *arg){
    // int ret;
    struct server_data *rdata = arg;
    printf("Thread %ld started\n", rdata->tid);

    rdata->server = zsock_new(ZMQ_REP);
    zsock_bind(rdata->server, "tcp://*:5555");

    while(!zsys_interrupted){
        int ret;
        zframe_t *req_frame, *rep_frame;
        struct cmd_request *req;
        struct rep_cmd_message *rep;

        req_frame = zframe_recv(rdata->server);
        if (!req_frame) {
            fprintf(stderr, "req_frame is NULL\n");

            zsock_destroy(&rdata->server);
            zsys_interrupted = 1;
            printf("Thread %ld finished\n", rdata->tid);
            return NULL;
        }

        req = (struct cmd_request *)zframe_data(req_frame);

        cmd_final_request * final_req = process_request(req);

        printf("comand: '%s'\n", final_req->cmd_name);
        printf("Payload size: %d\n", final_req->payload_size);
        printf("Payload: '%s'\n\n", final_req->payload);
        

       // Execute the command manager


        rep_frame = zframe_new(NULL, sizeof(struct rep_cmd_message));
        rep = (struct rep_cmd_message *)zframe_data(rep_frame);

        rep->response = req->payload_size;

        // No longer need request frame
        zframe_destroy(&req_frame);
        
        // Sending destroys the response frame
        ret = zframe_send(&rep_frame, rdata->server, 0);
        if (ret) {
            fprintf(stderr, "Failed to send msg with: %d\n", ret);

            zsock_destroy(&rdata->server);
            zsys_interrupted = 1;
            printf("Thread %ld finished\n", rdata->tid);
            return NULL;
        }
    }
    return NULL;
}


cmd_final_request * process_request(struct cmd_request *request){

    cmd_final_request *final_req = 
                malloc(sizeof(char[100]) + sizeof(uint32_t) + sizeof(char *));
    
    // final_req->cmd_name = *request->cmd_name;
    strcpy(final_req->cmd_name, request->cmd_name);
    final_req->payload_size = request->payload_size;

    final_req->payload = &request->payload;
    
    // Precessing the payload data
    char * temp_ptr = final_req->payload;
    while(*temp_ptr != '\0'){
        if(*temp_ptr == '}') {
            char * p = temp_ptr+1;
            *p = '\0';
        }
        temp_ptr++;
    }

    return final_req;
}