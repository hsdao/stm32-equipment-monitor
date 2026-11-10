#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <stdint.h>
#include "stm32f4xx_hal.h"

HAL_StatusTypeDef LCD_Init(I2C_HandleTypeDef *hi2c, uint8_t address);
HAL_StatusTypeDef LCD_WriteChar(char character);
HAL_StatusTypeDef LCD_WriteString(const char *text);
HAL_StatusTypeDef LCD_SetCursor(uint8_t row, uint8_t column);

#endif /* LCD_I2C_H */
