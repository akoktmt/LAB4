/*
 * TESTER.c
 *
 *  Created on: Dec 10, 2023
 *      Author: win 10
 */
#include "TESTER.h"

void Tester_RequestInit(TesterRequesttypedef *Tester){
	Tester->ReadDataID=DATAREQUESTSID;
	Tester->ReadDataIDHigh=DATAIDHIGH;
	Tester->ReadDataLow=DATAIDLOW;
}

void Tester_WriteDataIDInit(TesterWriteDataRequesttypedef *Tester){
	Tester->Record_Highbyte=RECORDDATAIDHIHG;
	Tester->Record_Lowbyte=RECORDDATALOW;
	Tester->WriteData_RequestSID=WRITEDATAID;
}
//
void Tester_SendRquestSeedInit(RequestSeedTypedef *Tester){
	Tester->Security_Level=SESEEDLEVEL;
	Tester->Security_SID=SEREQUESTID;
}

void KeyandSeedCompute(Keytypedef* Key , Seedtypedef * Seed){
	Key->Key_0 = Seed->Seed_0 ^ Seed->Seed_1;
	Key->Key_1 = Seed->Seed_1 + Seed->Seed_2;
	Key->Key_2 = Seed->Seed_2 ^ Seed->Seed_3;
	Key->Key_3 = Seed->Seed_3 + Seed->Seed_0;
	Key->Key_4 = Seed->Seed_0 | Seed->Seed_1;
	Key->Key_5 = Seed->Seed_1 + Seed->Seed_2;
	Key->Key_6 = Seed->Seed_2 | Seed->Seed_3;
	Key->Key_7 = Seed->Seed_3 + Seed->Seed_0;
	Key->Key_8 = Seed->Seed_0 & Seed->Seed_1;
	Key->Key_9 = Seed->Seed_1 + Seed->Seed_2;
	Key->Key_10 = Seed->Seed_2 & Seed->Seed_3;
	Key->Key_11 = Seed->Seed_3 + Seed->Seed_0;
	Key->Key_12 = Seed->Seed_0 - Seed->Seed_1;
	Key->Key_13 = Seed->Seed_1 + Seed->Seed_2;
	Key->Key_14 = Seed->Seed_2 - Seed->Seed_3;
	Key->Key_15 = Seed->Seed_3 + Seed->Seed_0;
}
