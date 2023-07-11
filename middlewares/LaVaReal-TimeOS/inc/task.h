#pragma once

typedef void (* TaskFunction_t)( void );

void vTaskStartScheduler(void);

void xTaskCreate(TaskFunction_t task);