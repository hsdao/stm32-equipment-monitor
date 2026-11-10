/*
 * soil_alarm.c
 *
 *  Created on: Oct 25, 2026
 *      Author: ADMIN
 */


#include "soil_alarm.h"
#include "main.h"

static uint8_t temperatureAlarm = 0;
static uint8_t moistureAlarm = 0;

static float temperatureHighThreshold = 30.0f;
static float temperatureClearThreshold = 28.0f;

static float moistureHighThreshold = 80.0f;
static float moistureClearThreshold = 75.0f;


void SoilAlarm_Init(void)
{
    temperatureAlarm = 0;
    moistureAlarm = 0;

    HAL_GPIO_WritePin(
        GPIOD,
        GPIO_PIN_12 | GPIO_PIN_14,
        GPIO_PIN_RESET
    );
}


void SoilAlarm_Update(SoilData_t reading)
{
    /* Invalid data: turn both LEDs off. */
    if (!reading.valid)
    {
        HAL_GPIO_WritePin(
            GPIOD,
            GPIO_PIN_12 | GPIO_PIN_14,
            GPIO_PIN_RESET
        );

        return;
    }

    /* Temperature alarm with hysteresis. */
    if (reading.temperature > temperatureHighThreshold)
    {
        temperatureAlarm = 1;
    }
    else if (reading.temperature < temperatureClearThreshold)
    {
        temperatureAlarm = 0;
    }

    /* Moisture alarm with hysteresis. */
    if (reading.moisture > moistureHighThreshold)
    {
        moistureAlarm = 1;
    }
    else if (reading.moisture < moistureClearThreshold)
    {
        moistureAlarm = 0;
    }

    uint8_t soilAlarm = temperatureAlarm || moistureAlarm;

    if (soilAlarm)
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    }
}
