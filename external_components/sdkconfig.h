/*
 * Automatically generated file. DO NOT EDIT.
 * Espressif IoT Development Framework (ESP-IDF)  Configuration Header
 */
#pragma once
#define CONFIG_FREERTOS_HZ 100
#define CONFIG_FREERTOS_CHECK_STACKOVERFLOW_CANARY 1
#define CONFIG_FREERTOS_THREAD_LOCAL_STORAGE_POINTERS 1
#define CONFIG_FREERTOS_IDLE_TASK_STACKSIZE 1536
#define CONFIG_FREERTOS_MAX_TASK_NAME_LEN 16
#define CONFIG_FREERTOS_TIMER_SERVICE_TASK_NAME "Tmr Svc"
#define CONFIG_FREERTOS_TIMER_TASK_PRIORITY 1
#define CONFIG_FREERTOS_TIMER_TASK_STACK_DEPTH 2048
#define CONFIG_FREERTOS_TIMER_QUEUE_LENGTH 10
#define CONFIG_FREERTOS_QUEUE_REGISTRY_SIZE 0
#define CONFIG_FREERTOS_TASK_NOTIFICATION_ARRAY_ENTRIES 1
#define CONFIG_FREERTOS_TLSP_DELETION_CALLBACKS 1
#define CONFIG_FREERTOS_CHECK_MUTEX_GIVEN_BY_OWNER 1
#define CONFIG_FREERTOS_ISR_STACKSIZE 1536
#define CONFIG_FREERTOS_INTERRUPT_BACKTRACE 1
#define CONFIG_FREERTOS_TICK_SUPPORT_SYSTIMER 1
#define CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL1 1
#define CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER 1
#define CONFIG_FREERTOS_PORT 1
#define CONFIG_FREERTOS_NO_AFFINITY 0x7FFFFFFF
#define CONFIG_FREERTOS_SUPPORT_STATIC_ALLOCATION 1
#define CONFIG_FREERTOS_DEBUG_OCDAWARE 1
#define CONFIG_FREERTOS_ENABLE_TASK_SNAPSHOT 1
#define CONFIG_FREERTOS_PLACE_SNAPSHOT_FUNS_INTO_FLASH 1
#define CONFIG_ESP_SYSTEM_PANIC_PRINT_REBOOT 1
#define CONFIG_ESP_SYSTEM_PANIC_REBOOT_DELAY_SECONDS 0
#define CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE 32
#define CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE 2304
#define CONFIG_ESP_MAIN_TASK_STACK_SIZE 3584
#define CONFIG_ESP_MAIN_TASK_AFFINITY_CPU0 1
#define CONFIG_ESP_MAIN_TASK_AFFINITY 0x0
#define CONFIG_ESP_MINIMAL_SHARED_STACK_SIZE 2048
#define CONFIG_ESP_CONSOLE_UART_DEFAULT 1
#define CONFIG_ESP_CONSOLE_UART 1
#define CONFIG_ESP_CONSOLE_UART_NUM 0
#define CONFIG_ESP_CONSOLE_UART_BAUDRATE 115200
#define CONFIG_ESP_INT_WDT 1
#define CONFIG_ESP_INT_WDT_TIMEOUT_MS 300
#define CONFIG_ESP_INT_WDT_CHECK_CPU1 1
#define CONFIG_ESP_TASK_WDT_EN 1
#define CONFIG_ESP_TASK_WDT_INIT 1
#define CONFIG_ESP_TASK_WDT_TIMEOUT_S 5
#define CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0 1
#define CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1 1
#define CONFIG_ESP_DEBUG_OCDAWARE 1
#define CONFIG_ESP_SYSTEM_CHECK_INT_LEVEL_4 1
#define CONFIG_ESP_IPC_TASK_STACK_SIZE 1024
#define CONFIG_ESP_IPC_USES_CALLERS_PRIORITY 1
#define CONFIG_ESP_IPC_ISR_ENABLE 1
#define CONFIG_SOC_GPIO_IN_RANGE_MAX 65535
#define CONFIG_SOC_GPIO_OUT_RANGE_MAX 65535
#define CONFIG_SOC_I2C_SUPPORT_SLAVE 1
#define CONFIG_SOC_I2C_SUPPORT_10BIT_ADDR 1
#define CONFIG_SOC_EFUSE_SECURE_BOOT_KEY_DIGESTS 1
#define CONFIG_LOG_DEFAULT_LEVEL_INFO 1
#define CONFIG_LOG_DEFAULT_LEVEL 3
#define CONFIG_LOG_MAXIMUM_EQUALS_DEFAULT 1
#define CONFIG_LOG_MAXIMUM_LEVEL 3
#define CONFIG_LOG_COLORS 1
#define CONFIG_LOG_TIMESTAMP_SOURCE_RTOS 1
#define CONFIG_EFUSE_MAX_BLK_LEN 256
