/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "isotp.h"
#include "TESTER.h"
#include "ECU.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_CAN_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  CAN_Config_filtering();
  HAL_CAN_Start(&hcan);
//
//  TesterRequesttypedef Tester;
//  ECU_PosResponse PosECU;
//  ECU_NegResponse NegECU;
//
//  Tester_RequestInit(&Tester);
//  ECU_PosResponseInit(&PosECU);
//  ECU_NegResponseInit(&NegECU);
//
//  TesterWriteDataRequesttypedef WTester;
//  WriteDataID_Negative NECU;
//  WriteDataID_Positive PECU;
//  Tester_WriteDataIDInit(&WTester);
//  ECU_NegWriteResponseInit(&NECU);
//  ECU_PosWriteResponseInit(&PECU);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t RequestData[3]={0};
  RequestData[0]= Tester.ReadDataID;
  RequestData[1]= Tester.ReadDataIDHigh;
  RequestData[2]= Tester.ReadDataLow;


  uint8_t PosResponse[5]={0};
  uint8_t NegResponse[3]={0};

  uint8_t HandleFlag=0;

  uint8_t WrtieDataRequest[3]={0};
  WrtieDataRequest[0]=WTester.WriteData_RequestSID;
  WrtieDataRequest[1]=WTester.Record_Highbyte;
  WrtieDataRequest[2]=WTester.Record_Lowbyte;

  uint8_t Positive_WriteResponse[1];
  uint8_t Negative_WriteResponse[3];

//SEND
  RequestSeedTypedef ReSeed;
  Tester_SendRquestSeedInit(&ReSeed);
  uint8_t RequestSeed[2]={0};
  RequestSeed[0]=ReSeed.Security_SID;
  RequestSeed[1]=ReSeed.Security_Level;
  Seedtypedef SendSeed;
  Keytypedef SendKey;
//REC
  ResponseSEEDtypedef Seed;
  ResponseSeedInit(&Seed);
  Seed.Seed_0 =getRandomNumber(0,4294967295);
  Seed.Seed_1 =getRandomNumber(0,4294967295);
  Seed.Seed_2 =getRandomNumber(0,4294967295);
  Seed.Seed_3 =getRandomNumber(0,4294967295);
  uint8_t ECU_ResponseSeed[6]={0};
  ECU_ResponseSeed[0]=Seed.ResponseID;
  ECU_ResponseSeed[1]=Seed.SecurityLevel;
  ECU_ResponseSeed[2]=Seed.Seed_0;
  ECU_ResponseSeed[3]=Seed.Seed_1;
  ECU_ResponseSeed[4]=Seed.Seed_2;
  ECU_ResponseSeed[5]=Seed.Seed_3;
//
  uint8_t rcData[8]={0};
  uint8_t size=0;
  uint32_t ID=0;
  uint8_t ret;
  char msg[50];

  static IsoTpLink g_link;
  static uint8_t g_isotpRecvBuf[50];
  static uint8_t g_isotpSendBuf[50];
  uint8_t SESendKey[18]={0};
  isotp_init_link(&g_link, REQUESTID ,g_isotpSendBuf, sizeof(g_isotpSendBuf), g_isotpRecvBuf, sizeof(g_isotpRecvBuf));
//
  uint8_t FIRequest=0;
  uint16_t sizebuf=18;
  uint8_t RquestOK=0;
  uint8_t ReponseOK=0;
  uint8_t SendKeyOK=0;
  //
  NegativeResponsetypedef NegReponse;
  NegativeResponseInit(&NegReponse);
  uint8_t NegReponseSE[3]={0};
  NegReponseSE[0]=NegReponse.NegativeResponse;
  NegReponseSE[1]=NegReponse.NegativeResponse;
  uint32_t id;
  uint8_t rcdata[8];
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  /* If receive any interested can message, call isotp_on_can_message to handle message */

////
	  	  	    KeyandSeedCompute(&SendKey, &SendSeed);
	  			SESendKey[0]=SEREQUESTID;
	  			SESendKey[1] = SESEEDLEVEL;
	  			SESendKey[2] = SendKey.Key_0;
	  			SESendKey[3] = SendKey.Key_1;
	  			SESendKey[4] = SendKey.Key_2;
	  			SESendKey[5] = SendKey.Key_3;
	  			SESendKey[6] = SendKey.Key_4;
	  			SESendKey[7] = SendKey.Key_5;
	  			SESendKey[8] = SendKey.Key_6;
	  			SESendKey[9] = SendKey.Key_7;
	  			SESendKey[10] = SendKey.Key_8;
	  			SESendKey[11] = SendKey.Key_9;
	  			SESendKey[12] = SendKey.Key_10;
	  			SESendKey[13] = SendKey.Key_11;
	  			SESendKey[14] = SendKey.Key_12;
	  			SESendKey[15] = SendKey.Key_13;
	  			SESendKey[16] = SendKey.Key_14;
	  			SESendKey[17] = SendKey.Key_15;
	  			ret=isotp_send(&g_link, SESendKey, sizeof(SESendKey));
		  	isotp_poll(&g_link);
	  		ret = CAN_RecData(&ID, rcData, &size);
	  		if (HAL_OK == ret && REQUESTID == ID) {
	  			isotp_on_can_message(&g_link, rcData, size);
	  		}
	  		ret = isotp_receive(&g_link, g_isotpRecvBuf, sizeof(g_isotpRecvBuf),
	  				&sizebuf);
	  		if (ISOTP_RET_OK == ret) {
	  			uint32_t len = sprintf(msg," ECU OK \r\n");
	  			HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
	  			if(g_isotpRecvBuf[0]==SEREQUESTID){
	  				ReponseOK=1;
	  			}
	  		}
	  				if(ReponseOK==1)
	  				{
	  					isotp_send(&g_link, ECU_ResponseSeed, sizeof(ECU_ResponseSeed));
	  				}
	  		KeyandSeedCompute(&SendKey, &SendSeed);
	  		if(g_link.receive_size==18){
	  		 if (g_isotpRecvBuf[0] != SendKey.Key_0 || g_isotpRecvBuf[1] != SendKey.Key_1 || g_isotpRecvBuf[2] != SendKey.Key_2 ||
	  		        g_isotpRecvBuf[3] != SendKey.Key_3 || g_isotpRecvBuf[4] != SendKey.Key_4 || g_isotpRecvBuf[5] != SendKey.Key_5 ||
	  		        g_isotpRecvBuf[6] != SendKey.Key_6 || g_isotpRecvBuf[7] != SendKey.Key_7 || g_isotpRecvBuf[8] != SendKey.Key_8 ||
	  		        g_isotpRecvBuf[9] != SendKey.Key_9 || g_isotpRecvBuf[10] != SendKey.Key_10 || g_isotpRecvBuf[11] != SendKey.Key_11 ||
	  		        g_isotpRecvBuf[12] != SendKey.Key_12 || g_isotpRecvBuf[13] != SendKey.Key_13 || g_isotpRecvBuf[14] != SendKey.Key_14 ||
	  		        g_isotpRecvBuf[15] != SendKey.Key_15) {
	  			 	 NegReponseSE[3]=INVALIDKEY;
	  			 	 isotp_send(&g_link, NegReponseSE, sizeof(NegReponseSE));

	  		 }
	  		 else
	  		 {
	  			uint32_t len = sprintf(msg," ECU KEY OK \r\n");
	  			HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
	  		 }
	  		}
	  if(FIRequest==0)
		ret = isotp_send(&g_link, RequestSeed, sizeof(RequestSeed));
		FIRequest=1;
	  }
		ret = CAN_RecData(&ID, rcData, &size);
		if (HAL_OK == ret && RESPONSE == ID) {
			isotp_on_can_message(&g_link, rcData, size);
		}
//		HAL_Delay(1);
//		ret = isotp_receive(&g_link, g_isotpRecvBuf, sizeof(g_isotpRecvBuf),
//				&sizebuf);
//		if (ISOTP_RET_OK == ret) {
//			if(g_isotpRecvBuf[0]==SERESPONSEID){
//				ReponseOK=1;
//				SendSeed.Seed_0=g_isotpRecvBuf[2];
//				SendSeed.Seed_1=g_isotpRecvBuf[3];
//				SendSeed.Seed_2=g_isotpRecvBuf[4];
//				SendSeed.Seed_3=g_isotpRecvBuf[5];
//			}
//		}
//		if(ReponseOK==1)
//		{
//			KeyandSeedCompute(&SendKey, &SendSeed);
//			SESendKey[0]=SEREQUESTID;
//			SESendKey[1] = SESEEDLEVEL;
//			SESendKey[2] = SendKey.Key_0;
//			SESendKey[3] = SendKey.Key_1;
//			SESendKey[4] = SendKey.Key_2;
//			SESendKey[5] = SendKey.Key_3;
//			SESendKey[6] = SendKey.Key_4;
//			SESendKey[7] = SendKey.Key_5;
//			SESendKey[8] = SendKey.Key_6;
//			SESendKey[9] = SendKey.Key_7;
//			SESendKey[10] = SendKey.Key_8;
//			SESendKey[11] = SendKey.Key_9;
//			SESendKey[12] = SendKey.Key_10;
//			SESendKey[13] = SendKey.Key_11;
//			SESendKey[14] = SendKey.Key_12;
//			SESendKey[15] = SendKey.Key_13;
//			SESendKey[16] = SendKey.Key_14;
//			SESendKey[17] = SendKey.Key_15;
//			ret=isotp_send(&g_link, SESendKey, sizeof(SESendKey));
//			while(g_link.send_status == ISOTP_SEND_STATUS_INPROGRESS){
//			isotp_poll(&g_link);
//			}
//			if(ISOTP_RET_OK == ret){
//				uint32_t len = sprintf(msg," Tester SercurityOK \r\n");
//				HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
//			}
//		}
//	  ret = CAN_RecData(&ID, rcData, &size);
//	 	  	  if (HAL_OK == ret && ReSponseID == ID) {
//	 	  	                 isotp_on_can_message(&g_link, rcData, size);
//	 	  	      }
//	 	  	  ret = isotp_receive(&g_link, g_isotpRecvBuf, sizeof(g_isotpRecvBuf),&sizebuf);
//	 	  	             if (ISOTP_RET_OK == ret) {
//	 	  	            	 if(g_isotpRecvBuf[0]==SERESPONSEID)
//	 	  	            	 {
//	 	  	            		 KeyandSeedCompute(&SendKey, &SendSeed);
//	 	  	            		SESendKey[0]=SEREQUESTID;
//	 	  	            		SESendKey[1]=SESEEDLEVEL;
//	 	  	            		SESendKey[2]=SendKey.Key_0;
//	 	  	            		SESendKey[3]=SendKey.Key_1;
//	 	  	            		SESendKey[4]=SendKey.Key_2;
//	 	  	            		SESendKey[5]=SendKey.Key_3;
//	 	  	            		SESendKey[6]=SendKey.Key_4;
//	 	  	            		SESendKey[7]=SendKey.Key_5;
//	 	  	            		SESendKey[8]=SendKey.Key_6;
//	 	  	            		SESendKey[9]=SendKey.Key_7;
//	 	  	            		SESendKey[10]=SendKey.Key_8;
//	 	  	            		SESendKey[11]=SendKey.Key_9;
//	 	  	            		SESendKey[12]=SendKey.Key_10;
//	 	  	            		SESendKey[13]=SendKey.Key_11;
//	 	  	            		SESendKey[14]=SendKey.Key_12;
//	 	  	            		SESendKey[15]=SendKey.Key_13;
//	 	  	            		SESendKey[16]=SendKey.Key_14;
//	 	  	            		SESendKey[17]=SendKey.Key_15;
//	 	  	            		 isotp_send(&g_link, SESendKey, sizeof(SESendKey));
//	 	  	            	 }
//	 	  	             }
//	 	  	          isotp_poll(&g_link);
	 	  	                 /* Handle received message */
	   //	ret = isotp_send(&g_link, WrtieDataRequest, sizeof(WrtieDataRequest));
//	HAL_Delay(1000);
	  	  ret = CAN_RecData(&ID, rcData, &size);
	  	  if (HAL_OK == ret && REQUESTID == ID) {
	  	                 isotp_on_can_message(&g_link, rcData, size);
	  	      }
	  	  ret = isotp_receive(&g_link, g_isotpRecvBuf, sizeof(g_isotpRecvBuf),&sizebuf);
	  	             if (ISOTP_RET_OK == ret) {
	  	                 /* Handle received message */
	  	            	 if(g_isotpRecvBuf[0]!=WRITEDATAID)
	  	            	 {
	  //	            		 uint32_t len = sprintf(msg,"ECU Receive Data: %x %x %x, ID TESTER : %ld\r\n",g_isotpRecvBuf[0],g_isotpRecvBuf[1],g_isotpRecvBuf[2],g_link.receive_arbitration_id);
	  	            		 uint32_t len = sprintf(msg," : ECU RequestPositive \r\n");
	  	            		 HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
	  	            		 Positive_WriteResponse[0]=PECU.WriteDataSID;
	  	            		 HandleFlag = POSITIVE;
	  	            	 }
	  	            	 else
	  	            	 {
	  	            		 uint32_t len = sprintf(msg," : ECU NegPositive \r\n");
	  	            		 HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
	  	            		Negative_WriteResponse[0]=NECU.Write_NegResponse;
	  	            		Negative_WriteResponse[1]=NECU.Write_NegResponseSID;
	  	            		if(g_link.receive_buf_size >4 ){
	  	            			Negative_WriteResponse[2]=NECU.NegativeInvalidLength;
	  	            		}else {
	  	            			Negative_WriteResponse[2]=NECU.NegativeDID;
	  	            		}
	  	            		 HandleFlag = NEGATIVE;
	  	            	 }
	  	             }
	  	             HAL_Delay(1);
	  	        if(HandleFlag==POSITIVE){
	  	        	ret = isotp_send_with_id(&g_link, 0x7A2, Positive_WriteResponse, sizeof(Positive_WriteResponse));
	  	        	if (ISOTP_RET_OK != ret) {
	  	        		uint32_t len = sprintf(msg," : ECU TransmitFail \r\n");
	  	        		HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
	  	        	}
	  	       }else {
	  	    	   ret = isotp_send_with_id(&g_link, 0x7A2, Negative_WriteResponse, sizeof(Negative_WriteResponse));
	         		if (ISOTP_RET_OK != ret) {
	         		uint32_t len = sprintf(msg," : ECU TransmitFail \r\n");
	         		HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
	         	}
	  	   }
//	  ret = isotp_send(&g_link, RequestData, sizeof(RequestData));
//	  HAL_Delay(1000);

//	  ret = CAN_RecData(&ID, rcData, &size);
//	  if (HAL_OK == ret && REQUESTID == ID) {
//	                 isotp_on_can_message(&g_link, rcData, size);
//	      }
//	  ret = isotp_receive(&g_link, g_isotpRecvBuf, sizeof(g_isotpRecvBuf),&sizebuf);
//	             if (ISOTP_RET_OK == ret) {
//	                 /* Handle received message */
//	            	 if(g_isotpRecvBuf[0]!=DATAREQUESTSID)
//	            	 {
////	            		 uint32_t len = sprintf(msg,"ECU Receive Data: %x %x %x, ID TESTER : %ld\r\n",g_isotpRecvBuf[0],g_isotpRecvBuf[1],g_isotpRecvBuf[2],g_link.receive_arbitration_id);
//	            		 uint32_t len = sprintf(msg," : ECU RequestPositive \r\n");
//	            		 HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
//	            		 PosResponse[0]=POSITIVE;
//	            		 PosResponse[1]=g_isotpRecvBuf[1];
//	            		 PosResponse[2]=g_isotpRecvBuf[2];
//	            		 PosResponse[3]=REQUESTDATAHIGH;
//	            		 PosResponse[4]=REQUESTDATALOW;
//	            		 HandleFlag = POSITIVE;
//	            	 }
//	            	 else
//	            	 {
//	            		 uint32_t len = sprintf(msg," : ECU NegPositive \r\n");
//	            		 HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
//	            		 NegResponse[0]=NEGATIVE;
//	            		 NegResponse[1]=RESPONSESID;
//	            		 NegResponse[2]=RESPONSEFORMAT;
//	            		 HandleFlag = NEGATIVE;
//	            	 }
//	             }
//	             HAL_Delay(1);
//	        if(HandleFlag==POSITIVE){
//	        	ret = isotp_send_with_id(&g_link, 0x7A2, NegResponse, sizeof(NegResponse));
//	        	if (ISOTP_RET_OK != ret) {
//	        		uint32_t len = sprintf(msg," : ECU TransmitFail \r\n");
//	        		HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
//	        	}
//	       }else {
//	    	   ret = isotp_send_with_id(&g_link, 0x7A2, NegResponse, sizeof(NegResponse));
//       		if (ISOTP_RET_OK != ret) {
//       		uint32_t len = sprintf(msg," : ECU TransmitFail \r\n");
//       		HAL_UART_Transmit(&huart2,(uint8_t*) msg, len, HAL_MAX_DELAY);
//       	}
//	   }
//	   sprintf(msg,"ID: %d, Data: %d %d %d %d, Size: %d \r\n",ID,rcData[0],rcData[1],rcData[2],rcData[3],size);
//	 		  HAL_UART_Transmit(&huart1,(uint8_t*) msg, sizeof(msg), HAL_MAX_DELAY);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
