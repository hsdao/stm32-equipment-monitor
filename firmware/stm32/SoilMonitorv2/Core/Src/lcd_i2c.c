/*
 * soil_i2c.c
 *
 *  Created on: Oct 25, 2026
 *      Author: ADMIN
 */


#include "lcd_i2c.h"
#include <stddef.h>

#define LCD_RS 				(1U << 0)
#define LCD_RW				(1U << 1)
#define LCD_EN				(1U << 2)
#define LCD_BACKLIGHT		(1U << 3)



static I2C_HandleTypeDef *lcdI2c = NULL;
static uint8_t lcdAddress = 0;

static HAL_StatusTypeDef LCD_WriteByte(uint8_t value)
{
	if(lcdI2c == NULL)
	{
		return HAL_ERROR;
	}

	return HAL_I2C_Master_Transmit(
		lcdI2c,
		lcdAddress << 1,
		&value,
		1,
		20
	);
}

static HAL_StatusTypeDef LCD_WriteNibble(uint8_t nibble, uint8_t rs)
{
    uint8_t output = (nibble & 0x0F) << 4;
    output |= LCD_BACKLIGHT;

    if (rs != 0)
    {
        output |= LCD_RS;
    }

    /* Set data with Enable LOW. */
    HAL_StatusTypeDef status = LCD_WriteByte(output);
    if (status != HAL_OK)
    {
        return status;
    }

    /* Set Enable HIGH without changing the data. */
    status = LCD_WriteByte(output | LCD_EN);
    if (status != HAL_OK)
    {
        return status;
    }

    /* Set Enable LOW again. */
    status = LCD_WriteByte(output);
    if (status != HAL_OK)
    {
        return status;
    }

    HAL_Delay(1);

    return HAL_OK;
}


static HAL_StatusTypeDef LCD_SendByte(uint8_t value, uint8_t rs)
{
    /* 1. Gửi 4 bit cao bằng LCD_WriteNibble().
       Lưu kết quả vào biến status. */
	uint8_t temp = value >> 4;
	HAL_StatusTypeDef status = LCD_WriteNibble(temp, rs);


    /* 2. Nếu status khác HAL_OK, trả về status ngay. */
	if (status != HAL_OK)
	{
		return status;
	}
    /* 3. Gửi 4 bit thấp bằng LCD_WriteNibble().
       Trả về kết quả của lần gọi này. */
	status = LCD_WriteNibble(value & 0x0F, rs);

    return status;
}


static HAL_StatusTypeDef LCD_SendCommand(uint8_t command)
{
    /* Gọi LCD_SendByte() để gửi command với RS = 0.
       Trả về kết quả của lần gọi đó. */
	return LCD_SendByte(command, 0);
}

HAL_StatusTypeDef LCD_SetCursor(uint8_t row, uint8_t column)
{
    /* LCD 16x2: chỉ chấp nhận dòng 0–1 và cột 0–15. */
    if (row >= 2 || column >= 16)
    {
        return HAL_ERROR;
    }

    uint8_t address;

    if (row == 0)
    {
        address = 0x00 + column;
    }
    else
    {
        address = 0x40 + column;
    }

    return LCD_SendCommand(0x80 | address);
}


HAL_StatusTypeDef LCD_WriteChar(char character)
{
    /* Gọi LCD_SendByte() với character và RS = 1.
       Trả về kết quả của lần gọi đó. */
	return LCD_SendByte(character, 1);
}

HAL_StatusTypeDef LCD_WriteString(const char *text)
{
    if (text == NULL)
    {
        return HAL_ERROR;
    }

    while (*text != '\0')
    {
        /* 1. Gọi LCD_WriteChar() với ký tự hiện tại: *text.
              Lưu kết quả vào biến status. */
    	HAL_StatusTypeDef status = LCD_WriteChar(*text);
        /* 2. Nếu có lỗi, trả về status ngay. */
    	if(status != HAL_OK)
    	{
    		return status;
    	}
        /* 3. Tăng con trỏ text để chuyển sang ký tự tiếp theo. */
    	text++;
    }

    return HAL_OK;
}

HAL_StatusTypeDef LCD_Init(I2C_HandleTypeDef *hi2c, uint8_t address)
{
    /* 1. Reject a NULL handle or an address greater than 0x7F. */
	if(address > 0x7F || hi2c == NULL)
	{
		return HAL_ERROR;
	}
    /* 2. Store hi2c in lcdI2c. */
	lcdI2c = hi2c;
    /* 3. Store address in lcdAddress. */
	lcdAddress = address;
    /* LCD initialization sequence will be added here later. */
	HAL_StatusTypeDef status;

	/* Chờ LCD ổn định sau khi được cấp nguồn. */
	HAL_Delay(50);

	status = LCD_WriteByte(LCD_BACKLIGHT);
	if (status != HAL_OK)
	{
	    return status;
	}

	/* Gửi mẫu khởi tạo đầu tiên: D7–D4 = 0011, RS = 0. */
	status = LCD_WriteNibble(0x03, 0);

	if (status != HAL_OK)
	{
	    return status;
	}

	/* Sau lần đầu, datasheet yêu cầu chờ hơn 4,1 ms. */
	HAL_Delay(5);

	/* Gửi 0x03 lần thứ hai. */
	status = LCD_WriteNibble(0x03, 0);
	if (status != HAL_OK)
	{
	    return status;
	}

	/* Gửi 0x03 lần thứ ba. */
	status = LCD_WriteNibble(0x03, 0);
	if (status != HAL_OK)
	{
	    return status;
	}

	/* Chuyển sang chế độ giao tiếp 4 bit. */
	status = LCD_WriteNibble(0x02, 0);
	if (status != HAL_OK)
	{
	    return status;
	}
	/* Chế độ 4 bit, 2 dòng, font 5x8. */
	status = LCD_SendCommand(0x28);

	if (status != HAL_OK)
	{
	    return status;
	}

	/* Tắt hiển thị, tắt con trỏ và nhấp nháy. */
	status = LCD_SendCommand(0x08);
	if (status != HAL_OK)
	{
	    return status;
	}

	/* Xóa màn hình và đưa con trỏ về đầu. */
	status = LCD_SendCommand(0x01);
	if (status != HAL_OK)
	{
	    return status;
	}

	/* Lệnh xóa cần thời gian xử lý lâu hơn lệnh thông thường. */
	HAL_Delay(2);

	/* Sau mỗi ký tự: tăng địa chỉ ghi, không dịch màn hình. */
	status = LCD_SendCommand(0x06);
	if (status != HAL_OK)
	{
	    return status;
	}

	/* Bật hiển thị, ẩn con trỏ, tắt nhấp nháy. */
	status = LCD_SendCommand(0x0C);
	if (status != HAL_OK)
	{
	    return status;
	}


	return HAL_OK;

}
