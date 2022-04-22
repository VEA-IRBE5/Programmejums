/*
 * SI1145_lib.c
 *
 *  Created on: Jan 16, 2022
 *      Author: Aleksandra
 */
#include "SI1145_lib.h"

uint8_t UCOEF[] = {0x7B, 0x6B, 0x01, 0x00};
uint8_t Calib_data[12];	// Unused

struct SI1145_read SI1145_raw_data;

HAL_StatusTypeDef SI1145_Init(I2C_HandleTypeDef handle, uint16_t Timeout)
{
	HAL_StatusTypeDef status;
	uint8_t data[2];


	// Mandatory before any I2C operations with this sensor
	data[0] = 0x17;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_HW_KEY, 1, data, 1, Timeout);
	if(status != HAL_OK)
		return status;


	// Software reset
	data[0] = SI1145_CMD_RESET;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_COMMAND, 1, data, 1, Timeout);
	HAL_Delay(30);
	data[0] = 0x17;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_HW_KEY, 1, data, 1, Timeout);
	if(status != HAL_OK)
		return status;


	// Set measure rate to 999 ms (thus, in theory, each 1000th reading has a risk of having hybrid data)
	// 124*256 + 224 = 31744
	// 31968 * 31.25us = 999ms
	data[0] = 224;	//LSB
	data[1] = 124;	//MSB
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_MEAS_RATE_L, 1, data, 4, Timeout);
	if(status != HAL_OK)
		return status;


	// UCOEF configuration
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_UCOEF0, 1, UCOEF, 4, Timeout*2);
	if(status != HAL_OK)
		return status;


	// VIS_RANGE set to high
	data[0] = 0b00100000;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_PARAM_WR, 1, data, 1, Timeout);
	data[0] = SI1145_CMD_writeRAM | SI1145_RAM_VIS_ADC_MISC;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_COMMAND, 1, data, 1, Timeout);
	if(status != HAL_OK)
		return status;


	// IR_RANGE set to high
	data[0] = 0b00000000;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_PARAM_WR, 1, data, 1, Timeout);
	data[0] = SI1145_CMD_writeRAM | SI1145_RAM_IR_ADC_MISC;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_COMMAND, 1, data, 1, Timeout);
	if(status != HAL_OK)
		return status;


	// Read calib data
	data[0] = SI1145_CMD_GET_CAL;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_COMMAND, 1, data, 1, Timeout);
	status = HAL_I2C_Mem_Read(&handle, SI1145_Address, SI1145_VIS_DATA_L , 1, Calib_data, 12, Timeout*6);
	if(status != HAL_OK)
		return status;


	// Enable UV, IR and VIS sensors
	data[0] = 0b10110000;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_PARAM_WR, 1, data, 1, Timeout);
	data[0] = SI1145_CMD_writeRAM | SI1145_RAM_CHLIST;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_COMMAND, 1, data, 1, Timeout);
	if(status != HAL_OK)
		return status;


	// Start autorun measurement
	data[0] = SI1145_ALS_AUTO;
	status = HAL_I2C_Mem_Write(&handle, SI1145_Address, SI1145_COMMAND, 1, data, 1, Timeout);
	return status;
}



HAL_StatusTypeDef SI1145_read_ID(I2C_HandleTypeDef handle, uint8_t *ptr_ID, uint16_t Timeout)
{
	return HAL_I2C_Mem_Read(&handle, SI1145_Address, SI1145_PART_ID, 1, ptr_ID, 1, Timeout);
}



HAL_StatusTypeDef SI1145_Read_Data(I2C_HandleTypeDef handle, uint16_t Timeout)
{
	HAL_StatusTypeDef status;
	uint8_t data[12];

	status = HAL_I2C_Mem_Read(&handle, SI1145_Address, SI1145_VIS_DATA_L , 1, data, 12, Timeout);
	if(status != HAL_OK)
		return status;

	SI1145_raw_data.VIS = data[1] << 8 | data[0];
	SI1145_raw_data.IR = data[3] << 8 | data[2];
	SI1145_raw_data.UV = data[11] << 8 | data[10];

	return status;
}



uint16_t SI1145_IR_raw()
{
	return SI1145_raw_data.IR;
}


uint16_t SI1145_VIS_raw()
{
	return SI1145_raw_data.VIS;
}


double SI1145_UV_double()
{
	return (double)SI1145_raw_data.UV / 100;
}




