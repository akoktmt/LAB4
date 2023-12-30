/*
 * TESTER.h
 *
 *  Created on: Dec 10, 2023
 *      Author: win 10
 */

#ifndef TESTER_H_
#define TESTER_H_
#include <stdio.h>
#include <stdint.h>

#define DATAIDHIGH 0x01
#define DATAIDLOW 0x23

#define DATAREQUESTSID 0X22
#define REQUESTID 0X712

#define NUMBEROFDATA 0x02
//
#define WRITEDATAID 0X2E
#define RECORDDATAIDHIHG 0X01
#define RECORDDATALOW 0X23
//
//
#define SEREQUESTID 0X27
#define SESEEDLEVEL 0x01
#define SERESPONSEID 0X67
typedef struct{
	uint8_t ReadDataID;
	uint8_t ReadDataIDHigh;
	uint8_t ReadDataLow;
}TesterRequesttypedef;

typedef struct{
	uint8_t WriteData_RequestSID;
	uint8_t Record_Highbyte;
	uint8_t Record_Lowbyte;
}TesterWriteDataRequesttypedef;
//

typedef struct{
	uint8_t Security_SID;
	uint8_t Security_Level;
}RequestSeedTypedef;

typedef struct{
	uint32_t Seed_0;
	uint32_t Seed_1;
	uint32_t Seed_2;
	uint32_t Seed_3;
}Seedtypedef;

typedef struct{
	uint32_t Key_0;
	uint32_t Key_1;
	uint32_t Key_2;
	uint32_t Key_3;
	uint32_t Key_4;
	uint32_t Key_5;
	uint32_t Key_6;
	uint32_t Key_7;
	uint32_t Key_8;
	uint32_t Key_9;
	uint32_t Key_10;
	uint32_t Key_11;
	uint32_t Key_12;
	uint32_t Key_13;
	uint32_t Key_14;
	uint32_t Key_15;
}Keytypedef;

void Tester_RequestInit(TesterRequesttypedef *Tester);
void Tester_WriteDataIDInit(TesterWriteDataRequesttypedef*Tester);
//
void Tester_SendRquestSeedInit(RequestSeedTypedef *Tester);
void KeyandSeedCompute(Keytypedef* Key , Seedtypedef * Seed);

#endif /* TESTER_H_ */
