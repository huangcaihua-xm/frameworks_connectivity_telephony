/****************************************************************************
 * frameworks/telephony/include/tapi.h
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

#ifndef __TELEPHONY_APIS_H
#define __TELEPHONY_APIS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define MAX_PHONE_NUMBER_LENGTH 80
#define MAX_CALLER_NAME_LENGTH 80
#define MAX_IMEI_STRING_LENGTH 20
#define MAX_OPERATOR_NAME_LENGTH 63
#define MAX_CALL_ID_LENGTH 100

#ifndef CONFIG_ACTIVE_MODEM_COUNT
#define CONFIG_ACTIVE_MODEM_COUNT 1
#endif

#define MAX_MODEM_COUNT 10

/* MCC is always three digits. MNC is either two or three digits */
#define MAX_MCC_LENGTH 3
#define MAX_MNC_LENGTH 3

#define DEFAULT_SLOT_ID 0

/****************************************************************************
 * Public Types
 ****************************************************************************/

typedef enum {
    SLOT_ID_1 = 0,
    SLOT_ID_2,
    SLOT_ID_MAX
} tapi_slot_id;

typedef enum {
    FEATURE_VOICE = 0,
    FEATURE_DATA,
    FEATURE_SMS,
    FEATURE_IMS
} tapi_feature_type;

typedef enum {
    PHONE_IDLE = 0,
    PHONE_RINGING,
    PHONE_OFFHOOK,
} tapi_phone_state;

typedef enum {
    STATE_IN_SERVICE = 0,
    STATE_OUT_OF_SERVICE,
    STATE_EMERGENCY_ONLY,
    STATE_POWER_OFF
} tapi_service_state;

typedef enum {
    UNKNOWN = -1,
    AVAILABLE = 0,
    CURRENTL,
    FORBIDDEN,
} tapi_operator_status;

typedef enum {
    NETWORK_REGISTRATION_STATUS_UNKNOWN = -1,
    NETWORK_REGISTRATION_STATUS_NOT_REGISTERED = 0,
    NETWORK_REGISTRATION_STATUS_REGISTERED = 1,
    NETWORK_REGISTRATION_STATUS_SEARCHING = 2,
    NETWORK_REGISTRATION_STATUS_DENIED = 3,
    NETWORK_REGISTRATION_STATUS_ROAMING = 5,
} tapi_registration_state;

typedef enum {
    NETWORK_ROAMING_UNKNOWN = 0,
    NETWORK_ROAMING_DOMESTIC,
    NETWORK_ROAMING_INTERNATIONAL,
} tapi_roaming_type;

typedef enum {
    NETWORK_SELECTION_UNKNOWN = -1,
    NETWORK_SELECTION_AUTO = 0,
    NETWORK_SELECTION_MANUAL,
} tapi_selection_mode;

typedef enum {
    NETWORK_PREF_NET_TYPE_ANY = 0,
    NETWORK_PREF_NET_TYPE_GSM_ONLY = 1,
    NETWORK_PREF_NET_TYPE_WCDMA_ONLY = 2,
    NETWORK_PREF_NET_TYPE_UMTS = 3,
    NETWORK_PREF_NET_TYPE_LTE_GSM_WCDMA = 9,
    NETWORK_PREF_NET_TYPE_LTE_WCDMA = 12,
    NETWORK_PREF_NET_TYPE_LTE_ONLY = 14,
    NETWORK_PREF_NET_TYPE_LTE_TDSCDMA_GSM = 17,
} tapi_pref_net_mode;

typedef enum {
    NETWORK_TYPE_UNKNOWN = 0,
    NETWORK_TYPE_GPRS = 1,
    NETWORK_TYPE_EDGE = 2,
    NETWORK_TYPE_UMTS = 3,
    NETWORK_TYPE_HSDPA = 8,
    NETWORK_TYPE_HSUPA = 9,
    NETWORK_TYPE_HSPA = 12,
    NETWORK_TYPE_LTE = 13,
    NETWORK_TYPE_LTE_CA = 19,
} tapi_network_type;

typedef enum {
    RADIO_STATE_UNAVAILABLE = 0,
    RADIO_STATE_ON,
    RADIO_STATE_OFF,
    RADIO_STATE_EMERGENCY_ONLY,
} tapi_radio_state;

typedef struct {
    char number[MAX_PHONE_NUMBER_LENGTH];
    int type;
} tapi_phone_number;

typedef struct {
    int msg_id;
    int status;
    int arg1;
    int arg2;
    void* data;
} tapi_async_result;

typedef void (*tapi_async_function)(tapi_async_result* result);

typedef enum {
    // Generic Indication Message
    MSG_RADIO_STATE_CHANGE_IND = 0,
    MSG_PHONE_STATE_CHANGE_IND,

    // Call Indication Message
    MSG_CALL_ADD_MESSAGE_IND,
    MSG_CALL_REMOVE_MESSAGE_IND,
    MSG_CALL_FORWARDED_MESSAGE_IND,
    MSG_CALL_BARRING_ACTIVE_MESSAGE_IND,
    MSG_CALL_PROPERTY_CHANGED_MESSAGE_IND,
    MSG_CALL_DISCONNECTED_REASON_MESSAGE_IND,
    MSG_CALL_MERGE_IND,
    MSG_CALL_SEPERATE_IND,
    MSG_ECC_LIST_CHANGE_IND,

    // Network Indication Message
    MSG_NETWORK_STATE_CHANGE_IND,
    MSG_CELLINFO_CHANGE_IND,
    MSG_SIGNAL_STRENGTH_STATE_CHANGE_IND,
    MSG_NITZ_STATE_CHANGE_IND,

    // Data Indication Message
    MSG_DATA_ENABLED_CHANGE_IND,
    MSG_DATA_NETWORK_TYPE_CHANGE_IND,
    MSG_DATA_CONNECTION_STATE_CHANGE_IND,
    MSG_DEFAULT_DATA_SLOT_CHANGE_IND,

    // SIM Indication Message
    MSG_SIM_STATE_CHANGE_IND,
} tapi_indication_msg;

typedef void* tapi_context;

#include <tapi_call.h>
#include <tapi_data.h>
#include <tapi_manager.h>

#endif /* __TELEPHONY_APIS_H */