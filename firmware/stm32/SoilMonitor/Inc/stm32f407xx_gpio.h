/*
 * stm32f407xx_gpio.h
 *
 *  Created on: Sep 28, 2026
 *      Author: ADMIN
 */

#ifndef STM32F407XX_GPIO_H_
#define STM32F407XX_GPIO_H_

#include "stm32f407xx.h"

/*
 * This is a configuration structure for a GPIO pin
 */
typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

typedef struct
{
	GPIO_PinConfig_t GPIO_PinConfig;
	GPIO_RegDef_t *pGPIOx;
}GPIO_Handle_t;

/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/
/*
 * Peripheral Clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);




#endif /* STM32F407XX_GPIO_H_ */
