/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct MPU6050_struct
{
	HAL_StatusTypeDef Status;
	uint8_t ID;
	double Accel_X;
	double Accel_Y;
	double Accel_Z;
	double Gyro_X;
	double Gyro_Y;
	double Gyro_Z;
	double Temperature;
} MPU6050_struct;

typedef struct SI1145_struct
{
	HAL_StatusTypeDef Status;
	uint8_t ID;
	double UV;
	uint16_t IR;
	uint16_t VIS;
}SI1145_struct;

typedef struct BME280_struct
{
	HAL_StatusTypeDef Status;
	uint8_t ID;
	double Temperature;
	double Pressure;
	double Pressure_ref;
	double Humidity;
	double Altitude;
} BME280_struct;

typedef struct Sensors_struct
{
	struct BME280_struct BME280_External;
	struct BME280_struct BME280_Internal;
	struct MPU6050_struct MPU650;
	struct SI1145_struct SI1145;
} Sensors_struct;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ROPE_CUT_EN_Pin GPIO_PIN_1
#define ROPE_CUT_EN_GPIO_Port GPIOA
#define SD_CS_Pin GPIO_PIN_4
#define SD_CS_GPIO_Port GPIOA
#define CAM2_OK_Pin GPIO_PIN_1
#define CAM2_OK_GPIO_Port GPIOB
#define CAM1_OK_Pin GPIO_PIN_2
#define CAM1_OK_GPIO_Port GPIOB
#define USER_LED3_Pin GPIO_PIN_12
#define USER_LED3_GPIO_Port GPIOB
#define USER_LED5_Pin GPIO_PIN_13
#define USER_LED5_GPIO_Port GPIOB
#define USER_LED2_Pin GPIO_PIN_14
#define USER_LED2_GPIO_Port GPIOB
#define USER_LED4_Pin GPIO_PIN_15
#define USER_LED4_GPIO_Port GPIOB
#define USER_LED1_Pin GPIO_PIN_8
#define USER_LED1_GPIO_Port GPIOA
#define BUS_SEL_1_Pin GPIO_PIN_11
#define BUS_SEL_1_GPIO_Port GPIOA
#define BUS_SEL_2_Pin GPIO_PIN_12
#define BUS_SEL_2_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_15
#define BUZZER_GPIO_Port GPIOA
#define CAM2_START_Pin GPIO_PIN_4
#define CAM2_START_GPIO_Port GPIOB
#define CAM2_START_EXTI_IRQn EXTI4_IRQn
#define CAM1_START_Pin GPIO_PIN_5
#define CAM1_START_GPIO_Port GPIOB
#define CAM1_START_EXTI_IRQn EXTI9_5_IRQn
#define CAM2_ON_Pin GPIO_PIN_8
#define CAM2_ON_GPIO_Port GPIOB
#define CAM1_ON_Pin GPIO_PIN_9
#define CAM1_ON_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
