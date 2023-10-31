/*
 * SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_log.h"
#include "original/button_gpio.h"
#include "original/button_adc.h"
#include "original/iot_button.h"
#include "Button.h"

static const char *TAG = "arduino-button";

#define CHECK_ESP_ERROR(result, message) \
    if (result != ESP_OK) { \
        ESP_LOGE(TAG, "%s(%d): %s, Error Code: %d", __FUNCTION__, __LINE__, message, result); \
    }

// Constructor for button using GPIO pin
Button::Button(gpio_num_t pin, bool pullup)
{
    _button_pin = pin;

    // Set pin mode based on pullup parameter
    gpio_set_pull_mode(_button_pin, pullup ? GPIO_PULLUP_ONLY : GPIO_PULLDOWN_ONLY);


    // Configure button using GPIO
    button_config_t cfg = {
        .type = BUTTON_TYPE_GPIO, // Set button type as GPIO
        .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS, // Set long press time
        .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS, // Set short press time
        .gpio_button_config = {
            .gpio_num = pin, // Set GPIO pin number
            .active_level = pullup // Set active level based on pullup parameter
        }
    };
    _handle = iot_button_create(&cfg);
    // Print button created message for debugging purposes
    ESP_LOGI(TAG, "Button created");
}

// Constructor for button using ADC pin
Button::Button(gpio_num_t pin, bool pullup, uint8_t adc_channel, uint8_t button_index, uint16_t min, uint16_t max)
{
    _button_pin = pin;

    // Set pin mode based on pullup parameter
    gpio_set_pull_mode(_button_pin, pullup ? GPIO_PULLUP_ONLY : GPIO_PULLDOWN_ONLY);

    // Configure button using ADC
    button_config_t cfg = {
        .type = BUTTON_TYPE_ADC, // Set button type as ADC
        .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS, // Set long press time
        .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS, // Set short press time
        .adc_button_config = {
            .adc_channel = adc_channel, // Set ADC channel
            .button_index = button_index, // Set button index
            .min = min, // Set minimum ADC reading
            .max = max, // Set maximum ADC reading
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
            .adc_handle = NULL           /**< handle of adc unit, if NULL will create new one internal, else will use the handle */
#endif
        }
    };
    // Create button handle
    _handle = iot_button_create(&cfg);
    // Print button created message for debugging purposes
    ESP_LOGI(TAG, "Button created");
}

/* 0. Button Press Down*/

// Method to attach callback function for button press down event
void Button::attachPressDownEventCb(callbackFunction newFunction, void *usr_data)
{
    if (newFunction == NULL) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    CHECK_ESP_ERROR(iot_button_register_cb(_handle, BUTTON_PRESS_DOWN, newFunction, usr_data), "attach callback fail");
}
// Method to unregister button press down event
void Button::unregisterPressDownEventCb(callbackFunction newFunction)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }
    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_PRESS_DOWN;
    CHECK_ESP_ERROR(iot_button_unregister_event(_handle, btn_cfg, newFunction), "unregister callback fail");
}
// Method to detach button press down event
void Button::detachPressDownEvent(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    }
    CHECK_ESP_ERROR(iot_button_unregister_cb(_handle, BUTTON_PRESS_DOWN), "detach pressdown event fail");
}

/* 1. Button Press Up*/

// Method to attach callback function for button press up event
void Button::attachPressUpEventCb(callbackFunction newFunction, void *usr_data)
{
    if (newFunction == NULL) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    CHECK_ESP_ERROR(iot_button_register_cb(_handle, BUTTON_PRESS_UP, newFunction, usr_data), "attach callback fail");
}

// Method to unregister button press up event
void Button::unregisterPressUpEventCb(callbackFunction newFunction)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_PRESS_UP;

    CHECK_ESP_ERROR(iot_button_unregister_event(_handle, btn_cfg, newFunction), "unregister callback fail");
}
// Method to detach button press up event
void Button::detachPressUpEvent(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    }

    CHECK_ESP_ERROR(iot_button_unregister_cb(_handle, BUTTON_PRESS_UP), "detach press up event fail");
}

/*2. Button Press Repeat*/

// Method to attach callback function for button press repeat event
void Button::attachPressRepeatEventCb(callbackFunction newFunction, void *usr_data)
{
    if (newFunction == NULL) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    CHECK_ESP_ERROR(iot_button_register_cb(_handle, BUTTON_PRESS_REPEAT, newFunction, usr_data), "attach callback fail");
}
// Method to unregister button press down event
void Button::unregisterPressRepeatEventCb(callbackFunction newFunction)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_PRESS_REPEAT;

    CHECK_ESP_ERROR(iot_button_unregister_event(_handle, btn_cfg, newFunction), "unregister callback fail");
}
// Method to detach button press repeat event
void Button::detachPressRepeatEvent(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    }

    CHECK_ESP_ERROR(iot_button_unregister_cb(_handle, BUTTON_PRESS_REPEAT), "detach press repeat event fail");
}

/*3. Button Single Click*/

// Method to attach callback function for button single click event
void Button::attachSingleClickEventCb(callbackFunction newFunction, void *usr_data)
{
    if (newFunction == NULL) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }
    CHECK_ESP_ERROR(iot_button_register_cb(_handle, BUTTON_SINGLE_CLICK, newFunction, usr_data), "attach callback fail");
}
// Method to unregister button press down event
void Button::unregisterSingleClickEventCb(callbackFunction newFunction)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_SINGLE_CLICK;

    CHECK_ESP_ERROR(iot_button_unregister_event(_handle, btn_cfg, newFunction), "unregister callback fail");
}
// Method to detach button single click event
void Button::detachSingleClickEvent(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    }

    CHECK_ESP_ERROR(iot_button_unregister_cb(_handle, BUTTON_SINGLE_CLICK), "detach single click event fail");
}

/*4. Button Double Click*/

// Method to attach callback function for button double click event
void Button::attachDoubleClickEventCb(callbackFunction newFunction, void *usr_data)
{
    if (newFunction == NULL) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }
    CHECK_ESP_ERROR(iot_button_register_cb(_handle, BUTTON_DOUBLE_CLICK, newFunction, usr_data), "attach callback fail");
}
// Method to unregister double click event
void Button::unregisterDoubleClickEventCb(callbackFunction newFunction)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_DOUBLE_CLICK;

    CHECK_ESP_ERROR(iot_button_unregister_event(_handle, btn_cfg, newFunction), "unregister callback fail");
}
// Method to detach button double click event
void Button::detachDoubleClickEvent(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    }

    CHECK_ESP_ERROR(iot_button_unregister_cb(_handle, BUTTON_DOUBLE_CLICK), "detach double click event Fail");
}

/*5. Button Long Press Start*/

// Method to attach callback function for button long press start event
void Button::attachLongPressStartEventCb(callbackFunction newFunction, void *usr_data)
{
    if (newFunction == NULL) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }
    CHECK_ESP_ERROR(iot_button_register_cb(_handle, BUTTON_LONG_PRESS_START, newFunction, usr_data), "attach callback fail");
}
// Method to unregister long press event
void Button::unregisterLongPressStartEventCb(callbackFunction newFunction)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_LONG_PRESS_START;
    CHECK_ESP_ERROR(iot_button_unregister_event(_handle, btn_cfg, newFunction), "unregister callback fail");
}
// Method to detach button long press start event
void Button::detachLongPressStartEvent(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    }

    CHECK_ESP_ERROR(iot_button_unregister_cb(_handle, BUTTON_LONG_PRESS_START), "Detach Callback Fail");
}

/*6. Button Long Press Hold*/

// Method to attach callback function for button long press hold event
void Button::attachLongPressHoldEventCb(callbackFunction newFunction, void *usr_data)
{
    if (newFunction == NULL) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }
    CHECK_ESP_ERROR(iot_button_register_cb(_handle, BUTTON_LONG_PRESS_HOLD, newFunction, usr_data), "attach callback fail");
}
// Method to unregister long press hold event
void Button::unregisterLongPressHoldEventCb(callbackFunction newFunction)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_LONG_PRESS_HOLD;

    CHECK_ESP_ERROR(iot_button_unregister_event(_handle, btn_cfg, newFunction), "unregister callback fail");
}
// Method to detach button long press hold event
void Button::detachLongPressHoldEvent(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    }

    CHECK_ESP_ERROR(iot_button_unregister_cb(_handle, BUTTON_LONG_PRESS_HOLD), "detach long press hold event fail");
}

/*7. Button Press Repeat Done*/

// Method to attach callback function for button press repeat done event
void Button::attachPressRepeatDoneEventCb(callbackFunction newFunction, void *usr_data)
{
    if (newFunction == NULL) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }
    CHECK_ESP_ERROR(iot_button_register_cb(_handle, BUTTON_PRESS_REPEAT_DONE, newFunction, usr_data), "attach callback fail");
}
// Method to unregister press repeat done event
void Button::unregisterPressRepeatDoneEventCb(callbackFunction newFunction)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_PRESS_REPEAT_DONE;

    CHECK_ESP_ERROR(iot_button_unregister_event(_handle, btn_cfg, newFunction), "unregister callback fail");
}
// Method to detach button repeat down event
void Button::detachPressRepeatDoneEvent(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    }

    CHECK_ESP_ERROR(iot_button_unregister_cb(_handle, BUTTON_PRESS_REPEAT_DONE), "detach press repeat done event fail");
}

/*8. Button Multiple Clicks*/

// Method to attach callback function for button press down event
void Button::attachMultipleClickEventCb(callbackFunction newFunction, int clicks, void *usr_data)
{
    if (newFunction == NULL) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_MULTIPLE_CLICK;
    btn_cfg.event_data.multiple_clicks.clicks = clicks;

    CHECK_ESP_ERROR(iot_button_register_event_cb(_handle, btn_cfg, newFunction, usr_data), "attach callback fail");
}
// Method to unregistered multiclick event
void Button::unregisterMultiClickEventCb(callbackFunction newFunction, int clicks)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_MULTIPLE_CLICK; // Set the event to unregister
    btn_cfg.event_data.multiple_clicks.clicks = clicks;

    CHECK_ESP_ERROR(iot_button_unregister_event(_handle, btn_cfg, newFunction), "unregister callback fail");
}

/*9. Button Long Press Up*/

// Method to attach callback function for button press down event
void Button::attachLongPressUpEventCb(callbackFunction newFunction, void *usr_data)
{
    if (newFunction == NULL) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }
    CHECK_ESP_ERROR(iot_button_register_cb(_handle, BUTTON_LONG_PRESS_UP, newFunction, usr_data), "attach callback fail");
}
// Method to unregistered long press up event
void Button::unregisterLongPressUpEventCb(callbackFunction newFunction)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Callback function not defined");
        return;
    }

    button_event_config_t btn_cfg;
    btn_cfg.event = BUTTON_LONG_PRESS_UP;

    CHECK_ESP_ERROR(iot_button_unregister_event(_handle, btn_cfg, newFunction), "unregister callback fail");
}
// Method to detach Button Long Pres Up  event
void Button::detachLongPressUpEvent(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    }

    CHECK_ESP_ERROR(iot_button_unregister_cb(_handle, BUTTON_LONG_PRESS_UP), "detach long press up event Fail");
}

/*Other Methods*/

// Method to delete button
void Button::del(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    }
    CHECK_ESP_ERROR(iot_button_delete(_handle), "delete button fail");
    _handle = NULL;
}

// Method to count call back
int Button::countCallBack(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return 0;
    } else {
        return iot_button_count_cb(_handle);
    }
}

// Method to count call back events
int Button::countEvent(button_event_t event)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return 0;
    } else {
        return iot_button_count_event(_handle, event);
    }
}

// Method to get event
int Button::getEvent(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return 0;
    } else {
        return iot_button_get_event(_handle);
    }
}

// Method to get repeat
int Button::getRepeat(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return 0;
    } else {
        return iot_button_get_repeat(_handle);
    }
}

// Method to get tick time
int Button::getTickTime(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return 0;
    } else {
        return iot_button_get_ticks_time(_handle);
    }
}

// Method to get long press hold count
int Button::getLongPressHoldCount(void)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return 0;
    } else {
        return iot_button_get_long_press_hold_cnt(_handle);
    }
}

// Method to set parameter
void Button::setParam(button_param_t param, void *value)
{
    if (!_handle) {
        ESP_LOGE(TAG, "Button not created");
        return;
    } else {
        CHECK_ESP_ERROR(iot_button_set_param(_handle, param, value), "paramater set fail");
    }
}

// Method to button resume
void Button::resume(void)
{
    CHECK_ESP_ERROR(iot_button_resume(), "button resume fail");
}

//Method to button stop
void Button::stop(void)
{
    CHECK_ESP_ERROR(iot_button_stop(), "button stop fail");
}
