/*
 * SI1145_lib.h
 *
 *  Created on: Jan 16, 2022
 *      Author: Aleksandra
 */

#ifndef INC_SI1145_LIB_H_
#define INC_SI1145_LIB_H_

#include "main.h"

#define SI1145_Address 		0x60 << 1

// Register offsets
#define SI1145_PART_ID 		0x00
#define SI1145_IRQ_ENABLE	0x04
#define SI1145_HW_KEY 		0x07
#define SI1145_MEAS_RATE_L 	0x08
#define SI1145_MEAS_RATE_H 	0x09
#define SI1145_UCOEF0		0x13
#define SI1145_UCOEF1		0x14
#define SI1145_UCOEF2		0x15
#define SI1145_UCOEF3		0x16
#define SI1145_PARAM_WR 	0x17
#define SI1145_COMMAND 		0x18
#define SI1145_VIS_DATA_L	0x22
#define SI1145_VIS_DATA_H	0x23
#define SI1145_IR_DATA_L 	0x24
#define SI1145_IR_DATA_H 	0x25
// 3 Prox sensor data goes between these
#define SI1145_UV_DATA_L	0x2C
#define SI1145_UV_DATA_H	0x2D
#define SI1145_PARAM_RD 	0x2E
#define SI1145_CHIP_STAT 	0x30

// Commands
#define SI1145_CMD_writeRAM 	0xA0
#define SI1145_CMD_readRAM 		0x80
#define SI1145_CMD_RESET		0x01
#define SI1145_CMD_GET_CAL		0x12
#define SI1145_CMD_NOP			0x00
#define SI1145_CMD_ALS_FORCE	0x06
#define SI1145_CMD_RESET		0x01
#define SI1145_ALS_AUTO			0x0E

// RAM offsets
#define SI1145_RAM_CHLIST			0x01
#define SI1145_RAM_VIS_ADC_MISC		0x12
#define SI1145_RAM_IR_ADC_MISC		0x1F



typedef struct SI1145_read
{
	uint16_t UV;
	uint16_t IR;
	uint16_t VIS;
}SI1145_read;


HAL_StatusTypeDef SI1145_Init(I2C_HandleTypeDef handle, uint16_t Timeout);
HAL_StatusTypeDef SI1145_read_ID(I2C_HandleTypeDef handle, uint8_t *ptr_ID, uint16_t Timeout);
HAL_StatusTypeDef SI1145_Read_Data(I2C_HandleTypeDef handle, uint16_t Timeout);

uint16_t SI1145_VIS_raw();
uint16_t SI1145_IR_raw();
double SI1145_UV_double();

#endif /* INC_SI1145_LIB_H_ */
