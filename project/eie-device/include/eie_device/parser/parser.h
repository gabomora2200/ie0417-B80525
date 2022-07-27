#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <eie_device/eie_device.h>

/**
 * @brief 
 * 
 * @param thing_id 
 * @param policy 
 * @param feature_id 
 * @param data 
 * @return char* 
 */
char *update_feature_parser(char *thing_id, char *policy, char *feature_id, char *data);

/**
 * @brief 
 * 
 * @param payload 
 * @param thing_id 
 * @param feature_id 
 * @param data 
 */
void callback_resp_parser(char *payload, char *thing_id, char *feature_id, char *data);

/**
 * @brief 
 * 
 * @param cfg_json 
 * @param correlation_id 
 * @param namespace 
 * @return char* 
 */
char *cfg_to_send(char *cfg_json, char *correlation_id, char *namespaces);

/**
 * @brief 
 * 
 * @param payload 
 * @param thing_id 
 * @param correlation_id 
 */
void payload_extract(char *payload, char *thing_id, char *correlation_id);

#ifdef __cplusplus
}
#endif

#endif //PARSER_H