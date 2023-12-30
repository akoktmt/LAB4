/*
 * ECU.h
 *
 *  Created on: Dec 10, 2023
 *      Author: win 10
 */

#ifndef ECU_H_
#define ECU_H_

#define RESPONSE 0x7A2

#define POSITIVE 0x62
#define NEGATIVE 0X7F

#define RESPONSESID 0X22
#define INVALIDLENGTH 0x13
#define RESPONSEFORMAT 0X13

#define REQUESTDATAHIGH 0X07
#define REQUESTDATALOW 0XA2
//
#define WRITEDATAPOS 0X6E
#define WRITEDATANEG 0X7F
#define WRITEDATARESPONSESID 0X2E
#define INVALIDREQUESTLEGNTH 0X13
#define DIDNOTSUPPORT 0X31
//
#define SERESPONSEID 0X67
#define SESEEDLEVEL 0x01
#define SEREQUESTID 0x27
#define INVALIDKEY 0x35
typedef struct {
	uint8_t ResponseSID;
	uint8_t RecordHighByte;
	uint8_t RecordLowByte;
}ECU_PosResponse;

typedef struct {
	uint8_t NegativeResponseID;
	uint8_t ResponseSID;
	uint8_t ResponseCode;
}ECU_NegResponse;
//

typedef struct{
	uint8_t WriteDataSID;
}WriteDataID_Positive;

typedef struct{
	uint8_t Write_NegResponse;
	uint8_t Write_NegResponseSID;
	uint8_t NegativeInvalidLength;
	uint8_t NegativeDID;
}WriteDataID_Negative;
//
typedef struct{
	uint8_t ResponseID;
	uint8_t SecurityLevel;
	uint8_t Seed_0;
	uint8_t Seed_1;
	uint8_t Seed_2;
	uint8_t Seed_3;
}ResponseSEEDtypedef;

typedef struct {
	uint8_t NegativeResponse;
	uint8_t ResponseSID;
	uint8_t NegativeResponseCode;
}NegativeResponsetypedef;

void ECU_PosResponseInit(ECU_PosResponse *ECU);
void ECU_NegResponseInit(ECU_NegResponse *ECU);
//
void ECU_PosWriteResponseInit(WriteDataID_Positive *ECU);
void ECU_NegWriteResponseInit(WriteDataID_Negative* ECU);
//
void ResponseSeedInit(ResponseSEEDtypedef *ECU);
void NegativeResponseInit(NegativeResponsetypedef *ECU);
#endif /* ECU_H_ */
