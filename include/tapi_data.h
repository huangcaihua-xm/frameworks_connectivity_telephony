/****************************************************************************
 * frameworks/telephony/include/tapi_data.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef TELEPHONY_DATA_H
#define TELEPHONY_DATA_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "tapi.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DATA_TYPE_INTERNET "internet"
#define DATA_TYPE_MMS "mms"
#define DATA_TYPE_IMS "ims"
#define MAX_APN_LIST_CAPACITY 10
#define MAX_APN_DOMAIN_LENGTH 128
#define MAX_IP_INTERFACE_NAME_LENGTH 128
#define MAX_IP_STRING_LENGTH 128
#define MAX_DATA_DNS_COUNT 10
#define MAX_DATA_CALL_LIST_SIZE 10

/****************************************************************************
 * Public Types
 ****************************************************************************/

typedef enum {
    DATA_CONNECTED,
    DATA_CONNECTING,
    DATA_DISCONNECTED,
    DATA_SUSPENDED,
    DATA_DISCONNECTING,
} tapi_data_state;

typedef enum {
    DATA_CONTEXT_TYPE_ANY = 0,
    DATA_CONTEXT_TYPE_INTERNET,
    DATA_CONTEXT_TYPE_HIPRI,
    DATA_CONTEXT_TYPE_SUPL,
    DATA_CONTEXT_TYPE_MMS,
    DATA_CONTEXT_TYPE_WAP,
    DATA_CONTEXT_TYPE_IMS,
    DATA_CONTEXT_TYPE_EMERGENCY,
} tapi_data_context_type;

typedef enum {
    DATA_PROTO_IP = 0,
    DATA_PROTO_IPV6,
    DATA_PROTO_IPV4V6,
} tapi_data_proto;

typedef enum {
    DATA_AUTH_METHOD_CHAP = 0,
    DATA_AUTH_METHOD_PAP,
    DATA_AUTH_METHOD_NONE,
} tapi_data_auth_method;

typedef struct {
    char interface[MAX_IP_INTERFACE_NAME_LENGTH + 1];
    char ip[MAX_IP_STRING_LENGTH + 1];
    char gateway[MAX_IP_STRING_LENGTH + 1];
    char* dns[MAX_DATA_DNS_COUNT];
    char proxy[MAX_IP_STRING_LENGTH + 1];
    char pcscf[MAX_IP_STRING_LENGTH + 1];
} tapi_ipv4_settings;

typedef struct {
    char interface[MAX_IP_INTERFACE_NAME_LENGTH + 1];
    char ip[MAX_IP_STRING_LENGTH + 1];
    char gateway[MAX_IP_STRING_LENGTH + 1];
    char* dns[MAX_DATA_DNS_COUNT];
    char pcscf[MAX_IP_STRING_LENGTH + 1];
} tapi_ipv6_settings;

typedef struct {
    tapi_ipv4_settings* ipv4;
    tapi_ipv6_settings* ipv6;
    unsigned int mtu;
} tapi_ip_settings;

typedef struct {
    char* id;
    char name[MAX_APN_DOMAIN_LENGTH + 1];
    tapi_data_context_type type;
    bool active;
    bool preferred;
    char username[MAX_APN_DOMAIN_LENGTH + 1];
    char password[MAX_APN_DOMAIN_LENGTH + 1];
    char accesspointname[MAX_APN_DOMAIN_LENGTH + 1];
    char messageproxy[MAX_APN_DOMAIN_LENGTH + 1];
    char messagecenter[MAX_APN_DOMAIN_LENGTH + 1];
    tapi_data_proto protocol;
    tapi_data_auth_method auth_method;
    tapi_ip_settings* ip_settings;
} tapi_data_context;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load Apn List from Apn Storage.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_load_apn_contexts(tapi_context context,
    int slot_id, int event_id, tapi_async_function p_handle);

/**
 * Add Apn to Apn Storage.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] apn            Apn item to save.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_add_apn_context(tapi_context context,
    int slot_id, int event_id, tapi_data_context* apn, tapi_async_function p_handle);

/**
 * Remove Apn Item from Apn Storage.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] apn            Apn item to remove.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_remove_apn_context(tapi_context context,
    int slot_id, int event_id, tapi_data_context* apn, tapi_async_function p_handle);

/**
 * Edit Apn in Apn Storage.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] apn            Apn item to edit.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_edit_apn_context(tapi_context context,
    int slot_id, int event_id, tapi_data_context* apn, tapi_async_function p_handle);

/**
 * Reset Apn Storage.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_reset_apn_contexts(tapi_context context,
    int slot_id, int event_id, tapi_async_function p_handle);

/**
 * Check if Packet switched domain is registered or not.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[out] out           Return value.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_is_registered(tapi_context context, int slot_id, bool* out);

/**
 * Check if Packet switched domain is emergency only.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[out] out           Return value.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_is_data_emergency_only(tapi_context context, int slot_id, bool* out);

/**
 * Get radio tech in Packet switched domain.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[out] out           Return value.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_get_network_type(tapi_context context, int slot_id, tapi_network_type* out);

/**
 * Check if roaming in Packet switched domain.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[out] out           Return value.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_is_data_roaming(tapi_context context, int slot_id, bool* out);

/**
 * Request network per APN type.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] type          Apn type.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_request_network(tapi_context context, int slot_id, const char* type);

/**
 * Release network per APN type.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] type          Apn type.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_release_network(tapi_context context, int slot_id, const char* type);

/**
 * Get active data connection list.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_get_data_connection_list(tapi_context context, int slot_id, int event_id,
    tapi_async_function p_handle);

/**
 * Set preferred apn for internet.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] apn            Apn item.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_set_preferred_apn(tapi_context context, int slot_id, tapi_data_context* apn);

/**
 * Get preferred apn.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[out] out           Pointer to Id of Preferred Apn item.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_get_preferred_apn(tapi_context context, int slot_id, char** out);

/**
 * Switch data on or off.
 * @param[in] context        Telephony api context.
 * @param[in] enabled        Data switch status.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_enable_data(tapi_context context, bool enabled);

/**
 * Get data switch status.
 * @param[in] context        Telephony api context.
 * @param[out] out           Data switch status.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_get_enabled(tapi_context context, bool* out);

/**
 * Switch data roaming on or off.
 * @param[in] context        Telephony api context.
 * @param[in] enabled        Data roaming switch status.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_enable_roaming(tapi_context context, bool enabled);

/**
 * Get data roaming switch status.
 * @param[in] context        Telephony api context.
 * @param[out] out           Data roaming switch status.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_get_roaming_enabled(tapi_context context, bool* out);

/**
 * Set default data slot id.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_set_default_slot(tapi_context context, int slot_id);

/**
 * Get default data slot id.
 * @param[in] context        Telephony api context.
 * @param[out] out        Slot id of current sim.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_get_default_slot(tapi_context context, int* out);

/**
 * Set data allow in given slot id.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] allowed        Data allowed status in given slot.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_set_data_allow(tapi_context context, int slot_id,
    int event_id, bool allowed, tapi_async_function p_handle);

/**
 * Register data event callback.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] msg            Radio event ID.
 * @param[in] user_obj       User data.
 * @param[in] p_handle       Event callback.
 * @return Positive value as watch_id on success; a negated errno value on failure.
 */
int tapi_data_register(tapi_context context,
    int slot_id, tapi_indication_msg msg, void* user_obj, tapi_async_function p_handle);

/**
 * Unregister data event callback.
 * @param[in] context        Telephony api context.
 * @param[in] watch_id       Watch id.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_data_unregister(tapi_context context, int watch_id);

#ifdef __cplusplus
}
#endif

#endif /* TELEPHONY_DATA_H */