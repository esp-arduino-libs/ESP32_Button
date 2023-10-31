/* SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_idf_version.h"
#include "esp_log.h"
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
#include "esp_adc/adc_cali.h"
#endif
#include "unity.h"
#include "Button.h"
#include "sdkconfig.h"

static const char *TAG = "ESP32 Arduino BUTTON TEST";

#define TEST_MEMORY_LEAK_THRESHOLD (-400)
#define BUTTON_IO_NUM  0
#define BUTTON_ACTIVE_LEVEL   0
#define BUTTON_NUM 16

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
#define ADC_BUTTON_WIDTH SOC_ADC_RTC_MAX_BITWIDTH
#else
#define ADC_BUTTON_WIDTH ADC_WIDTH_MAX - 1
#endif


static void onButtonPressDownCb(void *button_handle, void *usr_data)
{
    ESP_LOGI(TAG, "Button pressed down");
}
static void onButtonPressDownRepeatCb(void *button_handle, void *usr_data)
{
    ESP_LOGI(TAG, "Button press down repeat");
}
static void onButtonPressUpCb(void *button_handle, void *usr_data)
{
    ESP_LOGI(TAG, "Button press Up");
}
static void onButtonSingleClickCb(void *button_handle, void *usr_data)
{
    ESP_LOGI(TAG, "Button single click");
}
static void onButtonSingleClickRepeatCb(void *button_handle, void *usr_data)
{
    ESP_LOGI(TAG, "Button single click repeat");
}


TEST_CASE("gpio button test", "[button][iot]")
{
    // Button* btn = new Button(9, false);
    Button btn(GPIO_NUM_9, false);

    btn.attachPressDownEventCb(&onButtonPressDownCb, NULL);
    btn.attachPressUpEventCb(&onButtonPressUpCb, NULL);
    btn.attachPressDownEventCb(&onButtonPressDownRepeatCb, NULL);
    btn.attachSingleClickEventCb(&onButtonSingleClickCb, NULL);
    btn.attachSingleClickEventCb(&onButtonSingleClickRepeatCb, NULL);
    btn.unregisterPressDownEventCb(&onButtonPressDownCb);
    btn.detachSingleClickEvent();
    btn.stop();
    vTaskDelay(pdMS_TO_TICKS(5000));
    btn.resume();
    vTaskDelay(pdMS_TO_TICKS(10000));
    btn.del();
}

static size_t before_free_8bit;
static size_t before_free_32bit;

static void check_leak(size_t before_free, size_t after_free, const char *type)
{
    ssize_t delta = after_free - before_free;
    printf("MALLOC_CAP_%s: Before %u bytes free, After %u bytes free (delta %d)\n", type, before_free, after_free, delta);
    TEST_ASSERT_MESSAGE(delta >= TEST_MEMORY_LEAK_THRESHOLD, "memory leak");
}

void setUp(void)
{
    before_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    before_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
}

void tearDown(void)
{
    size_t after_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    size_t after_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
    check_leak(before_free_8bit, after_free_8bit, "8BIT");
    check_leak(before_free_32bit, after_free_32bit, "32BIT");
}

extern "C" void app_main(void)
{
    printf("USB STREAM TEST \n");
    unity_run_menu();
}
