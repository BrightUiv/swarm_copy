#ifndef _TASK_QUEUE_SYSTEM_H_
#define _TASK_QUEUE_SYSTEM_H_

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "swarm_ranging.h"

#include "adhocdeck.h"
#include <apr_queue.h>

/**
 * Type by which queues are referenced.  For example, a call to xQueueCreate()
 * returns an QueueHandle_t variable that can then be used as a parameter to
 * xQueueSend(), xQueueReceive(), etc.
 */
// struct QueueDefinition; /* Using old naming convention so as not to break kernel aware debuggers. */

#define pdFALSE 0
#define pdTRUE 1

#define M2T(X) ((unsigned int)(X))
#define F2T(X) ((unsigned int)((configTICK_RATE_HZ / (X))))
#define T2M(X) ((unsigned int)(X))

#define ASSERT(e) assert(e)

#define portMAX_DELAY (TickType_t)0xffffffffUL

#define RANGING_RX_QUEUE_ITEM_SIZE sizeof(Ranging_Message_With_Timestamp_t)
#define RANGING_RX_QUEUE_SIZE 5

//---------------------------------------------------------------------------------------------------------
static UWB_Message_Listener_t listener;
static timer_t neighborSetEvictionTimer;
static uint16_t MY_UWB_ADDRESS;
static UWB_Message_Listener_t listeners[UWB_MESSAGE_TYPE_COUNT];
static QueueHandle_t rxQueue;

typedef uint32_t TickType_t;
typedef pthread_mutex_t SemaphoreHandle_t;
typedef long BaseType_t;

void rangingRxCallback(void *parameters);
void rangingTxCallback(void *parameters);

uint16_t uwbGetAddress();
timer_t xTimerCreate();
long xTimerStart(timer_t timer_id, int expire_time, int repetition);
long xTaskCreate(void *task_funcion);
// typedef uint16_t logVarId_t;
// static logVarId_t idVelocityX, idVelocityY, idVelocityZ;
int uwbSendPacketBlock(UWB_Packet_t *packet);

//----------------------------------------------------------------------------------------------------------

typedef apr_queue_t *QueueHandle_t;
static apr_queue_t *queues[UWB_MESSAGE_TYPE_COUNT];

typedef uint32_t portTickType;

static UWB_Message_Listener_t listeners[UWB_MESSAGE_TYPE_COUNT];

/**
 * Type by which software timers are referenced.  For example, a call to
 * xTimerCreate() returns an TimerHandle_t variable that can then be used to
 * reference the subject timer in calls to other software timer API functions
 * (for example, xTimerStart(), xTimerReset(), etc.).
 */
// struct tmrTimerControl; /* The old naming convention is used to prevent breaking kernel aware debuggers. */
// typedef struct tmrTimerControl * TimerHandle_t;

/**
 * task. h
 *
 * Type by which tasks are referenced.  For example, a call to xTaskCreate
 * returns (via a pointer parameter) an TaskHandle_t variable that can then
 * be used as a parameter to vTaskDelete to delete the task.
 *
 * \defgroup TaskHandle_t TaskHandle_t
 * \ingroup Tasks
 */
struct tskTaskControlBlock; /* The old naming convention is used to prevent breaking kernel aware debuggers. */
// typedef struct tskTaskControlBlock * TaskHandle_t;

// 实现--自己修改
//  typedef uint32_t TickType_t;
//  typedef long TickType_t;

// BaseType_t xQueueSemaphoreTake( QueueHandle_t xQueue, TickType_t xTicksToWait );
// #define xSemaphoreTake( xSemaphore, xBlockTime )    xQueueSemaphoreTake( ( xSemaphore ), ( xBlockTime ) )

// BaseType_t xQueueGenericSend( QueueHandle_t xQueue);
// #define xSemaphoreGive( xSemaphore )    xQueueGenericSend( ( QueueHandle_t ) ( xSemaphore ))

// 实现
SemaphoreHandle_t xSemaphoreCreateMutex();

// 自己添加，实现
void xSemaphoreDestroyMutex(SemaphoreHandle_t mutex);

// 实现
TickType_t xTaskGetTickCount(void);

// 实现
void vTaskDelay(const TickType_t xTicksToDelay);

// BaseType_t  ( QueueHandle_t xQueue, void * const pvBuffer,TickType_t xTicksToWait );

// 实现
BaseType_t xQueueReceive(QueueHandle_t xQueue,
                         void *const pvBuffer,
                         TickType_t xTicksToWait);

// 实现
QueueHandle_t xQueueCreate(const uint32_t uxQueueLength, // 指针队列的大小
                           const uint32_t uxItemSize);   // uxItemSize没用

// 自己添加，实现，销毁内存池，释放所需要的所有资源
void xQueueDestroy(apr_pool_t *pool);

// 实现
BaseType_t xQueueSend(QueueHandle_t xQueue,
                      const void *const pvItemToQueue,
                      BaseType_t *const pxHigherPriorityTaskWoken);

// 实现
BaseType_t xQueueSendFromISR(QueueHandle_t xQueue,
                             const void *const pvItemToQueue,
                             BaseType_t *const pxHigherPriorityTaskWoken);

// 有些需要修改
void uwbRegisterListener(UWB_Message_Listener_t *listener);

#define //_TASK_QUEUE_SYSTEM_H_