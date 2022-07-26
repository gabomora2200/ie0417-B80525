#ifndef PARSER_H
#define PARSER_H

#include <eie_device/eie_device.h>


char *update_feature_parser(char *thing_id, char *policy, char *feature_id, char *data);

void callback_resp_parser(char *payload, char *thing_id, char *feature_id, char *data);

char *cfg_to_send(char *cfg_json, char *correlation_id, char *namespace);

void payload_extract(char *payload, char *thing_id, char *correlation_id);

#endif //PARSER_H