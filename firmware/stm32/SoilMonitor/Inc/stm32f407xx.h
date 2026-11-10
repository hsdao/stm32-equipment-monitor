/*
 * stm32f407xx.h
 *
 *  Created on: Sep 28, 2026
 *      Author: ADMIN
 */

#ifndef STM32F407XX_H_
#define STM32F407XX_H_

#include<stddef.h>
#include<stdint.h>

#define __vo volatile
#define __weak __attribute__((weak))


/*
 * AHBx and APBx Bus Peripheral base addresses
 */
#define APB1PERIPH_BASEADDR		0x40000000U
#define APB2PERIPH_BASEADDR		0x40010000U
#define AHB1PERIPH_BASEADDR		0x40020000U
#define AHB2PERIPH_BASEADDR		0x50000000U
#define AHB3PERIPH_BASEADDR		0xA0000000U

/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 */
#define GPIOA_BASEADDR		(APB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR		(APB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR		(APB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR		(APB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR		(APB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR		(APB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR		(APB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR		(APB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR		(APB1PERIPH_BASEADDR + 0x2000)
#define GPIOJ_BASEADDR		(APB1PERIPH_BASEADDR + 0x2400)
#define GPIOK_BASEADDR		(APB1PERIPH_BASEADDR + 0x2800)
#define RCC_BASEADDR		(APB1PERIPH_BASEADDR + 0x3800)

/**********************************peripheral register definition structures **********************************/

/*
 * Note : Registers of a peripheral are specific to MCU
 * e.g : Number of Registers of SPI peripheral of STM32F4x family of MCUs may be different(more or less)
 * Compared to number of registers of SPI peripheral of STM32Lx or STM32F0x family of MCUs
 * Please check your Device RM
 */
typedef struct
{
	__vo uint32_t MODER;
	__vo unint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;

typedef struct
{
	__vo uint32_t RCC_CR;
	__vo uint32_t RCC_PLLCFGR;
	__vo uint32_t RCC_CFGR;
	__vo uint32_t RCC_CIR;
	__vo uint32_t RCC_AHB1RSTR;
	__vo uint32_t RCC_AHB2RSTR;
	__vo uint32_t RCC_AHB3RSTR;
	uint32_t RESERVED0;
	__vo uint32_t RCC_APB1RSTR;
	__vo uint32_t RCC_APB2RSTR;
	uint32_t RESERVED1[2];
	__vo uint32_t RCC_AHB1ENR;
	__vo uint32_t RCC_AHB2ENR;
	__vo uint32_t RCC_AHB3ENR;
	uint32_t RESERVED2;
	__vo uint32_t RCC_APB1ENR;
	__vo uint32_t RCC_APB2ENR;
	uint32_t RESERVED3[2];
	__vo uint32_t RCC_AHB1LPENR;
	__vo uint32_t RCC_AHB2LPENR;
	__vo uint32_t RCC_AHB3LPENR;
	uint32_t RESERVED4;
	__vo uint32_t RCC_APB1LPENR;
	__vo uint32_t RCC_APB2LPENR;
	uint32_t RESERVED5[2];
	__vo uint32_t RCC_BDCR;
	__vo uint32_t RCC_CSR;
	uint32_t RESERVED6[2];
	__vo uint32_t RCC_SSCGR;
	__vo uint32_t RCC_PLLI2SCFGR;
}RCC_RegDef_t;


/*
 * peripheral definitions
 */
#define GPIOA				((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB				((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC				((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD				((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE				((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF				((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG				((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH				((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI				((GPIO_RegDef_t*)GPIOI_BASEADDR)
#define GPIOJ				((GPIO_RegDef_t*)GPIOJ_BASEADDR)
#define GPIOK				((GPIO_RegDef_t*)GPIOK_BASEADDR)


#define RCC					((RCC_RegDef_t*)RCC_BASEADDR)


/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN		(RCC->RCC_AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN		(RCC->RCC_AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN		(RCC->RCC_AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN		(RCC->RCC_AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN		(RCC->RCC_AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN		(RCC->RCC_AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN		(RCC->RCC_AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN		(RCC->RCC_AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN		(RCC->RCC_AHB1ENR |= (1 << 8))


/*
 * Clock Diable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI		(RCC->RCC_AHB1ENR &= ~ (1 << 0))
#define GPIOB_PCLK_DI		(RCC->RCC_AHB1ENR &= ~ (1 << 1))
#define GPIOC_PCLK_DI		(RCC->RCC_AHB1ENR &= ~ (1 << 2))
#define GPIOD_PCLK_DI		(RCC->RCC_AHB1ENR &= ~ (1 << 3))
#define GPIOE_PCLK_DI		(RCC->RCC_AHB1ENR &= ~ (1 << 4))
#define GPIOF_PCLK_DI		(RCC->RCC_AHB1ENR &= ~ (1 << 5))
#define GPIOG_PCLK_DI		(RCC->RCC_AHB1ENR &= ~ (1 << 6))
#define GPIOH_PCLK_DI		(RCC->RCC_AHB1ENR &= ~ (1 << 7))
#define GPIOI_PCLK_DI		(RCC->RCC_AHB1ENR &= ~ (1 << 8))



#define ENABLE			1
#define DISABLE			0
#endif /* STM32F407XX_H_ */

