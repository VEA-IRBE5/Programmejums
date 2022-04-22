/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "BME280_lib.h"
#include "MPU6050_Lib.h"
#include "SI1145_lib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* Buffer sizes */
#define UART_Buffer_size 50		// 2B command or nB data


/* Rope cut and sleep mode defines */
#define ROPE_NOT_CUT 0
#define ROPE_CUTTING 1
#define ROPE_CUT_DONE 2

#define ROPE_CUT_TIME 10			// in seconds
#define LOWER_ALTITUDE_LIMIT 1000 	// in meters
#define UPPER_ALTITUDE_LIMIT 28000 	// in meters
#define ALTITUDE_UPDATE_PERIOD 30	// in seconds


/* Sensor related defines */
#define I2C_BUS_SEL_BMEs 0
#define I2C_BUS_SEL_MPU__SI 1
#define I2C_handle_BME_ex__SI hi2c1
#define I2C_handle_BME_in__MPU hi2c2
#define I2C_short_timeout 20
#define I2C_long_timeout 200
#define PRESSURE_REFERENCE 100	//kpa at sea level, varies by location and weather


/* SD card related defines */
#define SD_MAX_RETRIES 5


/* Camera related defines */
#define CAM_NOK 0
#define CAM_OK 1
#define CAM_NREC 0
#define CAM_REC 1
#define CAM_STARTUP_TIME 6	// x*5 seconds

///* Timeout error defines */
//#define Timeout_none 0
//#define Timeout_SDcard 1
//#define Timeout_COM_uart 2
//#define Timeout_sensors 3

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define ARRAY_LENGTH(x) sizeof(x)/sizeof(x[0])

///* Timeout macros */
//#define Set_Timeout_Delay_ms(ms) __HAL_TIM_SET_AUTORELOAD(&htim2, ms)
//#define Start_Timeout __HAL_TIM_SET_COUNTER(&htim2, 0); HAL_TIM_Base_Start_IT(&htim2)
//#define Stop_Timeout HAL_TIM_Base_Stop_IT(&htim2)

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim9;
TIM_HandleTypeDef htim10;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* SD card handling variables */
FATFS fs;
FATFS *pfs;
FIL fil;
FRESULT fres;
DWORD fre_clust;
volatile uint32_t totalSpace, freeSpace;
char buffer[100];
volatile FRESULT sd_status;
volatile uint8_t sd_mounted;
volatile uint8_t sd_file_cnt;
volatile uint8_t sd_error_cnt;


/* System core and misc variables */
volatile uint8_t Is_asleep;
volatile uint8_t Rope_cut_delay, Rope_cut_status;
char message[] = "--test-please-ignore--";


/* Sensor data storage variables */
Sensors_struct Sensors;
char Data_to_send[UART_Buffer_size];

volatile uint16_t Cycle_runtime_last;
volatile uint16_t Cycle_runtime_min;
volatile uint16_t Cycle_runtime_max;

RTC_TimeTypeDef Current_Time;
RTC_DateTypeDef Current_Date;
volatile double Altitude_max;



/* UART1 specific */
uint8_t UART1_TxBuf[UART_Buffer_size];
uint8_t UART1_RxBuf[UART_Buffer_size];
uint8_t UART1_DataBuf[UART_Buffer_size];
volatile uint8_t UART1_RxIsData;
volatile uint8_t UART1_RxBytes;


/* UART2 specific */
uint8_t UART2_TxBuf[UART_Buffer_size];
uint8_t UART2_RxBuf[UART_Buffer_size];
uint8_t UART2_DataBuf[UART_Buffer_size];
volatile uint8_t UART2_RxIsData;
volatile uint8_t UART2_RxBytes;


/* CAM specific */
typedef struct CAM_struct
{
	GPIO_TypeDef *ON_PORT;
	uint16_t ON_PIN;
	GPIO_TypeDef *OK_PORT;
	uint16_t OK_PIN;
	GPIO_TypeDef *START_PORT;
	uint16_t START_PIN;
	TIM_HandleTypeDef *TIM;
	uint8_t REC_STATUS;
	uint8_t Do_Restart;
	uint8_t Do_EXTI;
	uint8_t Startup_delay;
} CAM_struct;

CAM_struct CAM_1;
CAM_struct CAM_2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM3_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM9_Init(void);
static void MX_TIM10_Init(void);
/* USER CODE BEGIN PFP */

void I2C_Select_bus(uint8_t select);
uint8_t Get_System_Status();
void Get_BME280_in_all_readings();
void Get_BME280_ex_all_readings();
void Get_MPU6050_all_readings();
void Get_SI1145_all_readings();
uint8_t Mount_open_SD_Card();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


uint8_t Get_System_Status()
{
	uint8_t status = 0;

	if(Is_asleep == 1)
		status |= 1 << 8;
	if(Sensors.BME280_Internal.Status == HAL_OK)
		status |= 1 << 6;
	if(Sensors.BME280_External.Status == HAL_OK)
		status |= 1 << 5;
	if(Sensors.MPU650.Status == HAL_OK)
		status |= 1 << 4;
	if(Sensors.SI1145.Status == HAL_OK)
		status |= 1 << 3;
	if(sd_status == FR_OK)
		status |= 1 << 2;
	if(CAM_1.REC_STATUS == CAM_REC)
		status |= 1 << 1;
	if(CAM_2.REC_STATUS == CAM_REC)
		status |= 1;

	return status;
}
/*
 * Use defined I2C_BUS_SEL_ for input
 * anything not defined (above 1) deselects both
 */
void I2C_Select_bus(uint8_t select)
{
	switch(select)
	{
	case I2C_BUS_SEL_BMEs:
		HAL_GPIO_WritePin(BUS_SEL_1_GPIO_Port, BUS_SEL_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(BUS_SEL_2_GPIO_Port, BUS_SEL_2_Pin, GPIO_PIN_RESET);
		break;

	case I2C_BUS_SEL_MPU__SI:
		HAL_GPIO_WritePin(BUS_SEL_2_GPIO_Port, BUS_SEL_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(BUS_SEL_1_GPIO_Port, BUS_SEL_1_Pin, GPIO_PIN_RESET);
		break;

	default:
		HAL_GPIO_WritePin(BUS_SEL_1_GPIO_Port, BUS_SEL_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(BUS_SEL_2_GPIO_Port, BUS_SEL_2_Pin, GPIO_PIN_SET);
		break;
	}
}


void Get_BME280_in_all_readings()
{
	I2C_Select_bus(I2C_BUS_SEL_BMEs);
	Sensors.BME280_Internal.Status = BME280_Get_ID(I2C_handle_BME_in__MPU, &Sensors.BME280_Internal.ID, I2C_short_timeout);
	if(Sensors.BME280_Internal.Status != HAL_OK)
		return;
	Sensors.BME280_Internal.Status = BME280_Get_All(I2C_handle_BME_in__MPU, I2C_long_timeout);
	if(Sensors.BME280_Internal.Status != HAL_OK)
		return;

	Sensors.BME280_Internal.Temperature = BME280_T_Double(&BME280_internal_Calib_Data);
	Sensors.BME280_Internal.Pressure = BME280_P_Double(&BME280_internal_Calib_Data);
	Sensors.BME280_Internal.Humidity = BME280_H_Double(&BME280_internal_Calib_Data);
	Sensors.BME280_Internal.Altitude = BME280_Altitude_Double(Sensors.BME280_Internal.Pressure, Sensors.BME280_Internal.Pressure_ref);
}


void Get_BME280_ex_all_readings()
{
	I2C_Select_bus(I2C_BUS_SEL_BMEs);
	Sensors.BME280_External.Status = BME280_Get_ID(I2C_handle_BME_ex__SI, &Sensors.BME280_External.ID, I2C_short_timeout);
	if(Sensors.BME280_External.Status != HAL_OK)
		return;
	Sensors.BME280_External.Status = BME280_Get_All(I2C_handle_BME_ex__SI, I2C_long_timeout);
	if(Sensors.BME280_External.Status != HAL_OK)
		return;

	Sensors.BME280_External.Temperature = BME280_T_Double(&BME280_external_Calib_Data);
	Sensors.BME280_External.Pressure = BME280_P_Double(&BME280_external_Calib_Data);
	Sensors.BME280_External.Humidity = BME280_H_Double(&BME280_external_Calib_Data);
	Sensors.BME280_External.Altitude = BME280_Altitude_Double(Sensors.BME280_External.Pressure, Sensors.BME280_External.Pressure_ref);
}


void Get_MPU6050_all_readings()
{
	I2C_Select_bus(I2C_BUS_SEL_MPU__SI);
	Sensors.MPU650.Status = MPU6050_read_ID(I2C_handle_BME_in__MPU, &Sensors.MPU650.ID, I2C_short_timeout);
	if(Sensors.MPU650.Status != HAL_OK)
		return;
	Sensors.MPU650.Status = MPU6050_read_All(I2C_handle_BME_in__MPU, I2C_long_timeout);
	if(Sensors.MPU650.Status != HAL_OK)
		return;

	MPU6050_Accel_double(&Sensors.MPU650);
	MPU6050_Gyro_double(&Sensors.MPU650);
	MPU6050_Temp_double(&Sensors.MPU650);
}


void Get_SI1145_all_readings()
{
	I2C_Select_bus(I2C_BUS_SEL_MPU__SI);
	Sensors.SI1145.Status = SI1145_read_ID(I2C_handle_BME_ex__SI, &Sensors.SI1145.ID, I2C_short_timeout);
	if(Sensors.SI1145.Status != HAL_OK)
		return;
	Sensors.SI1145.Status = SI1145_Read_Data(I2C_handle_BME_ex__SI, I2C_long_timeout);
	if(Sensors.SI1145.Status != HAL_OK)
		return;

	Sensors.SI1145.VIS = SI1145_VIS_raw();
	Sensors.SI1145.IR = SI1145_IR_raw();
	Sensors.SI1145.UV = SI1145_UV_double();
}


/* Returns FR_status after success or last failed step */
uint8_t Mount_open_SD_Card()
{
	uint8_t sd_mounting_status;

	/* Mount SD Card */
	sd_mounting_status = f_mount(&fs, "", 1);
	if(sd_mounting_status != FR_OK)
		return sd_mounting_status;

	/* Open file to write */
	sd_mounting_status = f_open(&fil, "Data0.txt", FA_OPEN_ALWAYS | FA_WRITE);
	if(sd_mounting_status != FR_OK)
		return sd_mounting_status;

	/* Check freeSpace space */
	sd_mounting_status = f_getfree("", &fre_clust, &pfs);
	if(sd_mounting_status != FR_OK)
		return sd_mounting_status;
	totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
	freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);

	/* free space is less than 1kb */
	if(freeSpace < 1)
	{
		sd_mounting_status = 0xDF;
		return sd_mounting_status;
	}

	/* Writing header text */
	f_printf(&fil, "STM32 SD Card data logger\n");
	f_printf(&fil, "RTC time and sensor readings (SI VIS and SI IR are raw values)\n");
	f_printf(&fil, "SD-CARD-MEMORY = %d \n SD-CARD-FREE-MEMORY = %d\n", totalSpace, freeSpace);
	f_printf(&fil, "| Dt | Hr | Mn | Sc |");
	f_printf(&fil, " BME_in T | BME_in P | BME_in H | BME_in A |");
	f_printf(&fil, " BME_ex T | BME_ex P | BME_ex H | BME_in A |");
	f_printf(&fil, " MPU Acc_X | MPU Acc_Y | MPU Acc_Z | MPU Gyr_X | MPU Gyr_Y | MPU Gyr_Z | MPU Tmpr  |");
	f_printf(&fil, " SI VIS | SI IR  | SI UV  |\n");
	sd_mounting_status = f_sync(&fil);
	return sd_mounting_status;
}


void CAM_ON(CAM_struct *CAM)
{
	// Checks if CAM is OFF
	if(HAL_GPIO_ReadPin(CAM->OK_PORT, CAM->OK_PIN) == 0)
	{
		HAL_GPIO_WritePin(CAM->ON_PORT, CAM->ON_PIN, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(CAM->ON_PORT, CAM->ON_PIN, GPIO_PIN_RESET);
		CAM->Startup_delay = CAM_STARTUP_TIME;
	}
	// Start heartbeat monitoring
	CAM->Do_EXTI = 1;
}


void CAM_START(CAM_struct *CAM)
{
	// Checks if CAM is ON and not recording
	if((CAM->REC_STATUS == CAM_NREC) && (HAL_GPIO_ReadPin(CAM->OK_PORT, CAM->OK_PIN) == 1) && (CAM->Startup_delay == 0))
	{
		HAL_GPIO_WritePin(CAM->OK_PORT, CAM->OK_PIN, GPIO_PIN_RESET);
		HAL_Delay(30);
		HAL_GPIO_WritePin(CAM->OK_PORT, CAM->OK_PIN, GPIO_PIN_SET);
	}

	if(HAL_GPIO_ReadPin(CAM->OK_PORT, CAM->OK_PIN) == 0)
		CAM_ON(CAM);

	// Start filming restart routine
	CAM->Do_Restart = 1;
}


void CAM_STOP(CAM_struct *CAM)
{
	// Checks if CAM is recording
	if(CAM->REC_STATUS == CAM_REC)
	{
		HAL_GPIO_WritePin(CAM->OK_PORT, CAM->OK_PIN, GPIO_PIN_RESET);
		HAL_Delay(30);
		HAL_GPIO_WritePin(CAM->OK_PORT, CAM->OK_PIN, GPIO_PIN_SET);
		CAM->REC_STATUS = CAM_NREC;
	}

	// Stop filming restart routine
	CAM->Do_Restart = 0;
}


void CAM_OFF(CAM_struct *CAM)
{
	// checks if CAM is ON
	if(HAL_GPIO_ReadPin(CAM->OK_PORT, CAM->OK_PIN))
	{
		HAL_GPIO_WritePin(CAM->ON_PORT, CAM->ON_PIN, GPIO_PIN_RESET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(CAM->ON_PORT, CAM->ON_PIN, GPIO_PIN_SET);
	}
	// Stop heartbeat monitoring
	CAM->Do_EXTI = 0;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_RTC_Init();
  MX_FATFS_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM5_Init();
  MX_TIM9_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */


  /*---------------Core systems setup--------------------*/
	Is_asleep = 0;
	Rope_cut_status = ROPE_NOT_CUT;
	Rope_cut_delay = ROPE_CUT_TIME;
	Cycle_runtime_last = 0;
	Cycle_runtime_min = 0xFFFF;
	Cycle_runtime_max = 0;

	// Get RTC time (date must be read as well for proper updating or something)
	HAL_RTC_GetTime(&hrtc, &Current_Time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &Current_Date, RTC_FORMAT_BIN);


  /*------------------SD card setup----------------------*/
	/* Wait for SD module reset */
	HAL_Delay(2000);

	sd_file_cnt = 0;
	sd_error_cnt = 0;
	sd_mounted = 0;
	sd_status = Mount_open_SD_Card();

	while(sd_status == FR_NOT_READY)
		sd_status = Mount_open_SD_Card();

	if(sd_status == FR_OK)
		sd_mounted = 1;
	else
	{
		UART1_TxBuf[0] = 0xD0;
		UART1_TxBuf[1] = sd_status;
		HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);
	}


  /*------------------Sensors init-----------------------*/
	Sensors.BME280_Internal.Pressure_ref = PRESSURE_REFERENCE;
	Sensors.BME280_External.Pressure_ref = PRESSURE_REFERENCE;


	/* Wait for Sensor power-on */
	HAL_Delay(1000);

	I2C_Select_bus(I2C_BUS_SEL_BMEs);
	Sensors.BME280_Internal.Status = BME280_Get_ID(I2C_handle_BME_in__MPU, &Sensors.BME280_Internal.ID, I2C_short_timeout);
	if (Sensors.BME280_Internal.Status == HAL_OK)
	{
		Sensors.BME280_Internal.Status = BME280_Init(I2C_handle_BME_in__MPU, I2C_short_timeout);
		Sensors.BME280_Internal.Status = BME280_Calib_Read(I2C_handle_BME_in__MPU, &BME280_internal_Calib_Data, I2C_long_timeout);
		Get_BME280_in_all_readings();
	}


	I2C_Select_bus(I2C_BUS_SEL_BMEs);
	Sensors.BME280_External.Status = BME280_Get_ID(I2C_handle_BME_ex__SI, &Sensors.BME280_External.ID, I2C_short_timeout);
	if (Sensors.BME280_External.Status == HAL_OK)
	{
		Sensors.BME280_External.Status = BME280_Init(I2C_handle_BME_ex__SI, I2C_short_timeout);
		Sensors.BME280_External.Status = BME280_Calib_Read(I2C_handle_BME_ex__SI, &BME280_external_Calib_Data, I2C_long_timeout);
		Get_BME280_ex_all_readings();
	}


	I2C_Select_bus(I2C_BUS_SEL_MPU__SI);
	Sensors.MPU650.Status = MPU6050_read_ID(I2C_handle_BME_in__MPU, &Sensors.MPU650.ID, I2C_short_timeout);
	if (Sensors.MPU650.Status == HAL_OK)
	{
		Sensors.MPU650.Status = MPU6050_Init(I2C_handle_BME_in__MPU, I2C_short_timeout);
		Get_MPU6050_all_readings();
	}


	I2C_Select_bus(I2C_BUS_SEL_MPU__SI);
	Sensors.SI1145.Status = SI1145_Init(I2C_handle_BME_ex__SI, I2C_short_timeout);
	if (Sensors.SI1145.Status == HAL_OK)
	{
		Sensors.SI1145.Status = SI1145_read_ID(I2C_handle_BME_ex__SI, &Sensors.SI1145.ID, I2C_short_timeout);
		Get_SI1145_all_readings();
	}


  /*--------Max altitude read from stabilised data-------*/
	Get_BME280_ex_all_readings();
	Altitude_max = Sensors.BME280_External.Altitude;


  /*---------------UART receiver setup-------------------*/
	UART1_RxIsData = 0;
	UART1_RxBytes = 2;
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == 0);
	HAL_UART_Receive_IT(&huart1, UART1_RxBuf, 2);

	UART2_RxIsData = 0;
	UART2_RxBytes = 2;
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 0);
	HAL_UART_Receive_IT(&huart2, UART2_RxBuf, 2);

	UART1_TxBuf[0] = 0x00;
	UART1_TxBuf[1] = Get_System_Status();
	HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);


  /*------------------Start timers-----------------------*/
	HAL_TIM_Base_Start_IT(&htim3);	// Sensor read cycle timer
	HAL_TIM_Base_Start_IT(&htim4);	// Flashes LEDs

	HAL_TIM_Base_Start_IT(&htim5);	// CAM1 heartbeat timer
	HAL_TIM_Base_Start_IT(&htim9);	// CAM2 heartbeat timer


  /*----------------- Camera init ----------------------*/
	CAM_1.OK_PIN = CAM1_OK_Pin;
	CAM_1.OK_PORT = CAM1_OK_GPIO_Port;
	CAM_1.ON_PIN = CAM1_ON_Pin;
	CAM_1.ON_PORT = CAM1_ON_GPIO_Port;
	CAM_1.START_PIN = CAM1_START_Pin;
	CAM_1.START_PORT = CAM1_START_GPIO_Port;
	CAM_1.REC_STATUS = CAM_NREC;
	CAM_1.TIM = &htim5;
	CAM_1.Do_Restart = 0;
	CAM_1.Do_EXTI = 0;
	CAM_1.Startup_delay = CAM_STARTUP_TIME;

	CAM_2.OK_PIN = CAM2_OK_Pin;
	CAM_2.OK_PORT = CAM2_OK_GPIO_Port;
	CAM_2.ON_PIN = CAM2_ON_Pin;
	CAM_2.ON_PORT = CAM2_ON_GPIO_Port;
	CAM_2.START_PIN = CAM2_START_Pin;
	CAM_2.START_PORT = CAM2_START_GPIO_Port;
	CAM_2.REC_STATUS = CAM_NREC;
	CAM_2.TIM = &htim9;
	CAM_2.Do_Restart = 0;
	CAM_2.Do_EXTI = 0;
	CAM_2.Startup_delay = CAM_STARTUP_TIME;

	CAM_ON(&CAM_1);
	CAM_ON(&CAM_2);
	CAM_START(&CAM_1);
	CAM_START(&CAM_2);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(UART1_RxIsData == 0)
		  UART1_RxBytes = 2;
	  if(UART2_RxIsData == 0)
		  UART2_RxBytes = 2;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 16000;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */
  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 16000;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 500;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 16000;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 5000;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief TIM9 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM9_Init(void)
{

  /* USER CODE BEGIN TIM9_Init 0 */

  /* USER CODE END TIM9_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM9_Init 1 */

  /* USER CODE END TIM9_Init 1 */
  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 16000;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 5000;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM9_Init 2 */

  /* USER CODE END TIM9_Init 2 */

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 16000;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 1000;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ROPE_CUT_EN_Pin|SD_CS_Pin|USER_LED1_Pin|BUZZER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, CAM2_OK_Pin|CAM1_OK_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, USER_LED3_Pin|USER_LED5_Pin|USER_LED2_Pin|USER_LED4_Pin
                          |CAM2_ON_Pin|CAM1_ON_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, BUS_SEL_1_Pin|BUS_SEL_2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : ROPE_CUT_EN_Pin SD_CS_Pin USER_LED1_Pin BUS_SEL_1_Pin
                           BUS_SEL_2_Pin */
  GPIO_InitStruct.Pin = ROPE_CUT_EN_Pin|SD_CS_Pin|USER_LED1_Pin|BUS_SEL_1_Pin
                          |BUS_SEL_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : CAM2_OK_Pin CAM1_OK_Pin */
  GPIO_InitStruct.Pin = CAM2_OK_Pin|CAM1_OK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : USER_LED3_Pin USER_LED5_Pin USER_LED2_Pin USER_LED4_Pin
                           CAM2_ON_Pin CAM1_ON_Pin */
  GPIO_InitStruct.Pin = USER_LED3_Pin|USER_LED5_Pin|USER_LED2_Pin|USER_LED4_Pin
                          |CAM2_ON_Pin|CAM1_ON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BUZZER_Pin */
  GPIO_InitStruct.Pin = BUZZER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUZZER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CAM2_START_Pin CAM1_START_Pin */
  GPIO_InitStruct.Pin = CAM2_START_Pin|CAM1_START_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	// Core cycle, runs every 1s
	if (htim == &htim3)
	{
		uint16_t tickstart = HAL_GetTick();

		// Get RTC time (date must be read as well for proper updating or something)
		HAL_RTC_GetTime(&hrtc, &Current_Time, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &Current_Date, RTC_FORMAT_BIN);


		// Get all sensor readings
		Get_BME280_in_all_readings();
		Get_BME280_ex_all_readings();
		Get_MPU6050_all_readings();
		Get_SI1145_all_readings();


		if(Sensors.BME280_External.Altitude > Altitude_max)
			Altitude_max = Sensors.BME280_External.Altitude;

		// Check if probe has fallen below altitude limit for going to sleep mode
		if((Altitude_max > LOWER_ALTITUDE_LIMIT+200) && (Sensors.BME280_External.Altitude < LOWER_ALTITUDE_LIMIT))
		{
			HAL_TIM_Base_Stop_IT(&htim3);
			HAL_TIM_Base_Start_IT(&htim10);
			Is_asleep = 1;
		}


		// Max altitude rope cut condition
		if((Sensors.BME280_External.Altitude > UPPER_ALTITUDE_LIMIT) && (Rope_cut_status != ROPE_CUTTING))
		{
			Rope_cut_status = ROPE_CUTTING;
			Rope_cut_delay = ROPE_CUT_TIME;
		}


		// Rope cut control
		if(Rope_cut_status == ROPE_CUTTING)
		{
			if(Rope_cut_delay > 0)
			{
				Rope_cut_delay--;
				HAL_GPIO_WritePin(ROPE_CUT_EN_GPIO_Port, ROPE_CUT_EN_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(ROPE_CUT_EN_GPIO_Port, ROPE_CUT_EN_Pin, GPIO_PIN_RESET);
				Rope_cut_status = ROPE_CUT_DONE;
			}
		}


		// Prepare data string that will be sent to COM
		memset(Data_to_send, 0, sizeof(Data_to_send));
		Data_to_send[0] = ',';
		if(Sensors.BME280_Internal.Status == HAL_OK)
		{
			char TempStr[20];
			sprintf(TempStr, "%.2f", Sensors.BME280_Internal.Temperature);
			strcat(Data_to_send, TempStr);
		}
		else
			sprintf(Data_to_send, "--");


		if(Sensors.BME280_External.Status == HAL_OK)
		{
			char TempStr[20];
			sprintf(TempStr, ",%.2f,%d", Sensors.BME280_External.Temperature, (int16_t)Sensors.BME280_External.Altitude);
			strcat(Data_to_send, TempStr);
		}
		else
			strcat(Data_to_send, ",--,--");


		if(Sensors.SI1145.Status == HAL_OK)
		{
			char TempStr[10];
			sprintf(TempStr, ",%.2f", Sensors.SI1145.UV);
			strcat(Data_to_send, TempStr);
		}
		else
			strcat(Data_to_send, ",--");


		// Write to file and sync current file addition with physical SD card
		if((sd_mounted == 1) && (sd_status == FR_OK))
		{
			sd_error_cnt = 0;
			f_printf(&fil, "| %2u | %2u | %2u | %2u |", Current_Date.Date, Current_Time.Hours, Current_Time.Minutes, Current_Time.Seconds);


			if(Sensors.BME280_Internal.Status == HAL_OK)
			{
				char TempStr[100];
				sprintf(TempStr, " %8.3f | %8.3f | %8.3f | %8.1f |", Sensors.BME280_Internal.Temperature, Sensors.BME280_Internal.Pressure, Sensors.BME280_Internal.Humidity, Sensors.BME280_Internal.Altitude);
				f_printf(&fil, TempStr);
			}
			else
				for(uint8_t i = 0; i < 3; i++)
					f_printf(&fil, "    N/A    |");


			if(Sensors.BME280_External.Status == HAL_OK)
			{
				char TempStr[100];
				sprintf(TempStr, " %8.3f | %8.3f | %8.3f | %8.1f |", Sensors.BME280_External.Temperature, Sensors.BME280_External.Pressure, Sensors.BME280_External.Humidity, Sensors.BME280_External.Altitude);
				f_printf(&fil, TempStr);
			}
			else
				for(uint8_t i = 0; i < 3; i++)
					f_printf(&fil, "    N/A    |");


			if(Sensors.MPU650.Status == HAL_OK)
			{
				char TempStr[100];
				sprintf(TempStr, " %9.3f | %9.3f | %9.3f |", Sensors.MPU650.Accel_X, Sensors.MPU650.Accel_Y, Sensors.MPU650.Accel_Z);
				f_printf(&fil, TempStr);
				sprintf(TempStr, " %9.3f | %9.3f | %9.3f | %9.3f |", Sensors.MPU650.Gyro_X, Sensors.MPU650.Gyro_Y, Sensors.MPU650.Gyro_Z, Sensors.MPU650.Temperature);
				f_printf(&fil, TempStr);
			}
			else
				for(uint8_t i = 0; i < 7; i++)
					f_printf(&fil, "      N/A     |");


			if(Sensors.SI1145.Status == HAL_OK)
			{
				char TempStr[100];
				sprintf(TempStr, " %6d | %6d | %6.2f |", Sensors.SI1145.VIS, Sensors.SI1145.IR, Sensors.SI1145.UV);
				f_printf(&fil, TempStr);
			}
			else
				for(uint8_t i = 0; i < 3; i++)
					f_printf(&fil, "  N/A   |");


			f_printf(&fil, "\n");
			sd_status = f_sync(&fil);
		}


		// If an SD card error has occured, attempt to remount card and write to a new file
		// After too many attempts the card is considered inoperable
		if((sd_status != FR_OK) && (sd_error_cnt <= SD_MAX_RETRIES))
		{
			sd_status = f_mount(NULL, "", 1);
			sd_status = f_mount(&fs, "", 1);
			if(sd_status == FR_OK)
			{
				sd_error_cnt = 0;
				sd_mounted = 1;
				sd_file_cnt++;

				char TempStr[12];
				sprintf(TempStr, "Data%d.txt", sd_file_cnt);
				sd_status = f_open(&fil, TempStr, FA_OPEN_ALWAYS | FA_WRITE);
			}
			else
				sd_error_cnt++;

			if(sd_error_cnt > SD_MAX_RETRIES)
			{
				UART1_TxBuf[0] = 0xD0;
				UART1_TxBuf[1] = sd_status;
				HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);
				sd_mounted = 0;
			}
		}


		// Cycle runtime logging
		uint16_t Cycle_runtime = HAL_GetTick() - tickstart;
		if(Cycle_runtime > Cycle_runtime_max)
			Cycle_runtime_max = Cycle_runtime;
		if(Cycle_runtime < Cycle_runtime_min)
			Cycle_runtime_min = Cycle_runtime;
		Cycle_runtime_last = Cycle_runtime;
	}



	// LED flasher
	if (htim == &htim4)
	{
		  // Status display for subsystems
		  if((sd_mounted == 1) && (sd_status == FR_OK))
			  HAL_GPIO_TogglePin(USER_LED1_GPIO_Port, USER_LED1_Pin);
		  else
			  HAL_GPIO_WritePin(USER_LED1_GPIO_Port, USER_LED1_Pin, GPIO_PIN_RESET);

		  if(Sensors.BME280_Internal.Status == HAL_OK)
			  HAL_GPIO_TogglePin(USER_LED4_GPIO_Port, USER_LED4_Pin);
		  else
			  HAL_GPIO_WritePin(USER_LED4_GPIO_Port, USER_LED4_Pin, GPIO_PIN_RESET);

		  if(Sensors.BME280_External.Status == HAL_OK)
			  HAL_GPIO_TogglePin(USER_LED2_GPIO_Port, USER_LED2_Pin);
		  else
			  HAL_GPIO_WritePin(USER_LED2_GPIO_Port, USER_LED2_Pin, GPIO_PIN_RESET);

		  if(Sensors.MPU650.Status == HAL_OK)
			  HAL_GPIO_TogglePin(USER_LED5_GPIO_Port, USER_LED5_Pin);
		  else
			  HAL_GPIO_WritePin(USER_LED5_GPIO_Port, USER_LED5_Pin, GPIO_PIN_RESET);

		  if(Sensors.SI1145.Status == HAL_OK)
			  HAL_GPIO_TogglePin(USER_LED3_GPIO_Port, USER_LED3_Pin);
		  else
			  HAL_GPIO_WritePin(USER_LED3_GPIO_Port, USER_LED3_Pin, GPIO_PIN_RESET);
	}



	// Camera_1 recording restart
	if (htim == CAM_1.TIM)
	{
		CAM_1.REC_STATUS = CAM_NREC;

		if(CAM_1.Startup_delay > 0)
			CAM_1.Startup_delay--;

		if(CAM_1.Do_Restart)
			CAM_START(&CAM_1);
	}

	// Camera_2 recording restart
	if (htim == CAM_2.TIM)
	{
		CAM_2.REC_STATUS = CAM_NREC;

		if(CAM_2.Startup_delay > 0)
			CAM_2.Startup_delay--;

		if(CAM_2.Do_Restart)
			CAM_START(&CAM_2);
	}


	// Buzzer control
	if (htim == &htim10)
	{
		if((Current_Time.Seconds == 30) || (Current_Time.Seconds == 0))
			HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
	}
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	if((GPIO_PIN == CAM1_START_Pin) && CAM_1.Do_EXTI && (CAM_1.Startup_delay == 0))
	{
		CAM_1.REC_STATUS = CAM_REC;
		HAL_TIM_Base_Stop_IT(CAM_1.TIM);
		__HAL_TIM_SET_COUNTER(CAM_1.TIM, 1);
		HAL_TIM_Base_Start_IT(CAM_1.TIM);
	}

	if((GPIO_PIN == CAM2_START_Pin) && CAM_2.Do_EXTI && (CAM_2.Startup_delay == 0))
	{
		CAM_2.REC_STATUS = CAM_REC;
		HAL_TIM_Base_Stop_IT(CAM_2.TIM);
		__HAL_TIM_SET_COUNTER(CAM_2.TIM, 1);
		HAL_TIM_Base_Start_IT(CAM_2.TIM);
	}
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	// UART1 connects to the bluetooth module for debugging
	if (huart == &huart1)
	{

		if (UART1_RxIsData == 1)
		{
			for (uint8_t i = 0; i < UART1_RxBytes; i++)
				UART1_DataBuf[i] = UART1_RxBuf[i];

			// Reply with status after data is received
			UART1_TxBuf[0] = 0x00;
			UART1_TxBuf[1] = Get_System_Status();
			HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);
			UART1_RxIsData = 0;
			UART1_RxBytes = 2;
			HAL_UART_Receive_IT(&huart1, UART1_RxBuf, 2);
		}

		else
		{
			volatile uint8_t Command = UART1_RxBuf[0];
			volatile uint8_t Parameter = UART1_RxBuf[1];
			uint16_t temp;
			RTC_TimeTypeDef sTime;
			RTC_DateTypeDef sDate;


			if(Command != 0x02)
			{
				UART1_RxBytes = 2;
				HAL_UART_Receive_IT(&huart1, UART1_RxBuf, 2);
			}

			switch(Command)
			{
			// Status received from bluetooth
			case 0x00:
			break;


			// Send status to bluetooth
			case 0x01:
				UART1_TxBuf[0] = 0x00;
				UART1_TxBuf[1] = Get_System_Status();
				HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);
			break;


			// Receive data from bluetooth
			case 0x02:
				UART1_RxIsData = 1;
				UART1_RxBytes = Parameter;
				HAL_UART_Receive_IT(&huart1, UART1_RxBuf, Parameter);
			break;


			// Send data to bluetooth
			case 0x03:
				if (Parameter == 0)
				{
					temp = ARRAY_LENGTH(message);
					UART1_TxBuf[0] = 0x02;
					UART1_TxBuf[1] = temp;
					for(uint8_t i = 0; i < temp; i++)
						UART1_TxBuf[2+i] = message[i];
					HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2+temp);
				}
				else
				{
					UART1_TxBuf[0] = 0x02;
					UART1_TxBuf[1] = Parameter;
					for(uint8_t i = 0; i < Parameter; i++)
						UART1_TxBuf[2+i] = UART1_DataBuf[i];
					HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2+Parameter);
				}
			break;


			// Buzzer toggle
			case 0x41:
				HAL_GPIO_TogglePin(BUZZER_GPIO_Port, BUZZER_Pin);
			break;


			// Set RTC from received data
			case 0x42:
				sTime.Seconds = UART2_DataBuf[0];
				sTime.Minutes = UART2_DataBuf[1];
				sTime.Hours = UART2_DataBuf[2];
				sDate.Date = UART2_DataBuf[3];
				sDate.Month = UART2_DataBuf[4];
				sDate.Year = UART2_DataBuf[5];
				HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
				HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
			break;


			// Cut rope toggle
			case 0x4F:
				if((Parameter == 0xCC) && (Rope_cut_status != ROPE_CUTTING))
				{
					Rope_cut_status = ROPE_CUTTING;
					Rope_cut_delay = ROPE_CUT_TIME;
				}
			break;


			// Request status from COM
			case 0xC0:
				UART2_TxBuf[0] = 0x01;
				UART2_TxBuf[1] = 0x00;
				HAL_UART_Transmit_IT(&huart2, UART2_TxBuf, 2);
			break;


			// Send data from bluetooth buffer to COM
			case 0xC1:
				UART2_TxBuf[0] = 0x02;
				UART2_TxBuf[1] = Parameter;
				for(uint8_t i = 0; i < Parameter; i++)
					UART2_TxBuf[2+i] = UART1_DataBuf[i];
				HAL_UART_Transmit_IT(&huart2, UART2_TxBuf, 2+Parameter);
			break;


			// Request data from COM
			case 0xC2:
				UART2_TxBuf[0] = 0x03;
				UART2_TxBuf[1] = Parameter;
				HAL_UART_Transmit_IT(&huart2, UART2_TxBuf, 2);
			break;


			// Send data from COM buffer to bluetooth
			case 0xC3:
				UART1_TxBuf[0] = 0x02;
				UART1_TxBuf[1] = Parameter;
				for(uint8_t i = 0; i < Parameter; i++)
					UART1_TxBuf[2+i] = UART2_DataBuf[i];
				HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2+Parameter);
			break;


			// Mount SD card and start writing to it
			case 0xC4:
				if (sd_mounted == 0)
				{
					sd_status = Mount_open_SD_Card();
					sd_file_cnt = 0;
					if (sd_status == FR_OK)
						sd_mounted = 1;

					/* Send SD status after opening*/
					UART1_TxBuf[0] = 0xD0;
					UART1_TxBuf[1] = sd_status;
					HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);
				}
				else
				{
					/* Inform that SD is already mounted*/
					UART1_TxBuf[0] = 0xD0;
					UART1_TxBuf[1] = 0xD1;
					HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);
				}
			break;


			// Close file on SD card and unmount it
			case 0xC5:
				if (sd_mounted == 1)
				{
					/* Close file and unmount SD card */
					sd_status = f_close(&fil);
					sd_status = f_mount(NULL, "", 1);
					sd_mounted = 0;

					/* Send SD unmounting status */
					UART1_TxBuf[0] = 0xD0;
					UART1_TxBuf[1] = sd_status;
					HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);
				}
			else
				{
					/* Inform that SD is already unmounted*/
					UART1_TxBuf[0] = 0xD0;
					UART1_TxBuf[1] = 0xD0;
					HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);
				}
			break;


			// Set TIM4 period to value received from bluetooth and restart it
			case 0xC6:
				temp = 0;
				for (uint8_t i = 0; i < 4; i++)
					temp += UART1_DataBuf[i] << ((3 - i)*8);
				HAL_TIM_Base_Stop_IT(&htim4);
				if(temp > 0)
				{
					__HAL_TIM_SET_AUTORELOAD(&htim4, temp);
					__HAL_TIM_SET_COUNTER(&htim4, 0);
					HAL_TIM_Base_Start_IT(&htim4);
				}
			break;


			// Get and send all sensor IDs
			case 0xC7:
				UART1_TxBuf[0] = 0xD1;
				UART1_TxBuf[1] = Sensors.BME280_Internal.ID;
				UART1_TxBuf[2] = Sensors.BME280_External.ID;
				UART1_TxBuf[3] = Sensors.MPU650.ID;
				UART1_TxBuf[4] = Sensors.SI1145.ID;
				HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 5);
			break;


			// Send last read cycle min/max/last runtimes in ms
			case 0xC8:
				UART1_TxBuf[0] = 0xD2;
				UART1_TxBuf[1] = Cycle_runtime_min >> 8;
				UART1_TxBuf[2] = Cycle_runtime_min & 0x00FF;
				UART1_TxBuf[3] = Cycle_runtime_max >> 8;
				UART1_TxBuf[4] = Cycle_runtime_max & 0x00FF;
				UART1_TxBuf[5] = Cycle_runtime_last >> 8;
				UART1_TxBuf[6] = Cycle_runtime_last & 0x00FF;
				HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 7);
			break;


			// Set BME280 reference pressure from received data
			case 0xC9:
				temp = UART1_DataBuf[1] >> 8 | UART1_DataBuf[0];
				Sensors.BME280_Internal.Pressure_ref = 90 + (((double)temp)/1000);
				Sensors.BME280_External.Pressure_ref = 90 + (((double)temp)/1000);
			break;


			// Start cameras
			case 0xCA:
				CAM_START(&CAM_1);
				CAM_START(&CAM_2);
			break;


			// Stop cameras
			case 0xCB:
				CAM_STOP(&CAM_1);
				CAM_STOP(&CAM_2);
			break;



			default:
			break;
			}
		}
		memset(UART1_RxBuf, 0, UART_Buffer_size);
	}


	// UART2 connects to the COM computer
	if (huart == &huart2)
	{
		if (UART2_RxIsData == 1)
		{
			for (uint8_t i = 0; i < UART2_RxBytes; i++)
				UART2_DataBuf[i] = UART2_RxBuf[i];
			UART2_RxIsData = 0;
			UART2_RxBytes = 2;
			HAL_UART_Receive_IT(&huart2, UART2_RxBuf, 2);
		}
		else
		{
			volatile uint8_t Command = UART2_RxBuf[0];
			volatile uint8_t Parameter = UART2_RxBuf[1];
			RTC_TimeTypeDef sTime;
			RTC_DateTypeDef sDate;


			if(Command != 0x02)
			{
				UART2_RxBytes = 2;
				HAL_UART_Receive_IT(&huart2, UART2_RxBuf, 2);
			}

			switch(Command)
			{

			// Status received from COM, pass it to bluetooth
			case 0x00:
				UART1_TxBuf[0] = 0x00;
				UART1_TxBuf[1] = Parameter;
				HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);
			break;

			// Send status to COM
			case 0x01:
				UART2_TxBuf[0] = 0x00;
				UART2_TxBuf[1] = Get_System_Status();
				HAL_UART_Transmit_IT(&huart2, UART2_TxBuf, 2);
			break;

			// Receive data from COM
			case 0x02:
				UART2_RxIsData = 1;
				UART2_RxBytes = Parameter;
				HAL_UART_Receive_IT(&huart2, UART2_RxBuf, Parameter);
			break;

			// Send data to COM
			case 0x03:
				if(Parameter == 0x99)
				{
					uint8_t temp;
					Data_to_send[0] = ',';
					temp = strlen(Data_to_send);
					UART2_TxBuf[0] = 0x02;
					UART2_TxBuf[1] = temp+1;
					UART2_TxBuf[2] = Get_System_Status();
					for(uint8_t i = 0; i < temp; i++)
						UART2_TxBuf[3+i] = Data_to_send[i];
					HAL_UART_Transmit_IT(&huart2, UART2_TxBuf, 3+temp);
				}
			break;

			// Set RTC from received data
			case 0x42:
				sTime.Seconds = UART2_DataBuf[0];
				sTime.Minutes = UART2_DataBuf[1];
				sTime.Hours = UART2_DataBuf[2];
				sDate.Date = UART2_DataBuf[3];
				sDate.Month = UART2_DataBuf[4];
				sDate.Year = UART2_DataBuf[5];
				HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
				HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
			break;

			// Start rope cutting
			case 0x4F:
				if((Parameter == 0xCC) && (Rope_cut_status != ROPE_CUTTING))
				{
					Rope_cut_status = ROPE_CUTTING;
					Rope_cut_delay = ROPE_CUT_TIME;
				}
			break;

			default:
			break;
			}
		}
		memset(UART2_RxBuf, 0, UART_Buffer_size);
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		HAL_UART_Receive_IT(&huart1, UART1_RxBuf, UART1_RxBytes);
	}

	if(huart == &huart2)
	{
		HAL_UART_Receive_IT(&huart2, UART2_RxBuf, UART2_RxBytes);
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
	UART1_TxBuf[0] = 0xEE;
	UART1_TxBuf[1] = Get_System_Status();
	HAL_UART_Transmit_IT(&huart1, UART1_TxBuf, 2);
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

