/*
 * PCF85363A.cpp
 *
 *  Created on: Mar 20, 2023
 *      Author: hle
 */

#include "PCF85363A.h"


PCF85363A::PCF85363A(I2C_HandleTypeDef &i2cHandle) : handle(i2cHandle){}

HAL_StatusTypeDef PCF85363A::ReadRegister(uint8_t reg, uint8_t &data){
	return HAL_I2C_Mem_Read(&handle, PCF85363A_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef PCF85363A::WriteRegister(uint8_t reg, uint8_t &data){
	return HAL_I2C_Mem_Write(&handle, PCF85363A_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
}

int PCF85363A::GetSeconds(){
	HAL_StatusTypeDef status;
	uint8_t data;
	status = ReadRegister(PCF85363A_REG_SECS, data);

	if (status != HAL_OK){
		return 100;
	}

	else {
		uint8_t tens = (data & 0b01110000) >> 4;
		uint8_t digits = data & 0b00001111;
		return tens * 10 + digits;
	}
}

