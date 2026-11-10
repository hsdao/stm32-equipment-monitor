#ifndef SOIL_SPI_H
#define SOIL_SPI_H

#include "stm32f4xx_hal.h"

typedef struct
{
    float temperature;
    float moisture;
    uint8_t valid;
} SoilData_t;

void SoilSPI_Init(SPI_HandleTypeDef *hspi);
void SoilSPI_Process(void);
SoilData_t SoilSPI_GetData(void);

#endif
