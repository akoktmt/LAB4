/*
 * ECU.c
 *
 *  Created on: Dec 10, 2023
 *      Author: win 10
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ECU.h"

void initializeRandomSeed() {
    srand((unsigned int)time(NULL));
}
unsigned int getRandomNumber(unsigned int min, unsigned int max) {
    static int seedInitialized = 0;
    if (!seedInitialized) {
        initializeRandomSeed();
        seedInitialized = 1;
    }

    return min + rand() % (max - min + 1);
}
void ECU_PosResponseInit(ECU_PosResponse *ECU){
	ECU->ResponseSID=POSITIVE;
	ECU->RecordHighByte=0;
	ECU->RecordLowByte=0;
}
void ECU_NegResponseInit(ECU_NegResponse *ECU){

	ECU->NegativeResponseID=NEGATIVE;
	ECU->ResponseCode=0;
	ECU->ResponseSID=RESPONSESID;
}

void ECU_PosWriteResponseInit(WriteDataID_Positive *ECU){
	ECU->WriteDataSID=WRITEDATAPOS;
}
void ECU_NegWriteResponseInit(WriteDataID_Negative* ECU){
	ECU->NegativeDID=WRITEDATANEG;
	ECU->NegativeInvalidLength=INVALIDREQUESTLEGNTH;
	ECU->Write_NegResponseSID=WRITEDATARESPONSESID;
	ECU->Write_NegResponse=WRITEDATANEG;
}

void ResponseSeedInit(ResponseSEEDtypedef *ECU){
	ECU->ResponseID = SERESPONSEID;
	ECU->SecurityLevel =SESEEDLEVEL;
	ECU->Seed_0=0;
	ECU->Seed_1=0;
	ECU->Seed_2=0;
	ECU->Seed_3=0;
}
void NegativeResponseInit(NegativeResponsetypedef *ECU){
	ECU->NegativeResponse=WRITEDATANEG;
	ECU->ResponseSID=SEREQUESTID;
	ECU->NegativeResponseCode=0;
}
