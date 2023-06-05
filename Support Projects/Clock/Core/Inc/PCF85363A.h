/*
 * PCF85363A.h
 *
 *  Created on: Mar 20, 2023
 *      Author: hle
 */

#ifndef INC_PCF85363A_H_
#define INC_PCF85363A_H_

#include "stm32f0xx_hal.h"

#define PCF85363A_I2C_ADDR (0x51 << 1) //1010001 in binary, 9.3.1 in datasheet, left bit shift to allow RW LSB


#define PCF85363A_REG_BATSWITCH 0x26
#define PCF85363A_REG_FUNCTION 0x28
#define PCF85363A_REG_RESETS 0x2F


//RTC MODE

#define PCF85363A_REG_100THSECS 0x00
#define PCF85363A_REG_SECS 0x01
#define PCF85363A_REG_MINS 0x02
#define PCF85363A_REG_HOURS 0x03
#define PCF85363A_REG_DAYS 0x04
#define PCF85363A_REG_WEEKDAYS 0x05
#define PCF85363A_REG_MONTHS 0x06
#define PCF85363A_REG_YEARS 0x07

using namespace std;
#include <vector>

class PCF85363A{

	I2C_HandleTypeDef& handle;

	public:
		PCF85363A(I2C_HandleTypeDef &i2cHandle);

		std::vector<int> GetTime();
		void SetFunction(bool mode);
		void Reset();
		int GetSeconds();

	private:
		HAL_StatusTypeDef ReadRegister(uint8_t reg, uint8_t &data);
		HAL_StatusTypeDef WriteRegister(uint8_t reg, uint8_t &data);

};



#endif /* INC_PCF85363A_H_ */
