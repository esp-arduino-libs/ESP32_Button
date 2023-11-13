[![Arduino Lint](https://github.com/esp-arduino-libs/ESP32_Button/actions/workflows/arduino_lint.yml/badge.svg)](https://github.com/esp-arduino-libs/ESP32_Button/actions/workflows/arduino_lint.yml) [![pre-commit](https://github.com/esp-arduino-libs/ESP32_Button/actions/workflows/pre-commit.yml/badge.svg)](https://github.com/esp-arduino-libs/ESP32_Button/actions/workflows/pre-commit.yml) [![Build Test Apps](https://github.com/esp-arduino-libs/ESP32_Button/actions/workflows/build_test.yml/badge.svg)](https://github.com/esp-arduino-libs/ESP32_Button/actions/workflows/build_test.yml)

# ESP32_Button

ESP32_Button is an Arduino library designed for creating both GPIO and ADC buttons using ESP32 System-on-Chip (SoC) devices. This versatile library simplifies the process of configuring and working with buttons on ESP32-based projects.

ESP32_Button builds upon the functionality provided by the [ESP-IOT-SOLUTION/Components/Button](https://github.com/espressif/esp-iot-solution/tree/master/components/button) library, offering an accessible interface for button-related tasks in the Arduino ecosystem.

## Features

- Support for all ESP SoCs.
- Supported multiple events.

| Events                      | Description                                                                                                             | Arduino Function             |
| --------------------------- | ----------------------------------------------------------------------------------------------------------------------- | ---------------------------- |
| `Button pressed`            | This event is triggered when the button is initially pressed down.                                                      | attachPressDownEventCb       |
| `Button released`           | This event is triggered when the button is released after being pressed down.                                           | attachPressUpEventCb         |
| `Button pressed - repeated` | This event is triggered when the button is pressed repeatedly in a short span of time.                                  | attachPressRepeatEventCb     |
| `Button single click`       | This event is triggered when the button is clicked once without any repeated presses.                                   | attachSingleClickEventCb     |
| `Button double click`       | This event is triggered when the button is clicked twice in quick succession.                                           | attachDoubleClickEventCb     |
| `Button long press start`   | This event is triggered when the button is held down for a specified amount of time, indicating a potential long press. | attachLongPressStartEventCb  |
| `Button long press hold`    | This event is triggered repeatedly while the button is held down after a long press has been detected.                  | attachLongPressHoldEventCb   |
| `Button press repeat done`  | This event is triggered when the button repetition is completed                                                         | attachPressRepeatDoneEventCb |
| `Button long press up`      | This event is triggered after the button long press is completed and button is up                                       | attachLongPressUpEventCb     |
| `Button multiple click`     | This event is triggered when button is designed to click multiple times                                                 | attachMultipleClickEventCb   |

## Supported Drivers

|                             **Driver**                              | **Version** |
| ------------------------------------------------------------------  | ----------- |
| [knob](https://components.espressif.com/components/espressif/button)| 3.1.2       |

## How to Use

For information on how to use the library in the Arduino IDE, please refer to the documentation for [Arduino IDE v1.x.x](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries) or [Arduino IDE v2.x.x](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library).

### Examples

* [example.ino](./examples/example/example.ino): Demonstrates how to use ESP32-Button.

## Detailed Usage

### Initializing a GPIO Button

```
  Button *btn = new Button(pin number, pullupActive)
```
This creates a new button object and assigns it to the pointer variable btn. The button::button() constructor is then defined to take two arguments:

- **pin :** which specifies the pin number that the button is connected to
- **pullupActive :** which is a boolean value indicating whether the internal pull-up resistor of the pin should be enabled or not. If pullupActive is true, the pinMode() function sets the pin as an input with its internal pull-up resistor enabled. This means that the pin will read as HIGH when the button is not pressed, and LOW when the button is pressed. If pullupActive is false, the pinMode() function sets the pin as an input with its internal pull-up resistor disabled. In this case, the pin will read as a floating state, which may be either HIGH or LOW when the button is not pressed. When the button is pressed, it will again momentarily connect the pin to ground, causing it to read as LOW.

### Initializing an ADC Button

```
  Button *btn = new Button(pin number, pullupActive, adc_channel, button_index, min, max);
```
This creates a new button object and assigns it to the pointer variable btn. The Button::Button() constructor is then defined arguments:

- **pin :** which specifies the pin number that the button is connected to,
- **pullupActive :** which is a boolean value indicating whether the internal pull-up resistor of the pin should be enabled or not. If pullupActive is true, the pinMode() function sets the pin as an input with its internal pull-up resistor enabled. This means that the pin will read as HIGH when the button is not pressed, and LOW when the button is pressed. If pullupActive is false, the pinMode() function sets the pin as an input with its internal pull-up resistor disabled. In this case, the pin will read as a floating state, which may be either HIGH or LOW when the button is not pressed. When the button is pressed, it will again momentarily connect the pin to ground, causing it to read as LOW.
- **adc_channel :** Channel of ADC
- **button_index :** button index on the channel
- **min :** min voltage in millivolt corresponding to the button
- **max :** max voltage in millivolt corresponding to the button

### Attach Callback Function

```
  btn-> attachPressDownEventCb(&Callback Function name, usr_data)
```

This attaches a callback function to the button's `attachPressDownEventCb`, which triggers when the button is pressed down.

To use this code, you should replace & "Callback Function name" with the actual name of the function that you want to be called when the attachPressDown event occurs. This function will be executed whenever the button is pressed down. Such as toggling an LED or executing a sequence of instructions. The usr_data parameter can be used to pass any additional user-defined data to the callback function, allowing for more flexibility in response to button presses.

### Detach Callback Function

```
  btn->detachPressDownEvent()
```

The code detaches any event handler that was previously attached to the button instance's `attachPressDownEvent`. This means that if a callback function was previously attached to this event using `btn->attachPressDownEventCb(& Callback Function name, usr_data)`, it will no longer be executed when the button is pressed down.

Detaching an event handler is useful when you want to change the behavior of a button or disable a specific event without affecting the other events attached to the button. For example, if you have multiple functions attached to the button's events and you want to disable only the attachPressDown event temporarily, you can use btn->detachPressDown() to remove the attachPressDown callback function without affecting the other event handlers.

### Unregistered Event Function

```
  btn->unregisterPressDownEvent(callbackFunction newFunction);
```

This function unregister a callback function which is previously attached to the event. The `newFunction` parameter specifies the callback function to be removed from the event's callback list.
Note: One Event can have multiple callbacks attached

### Delete Button

```
  btn->del()
```

The `btn->del()` code deletes the button instance created by `new button(pin number, pullupActive)`, which means all the events attached to the button instance will be detached as well.

So, you don't need to detach the events manually before deleting the button instance using `btn->del()`. The function will automatically detach all the events and remove the instance from memory.

Deleting the button instance is useful when you no longer need the button and want to free up memory space.

### Count Call Back

```
  btn->countCallBack()
```

This function returns the number of callbacks **currently** attached to the button. This functions is useful for debugging and monitoring the state of the button instance, especially if you have multiple event handlers attached to the button and want to ensure that they are all being executed correctly.

### Get Event

```
  btn->getEvent()
```

This event is used to retrieve the current event type of a button instance. This can be helpful for monitoring the current state of the button instance and for triggering different actions or behaviors depending on the current event type.

```
typedef enum {
    BUTTON_PRESS_DOWN = 0,
    BUTTON_PRESS_UP,
    BUTTON_PRESS_REPEAT,
    BUTTON_PRESS_REPEAT_DONE,
    BUTTON_SINGLE_CLICK,
    BUTTON_DOUBLE_CLICK,
    BUTTON_MULTIPLE_CLICK,
    BUTTON_LONG_PRESS_START,
    BUTTON_LONG_PRESS_HOLD,
    BUTTON_LONG_PRESS_UP,
    BUTTON_EVENT_MAX,
    BUTTON_NONE_PRESS,
} button_event_t;
```

### Get Repeat

```
  btn->getRepeat()
```

This function is used to retrieve the number of times a button has been repeatedly pressed since the last button event was triggered.

### Get Tick Time

```
  btn->getTickTime()
```

 This function is used to retrieve the elapsed time since the last button event in milliseconds.

### Get Long Press Hold Count

```
  btn->getLongPressHoldCount()
```

This function is used to retrieve the number of times the button has been held down during a long press event.

### Set Parameter

```
btn->setParam(button_param_t param, void *value);
```

This function allows you to set a parameter value for the button. The parameter includes:

```
typedef enum {
    BUTTON_LONG_PRESS_TIME_MS = 0,
    BUTTON_SHORT_PRESS_TIME_MS,
    BUTTON_PARAM_MAX,
} button_param_t;
```

---
Note:
For additional details and information about the button functionality, please refer to the documentation provided by [ESP-IOT Solutions](https://github.com/espressif/esp-iot-solution/tree/master/components/button).