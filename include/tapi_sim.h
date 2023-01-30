/****************************************************************************
 * frameworks/telephony/include/tapi_sim.h
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

#ifndef __TELEPHONY_SIM_H
#define __TELEPHONY_SIM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "tapi.h"

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Whether an ICC card is present for a subscription.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[out] out           State of Icc card.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_sim_has_icc_card(tapi_context context, int slot_id, bool* out);

/**
 * Get the MCC+MNC (mobile country code + mobile network code) of the
 * provider of the SIM. 5 or 6 decimal digits.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] length         Length of out param.
 * @param[out] out           Operator returned from ICC.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_sim_get_sim_operator(tapi_context context, int slot_id, int length, char* out);

/**
 * Get the Service Provider Name (SPN).
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[out] out           SimOperatorName returned from ICC.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_sim_get_sim_operator_name(tapi_context context, int slot_id, char** out);

/**
 * Get the sim serial number for the given subscription, if applicable.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[out] out           Sim serial number returned from ICC.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_sim_get_sim_iccid(tapi_context context, int slot_id, char** out);

/**
 * Register sim state changed event callback.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] p_handle       Event callback.
 * @return Positive value as watch_id on success; a negated errno value on failure.
 */
int tapi_sim_register_sim_state_change(tapi_context context,
    int slot_id, tapi_async_function p_handle);

/**
 * Unregister sim state changed event callback.
 * @param[in] context        Telephony api context.
 * @param[in] watch_id       Watch id.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_sim_unregister_sim_state_change(tapi_context context, int watch_id);

/**
 * Change the ICC password used in ICC pin lock or ICC fdn enable.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] pin_type       Supported by two types "pin" or "pin2".
 * @param[in] old_pin        Old pin value.
 * @param[in] new_pin        New pin value.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_sim_change_pin(tapi_context context, int slot_id,
    int event_id, char* pin_type, char* old_pin, char* new_pin, tapi_async_function p_handle);

/**
 * Enters the currently pending pin.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] pin_type       Supported by two types "pin" or "pin2".
 * @param[in] pin            Pin value.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_sim_enter_pin(tapi_context context, int slot_id,
    int event_id, char* pin_type, char* pin, tapi_async_function p_handle);

/**
 * Provides the unblock key to the modem and if correct
 * resets the pin to the new value of newpin.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] puk_type       Supported by two types "puk" or "puk2".
 * @param[in] puk            Puk value.
 * @param[in] new_pin        New pin value.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_sim_reset_pin(tapi_context context, int slot_id,
    int event_id, char* puk_type, char* puk, char* new_pin, tapi_async_function p_handle);

/**
 * Activates the lock for the particular pin type. The
 * device will ask for a PIN automatically next time the
 * device is turned on or the SIM is removed and
 * re-inserted. The current PIN is required for the
 * operation to succeed.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] pin_type       Supported by "pin". "pin2" is not supported according to 27.007.
 * @param[in] pin            Pin value.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_sim_lock_pin(tapi_context context, int slot_id,
    int event_id, char* pin_type, char* pin, tapi_async_function p_handle);

/**
 * Deactivates the lock for the particular pin type. The
 * current PIN is required for the operation to succeed.
 * @param[in] context        Telephony api context.
 * @param[in] slot_id        Slot id of current sim.
 * @param[in] event_id       Async event identifier.
 * @param[in] pin_type       Supported by "pin". "pin2" is not supported according to 27.007.
 * @param[in] pin            Pin value.
 * @param[in] p_handle       Event callback.
 * @return Zero on success; a negated errno value on failure.
 */
int tapi_sim_unlock_pin(tapi_context context, int slot_id,
    int event_id, char* pin_type, char* pin, tapi_async_function p_handle);

#ifdef __cplusplus
}
#endif

#endif /* __TELEPHONY_SIM_H */