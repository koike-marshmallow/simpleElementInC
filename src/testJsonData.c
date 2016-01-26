#include <stdio.h>
#include <string.h>
#include "jsonNode/jsonData.h"

void printJsonData(JSONDATA* data);

int main(void){
	JSONDATA* dat1;
	JSONDATA *ins1, *ins2, *ins3;
	
	dat1 = createJsonData();
	printJsonData(dat1);
	
	jdataSetInt(dat1, 4096);
	printJsonData(dat1);
	
	jdataSetFloat(dat1, 7.1823);
	printJsonData(dat1);
	
	jdataSetString(dat1, "models");
	printJsonData(dat1);
	
	jdataSetBool(dat1, TRUE);
	printJsonData(dat1);
	
	jdataSetNull(dat1);
	printJsonData(dat1);
	
	printJsonData(ins1 = JD_STRING("valvalval"));
	printJsonData(ins2 = JD_FLOAT(32.865654654651));
	printJsonData(ins3 = JD_BOOLEAN(FALSE));
	
	destroyJsonData(dat1);
	destroyJsonData(ins1);
	destroyJsonData(ins2);
	destroyJsonData(ins3);

	return 0;
}


void printJsonData(JSONDATA* data){
	int type = jdataGetType(data);
	char type_str[64];
	char value_str[128];
	
	switch( type ) {
	case JDTYPE_INTEGER:
		strcpy(type_str, "INTEGER");
		/*sprintf(value_str, "%d", jdataGetInt(data));*/
		break;
	case JDTYPE_FLOAT:
		strcpy(type_str, "FLOAT");
		/*sprintf(value_str, "%f", jdataGetFloat(data));*/
		break;
	case JDTYPE_STRING:
		strcpy(type_str, "STRING");
		/*sprintf(value_str, "\"%s\"", jdataGetString(data));*/
		break;
	case JDTYPE_BOOLEAN:
		strcpy(type_str, "BOOLEAN");
		/*if( jdataGetBool(data) ) strcpy(value_str, "<TRUE>");
		else strcpy(value_str, "<FALSE>");*/
		break;
	case JDTYPE_NULL:
		strcpy(type_str, "NULL");
		/*strcpy(value_str, "NULL");*/
		break;
	}
	
	printf("data type  : %s\n", type_str);
	jdataConvertValueString(data, value_str, 6);
	printf("data value : %s\n", value_str);
}
