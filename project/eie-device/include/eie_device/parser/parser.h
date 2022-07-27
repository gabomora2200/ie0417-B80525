#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <eie_device/eie_device.h>

char *update_feature_parser(char *thing_id, char *policy, char *feature_id, char *data);

void callback_resp_parser(char *payload, char *thing_id, char *feature_id, char *data);

char *cfg_to_send(char *cfg_json, char *correlation_id, char *namespace);

void payload_extract(char *payload, char *thing_id, char *correlation_id);

#ifdef __cplusplus
}
#endif

#endif //PARSER_H