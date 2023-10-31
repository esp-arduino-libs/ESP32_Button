/*
 * SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BUTTON_H
#define BUTTON_H
#include "original/iot_button.h"
#include "original/arduino_config.h"

// Define a function pointer type for callbacks
typedef void (*callbackFunction)(void *button_handle, void *usr_data);

// Define the Button class
class Button {
public:
    // Constructors for gpio button
    Button(gpio_num_t pin, bool pullup);

    // Constructors for gpio button
    Button(gpio_num_t pin, bool pullup, uint8_t adc_channel, uint8_t button_index, uint16_t min, uint16_t max);

    /*Attach Methods*/
    void attachPressDownEventCb(callbackFunction newFunction, void *usr_data);
    void attachPressUpEventCb(callbackFunction newFunction, void *usr_data);
    void attachPressRepeatEventCb(callbackFunction newFunction, void *usr_data);
    void attachSingleClickEventCb(callbackFunction newFunction, void *usr_data);
    void attachDoubleClickEventCb(callbackFunction newFunction, void *usr_data);
    void attachLongPressStartEventCb(callbackFunction newFunction, void *usr_data);
    void attachLongPressHoldEventCb(callbackFunction newFunction, void *usr_data);
    void attachPressRepeatDoneEventCb(callbackFunction newFunction, void *usr_data);
    void attachLongPressUpEventCb(callbackFunction newFunction, void *usr_data);
    void attachButtonNonePressEventCb(callbackFunction newFunction, void *usr_data);
    void attachMultipleClickEventCb(callbackFunction newFunction, int clicks, void *usr_data);

    /*Detach Methods*/
    void detachPressDownEvent(void);
    void detachPressUpEvent(void);
    void detachPressRepeatEvent(void);
    void detachSingleClickEvent(void);
    void detachDoubleClickEvent(void);
    void detachLongPressStartEvent(void);
    void detachLongPressHoldEvent(void);
    void detachPressRepeatDoneEvent(void);
    void detachLongPressUpEvent(void);

    /*Unregister Methods*/
    void unregisterPressDownEventCb(callbackFunction newFunction);
    void unregisterPressUpEventCb(callbackFunction newFunction);
    void unregisterPressRepeatEventCb(callbackFunction newFunction);
    void unregisterSingleClickEventCb(callbackFunction newFunction);
    void unregisterDoubleClickEventCb(callbackFunction newFunction);
    void unregisterLongPressStartEventCb(callbackFunction newFunction);
    void unregisterLongPressHoldEventCb(callbackFunction newFunction);
    void unregisterPressRepeatDoneEventCb(callbackFunction newFunction);
    void unregisterLongPressUpEventCb(callbackFunction newFunction);
    void unregisterButtonNonePressEventCb(callbackFunction newFunction);
    void unregisterMultiClickEventCb(callbackFunction newFunction, int clicks);

    // Other methods
    void del(void);
    int countCallBack(void);
    int countEvent(button_event_t event);
    int getEvent(void);
    int getRepeat(void);
    int getTickTime(void);
    int getLongPressHoldCount(void);
    void setParam(button_param_t param, void *value);
    void resume(void);
    void stop(void);

private:
    // Private variables
    gpio_num_t _button_pin;
    button_handle_t _handle;
};

#endif
