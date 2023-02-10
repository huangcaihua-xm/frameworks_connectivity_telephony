/*
 * Copyright (C) 2023 Xiaomi Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <dbus/dbus.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tapi_internal.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

const char* tapi_pref_network_mode_to_string(tapi_pref_net_mode mode)
{
    switch (mode) {
    case NETWORK_PREF_NET_TYPE_ANY:
        return "any";
    case NETWORK_PREF_NET_TYPE_GSM_ONLY:
        return "gsm";
    case NETWORK_PREF_NET_TYPE_WCDMA_ONLY:
        return "umts";
    case NETWORK_PREF_NET_TYPE_LTE_ONLY:
        return "lte";
    case NETWORK_PREF_NET_TYPE_UMTS:
        return "umts,gsm";
    case NETWORK_PREF_NET_TYPE_LTE_WCDMA:
        return "lte,umts";
    case NETWORK_PREF_NET_TYPE_LTE_TDSCDMA_GSM:
        return "lte,gsm";
    case NETWORK_PREF_NET_TYPE_LTE_GSM_WCDMA:
        return "lte,umts,gsm";
    }

    return NULL;
}

bool tapi_pref_network_mode_from_string(const char* str, tapi_pref_net_mode* mode)
{
    if (str == NULL) {
        *mode = NETWORK_PREF_NET_TYPE_ANY;
        return false;
    }

    if (strcmp(str, "any") == 0) {
        *mode = NETWORK_PREF_NET_TYPE_ANY;
        return true;
    } else if (strcmp(str, "gsm") == 0) {
        *mode = NETWORK_PREF_NET_TYPE_GSM_ONLY;
        return true;
    } else if (strcmp(str, "umts") == 0) {
        *mode = NETWORK_PREF_NET_TYPE_WCDMA_ONLY;
        return true;
    } else if (strcmp(str, "lte") == 0) {
        *mode = NETWORK_PREF_NET_TYPE_LTE_ONLY;
        return true;
    } else if (strcmp(str, "umts,gsm") == 0) {
        *mode = NETWORK_PREF_NET_TYPE_UMTS;
        return true;
    } else if (strcmp(str, "lte,umts") == 0) {
        *mode = NETWORK_PREF_NET_TYPE_LTE_WCDMA;
        return true;
    } else if (strcmp(str, "lte,gsm") == 0) {
        *mode = NETWORK_PREF_NET_TYPE_LTE_TDSCDMA_GSM;
        return true;
    } else if (strcmp(str, "lte,umts,gsm") == 0) {
        *mode = NETWORK_PREF_NET_TYPE_LTE_GSM_WCDMA;
        return true;
    } else {
        *mode = NETWORK_PREF_NET_TYPE_ANY;
    }

    return false;
}

bool tapi_network_type_from_string(const char* str, tapi_network_type* type)
{
    if (str == NULL)
        return false;

    if (strcmp(str, "gsm") == 0) {
        *type = NETWORK_TYPE_EDGE;
        return true;
    } else if (strcmp(str, "umts") == 0) {
        *type = NETWORK_TYPE_UMTS;
        return true;
    } else if (strcmp(str, "lte") == 0) {
        *type = NETWORK_TYPE_LTE;
        return true;
    } else if (strcmp(str, "hsdpa") == 0) {
        *type = NETWORK_TYPE_HSDPA;
        return true;
    } else if (strcmp(str, "hspa") == 0) {
        *type = NETWORK_TYPE_HSPA;
        return true;
    } else if (strcmp(str, "hsupa") == 0) {
        *type = NETWORK_TYPE_HSUPA;
        return true;
    } else if (strcmp(str, "lte_ca") == 0) {
        *type = NETWORK_TYPE_LTE_CA;
        return true;
    } else {
        *type = NETWORK_TYPE_UNKNOWN;
    }

    return false;
}

const char* tapi_registration_status_to_string(int status)
{
    switch (status) {
    case NETWORK_REGISTRATION_STATUS_NOT_REGISTERED:
        return "unregistered";
    case NETWORK_REGISTRATION_STATUS_REGISTERED:
        return "registered";
    case NETWORK_REGISTRATION_STATUS_SEARCHING:
        return "searching";
    case NETWORK_REGISTRATION_STATUS_DENIED:
        return "denied";
    case NETWORK_REGISTRATION_STATUS_UNKNOWN:
        return "unknown";
    case NETWORK_REGISTRATION_STATUS_ROAMING:
        return "roaming";
    }

    return "";
}

int tapi_registration_status_from_string(char* status)
{
    if (status == NULL)
        return NETWORK_REGISTRATION_STATUS_UNKNOWN;

    if (strcmp(status, "unregistered") == 0) {
        return NETWORK_REGISTRATION_STATUS_NOT_REGISTERED;
    } else if (strcmp(status, "registered") == 0) {
        return NETWORK_REGISTRATION_STATUS_REGISTERED;
    } else if (strcmp(status, "searching") == 0) {
        return NETWORK_REGISTRATION_STATUS_SEARCHING;
    } else if (strcmp(status, "denied") == 0) {
        return NETWORK_REGISTRATION_STATUS_DENIED;
    } else if (strcmp(status, "unknown") == 0) {
        return NETWORK_REGISTRATION_STATUS_UNKNOWN;
    } else if (strcmp(status, "roaming") == 0) {
        return NETWORK_REGISTRATION_STATUS_ROAMING;
    }

    return NETWORK_REGISTRATION_STATUS_UNKNOWN;
}

int tapi_registration_mode_from_string(char* mode)
{
    if (mode == NULL)
        return NETWORK_SELECTION_UNKNOWN;

    if (strcmp(mode, "auto") == 0) {
        return NETWORK_SELECTION_AUTO;
    } else if (strcmp(mode, "manual") == 0) {
        return NETWORK_SELECTION_MANUAL;
    }

    return NETWORK_SELECTION_UNKNOWN;
}

int tapi_operator_status_from_string(char* mode)
{
    if (mode == NULL)
        return UNKNOWN;

    if (strcmp(mode, "current") == 0) {
        return CURRENTL;
    } else if (strcmp(mode, "available") == 0) {
        return AVAILABLE;
    } else if (strcmp(mode, "forbidden") == 0) {
        return FORBIDDEN;
    }

    return UNKNOWN;
}

const char* tapi_get_call_signal_member(tapi_indication_msg msg)
{
    int msg_id = msg;

    switch (msg_id) {
    case MSG_CALL_ADD_MESSAGE_IND:
        return "CallAdded";
    case MSG_CALL_REMOVE_MESSAGE_IND:
        return "CallRemoved";
    case MSG_CALL_FORWARDED_MESSAGE_IND:
        return "Forwarded";
    case MSG_CALL_BARRING_ACTIVE_MESSAGE_IND:
        return "BarringActive";
    case MSG_CALL_PROPERTY_CHANGED_MESSAGE_IND:
        return "PropertyChanged";
    case MSG_CALL_DISCONNECTED_REASON_MESSAGE_IND:
        return "DisconnectReason";
    case MSG_ECC_LIST_CHANGE_IND:
        return "PropertyChanged";
    }

    return NULL;
}

char* tapi_utils_get_modem_path(int slot_id)
{
    switch (slot_id) {
    case SLOT_ID_1:
#ifdef CONFIG_MODEM_PATH_1
        return CONFIG_MODEM_PATH_1;
#else
        return CONFIG_MODEM_PATH;
#endif
    case SLOT_ID_2:
#ifdef CONFIG_MODEM_PATH_2
        return CONFIG_MODEM_PATH_2;
#endif
    default:
        break;
    }

    return NULL;
}

enum tapi_call_status tapi_call_string_to_status(char* str_status)
{
    enum tapi_call_status ret = CALL_STATUS_UNKNOW;

    if (str_status == NULL)
        return CALL_STATUS_UNKNOW;

    if (strcmp(str_status, "active") == 0) {
        ret = CALL_STATUS_ACTIVE;
    } else if (strcmp(str_status, "held") == 0) {
        ret = CALL_STATUS_HELD;
    } else if (strcmp(str_status, "dialing") == 0) {
        ret = CALL_STATUS_DIALING;
    } else if (strcmp(str_status, "alerting") == 0) {
        ret = CALL_STATUS_ALERTING;
    } else if (strcmp(str_status, "incoming") == 0) {
        ret = CALL_STATUS_INCOMING;
    } else if (strcmp(str_status, "waiting") == 0) {
        ret = CALL_STATUS_WAITING;
    } else if (strcmp(str_status, "disconnected") == 0) {
        ret = CALL_STATUS_DISCONNECTED;
    }

    return ret;
}

const char* tapi_apn_context_type_to_string(tapi_apn_context_type type)
{
    switch (type) {
    case APN_CONTEXT_TYPE_ANY:
        return NULL;
    case APN_CONTEXT_TYPE_INTERNET:
        return "internet";
    case APN_CONTEXT_TYPE_MMS:
        return "mms";
    case APN_CONTEXT_TYPE_WAP:
        return "wap";
    case APN_CONTEXT_TYPE_IMS:
        return "ims";
    }

    return NULL;
}

tapi_apn_context_type tapi_apn_context_type_from_string(const char* type)
{
    if (type == NULL)
        return APN_CONTEXT_TYPE_ANY;

    if (strcmp(type, "internet") == 0)
        return APN_CONTEXT_TYPE_INTERNET;
    else if (strcmp(type, "mms") == 0)
        return APN_CONTEXT_TYPE_MMS;
    else if (strcmp(type, "wap") == 0)
        return APN_CONTEXT_TYPE_WAP;
    else if (strcmp(type, "ims") == 0)
        return APN_CONTEXT_TYPE_IMS;

    return APN_CONTEXT_TYPE_ANY;
}

const char* tapi_apn_auth_method_to_string(tapi_data_auth_method auth)
{
    switch (auth) {
    case DATA_AUTH_METHOD_CHAP:
        return "chap";
    case DATA_AUTH_METHOD_PAP:
        return "pap";
    case DATA_AUTH_METHOD_NONE:
        return "none";
    };

    return NULL;
}

tapi_data_auth_method tapi_apn_auth_method_from_string(const char* auth)
{
    if (auth == NULL)
        return DATA_AUTH_METHOD_NONE;

    if (strcmp(auth, "chap") == 0)
        return DATA_AUTH_METHOD_CHAP;
    else if (strcmp(auth, "pap") == 0)
        return DATA_AUTH_METHOD_PAP;
    else if (strcmp(auth, "none") != 0)
        return DATA_AUTH_METHOD_NONE;

    return DATA_AUTH_METHOD_NONE;
}

const char* tapi_apn_proto_to_string(tapi_data_proto proto)
{
    switch (proto) {
    case DATA_PROTO_IP:
        return "ip";
    case DATA_PROTO_IPV6:
        return "ipv6";
    case DATA_PROTO_IPV4V6:
        return "dual";
    };

    return NULL;
}

bool tapi_apn_proto_from_string(const char* str, tapi_data_proto* proto)
{
    if (str == NULL)
        return false;

    if (strcmp(str, "ip") == 0) {
        *proto = DATA_PROTO_IP;
        return true;
    } else if (strcmp(str, "ipv6") == 0) {
        *proto = DATA_PROTO_IPV6;
        return true;
    } else if (strcmp(str, "dual") == 0) {
        *proto = DATA_PROTO_IPV4V6;
        return true;
    }

    return false;
}

bool tapi_is_call_signal_message(DBusMessage* message, DBusMessageIter* iter, int msg_type)
{
    bool ret = false;

    if (!dbus_message_iter_init(message, iter))
        tapi_log_error("manager_call_signal Message Has no Param");
    else if (dbus_message_iter_get_arg_type(iter) != msg_type)
        tapi_log_error("manager_call_signal Param is not object");
    else
        ret = true;

    return ret;
}

tapi_call_list* tapi_add_call_to_list(tapi_call_list* head, tapi_call_info* new_val)
{
    tapi_call_list* current;
    tapi_call_list* new_list_node = malloc(sizeof(tapi_call_list));
    if (new_list_node == NULL) {
        return NULL;
    }

    new_list_node->data = new_val;
    new_list_node->next = NULL;

    if (head == NULL) {
        head = new_list_node;
        return head;
    }

    current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_list_node;

    return head;
}

unsigned int tapi_get_call_count(tapi_call_list* First)
{
    int count = 0;

    for (tapi_call_list* p = First; p != NULL; p = p->next)
        count++;

    return count;
}

int tapi_get_call_by_state(tapi_call_list* pfirst, int state, tapi_call_info* val)
{
    int ret = 0;

    for (tapi_call_list* p = pfirst; p != NULL; p = p->next) {
        if (p->data->state == state) {
            memcpy(val, p->data, sizeof(tapi_call_info));
            ret++;
            break;
        }
    }

    return ret;
}

void tapi_free_call_list(tapi_call_list* head)
{
    tapi_call_list* current;
    tapi_call_list* del;

    current = head;
    while (current != NULL) {
        del = current;
        current = current->next;
        free(del->data);
        free(del);
    }

    head = NULL;
}