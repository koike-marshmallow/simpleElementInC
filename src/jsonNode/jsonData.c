#include <stdlib.h>
#include <string.h>
#include "../error/error.h"
#include "jsonData.h"

#define NULL_CHECK(p, fnc) ifassert((p == NULL), fnc, "jsondata is null")
#define DATA_MALLOC_ASSERT(p, fnc) ifassert((p == NULL), fnc, "cannot create data space")
#define VALUE_NULL_CHECK(p, fnc) ifassert((p == NULL), fnc, "jsondata value is null")

JSONDATA* createJsonData(void){
	JSONDATA* new_data;
	
	new_data = malloc(sizeof(JSONDATA));
	ifassert((new_data == NULL), "createJsonData", "JSONDATA cannot create!");
	
	new_data->dtype = JDTYPE_NULL;
	new_data->value = NULL;
	
	return new_data;
}


void destroyJsonData(JSONDATA* data){
	NULL_CHECK(data, "destroyJsonData");

	clearJsonData(data);
	free(data);
}


void clearJsonData(JSONDATA* data){
	NULL_CHECK(data, "destroyJsonData");
	
	switch( data->dtype ){
	case JDTYPE_NULL:
		break;
	case JDTYPE_INTEGER:
		*(JD_TYPE_INT*)data->value = 0;
		free(data->value);
		break;
	case JDTYPE_FLOAT:
		*(JD_TYPE_FLOAT*)data->value = 0;
		free(data->value);
		break;
	case JDTYPE_BOOLEAN:
		*(JD_TYPE_BOOL*)data->value = 0;
		free(data->value);
		break;
	case JDTYPE_STRING:
		memset(data->value, 0, strlen(data->value));
		free(data->value);
		break;
	default:
		fnerror("clearJsonData", "illigal data type code");
		break;
	}
	
	data->dtype = JDTYPE_NULL;
	data->value = NULL;
}


JSONDATA* jdataSetNull(JSONDATA* data){
	NULL_CHECK(data, "jdataSetNull");
	clearJsonData(data);
	
	return data;
}


JSONDATA* jdataSetInt(JSONDATA* data, JD_TYPE_INT val){
	NULL_CHECK(data, "jdataSetInt");
	clearJsonData(data);

	data->value = malloc(sizeof(JD_TYPE_INT));
	DATA_MALLOC_ASSERT(data->value, "jdataSetInt");

	data->dtype =JDTYPE_INTEGER;
	*(JD_TYPE_INT*)data->value = val;
	
	return data;
}


JSONDATA* jdataSetFloat(JSONDATA* data, JD_TYPE_FLOAT val){
	NULL_CHECK(data, "jdataSetFloat");
	clearJsonData(data);
	
	data->value = malloc(sizeof(JD_TYPE_FLOAT));
	DATA_MALLOC_ASSERT(data->value, "jdataSetFloat");
	
	data->dtype = JDTYPE_FLOAT;
	*(JD_TYPE_FLOAT*)data->value = val;
	
	return data;
}


JSONDATA* jdataSetString(JSONDATA* data, char* str){
	NULL_CHECK(data, "jdataSetString");
	clearJsonData(data);
	
	data->value = malloc(sizeof(char) * (strlen(str) + 1));
	DATA_MALLOC_ASSERT(data->value, "jdataSetString");

	data->dtype = JDTYPE_STRING;	
	strcpy(data->value, str);
	
	return data;
}


JSONDATA* jdataSetBool(JSONDATA* data, JD_TYPE_BOOL val){
	NULL_CHECK(data, "jdataSetBool");
	clearJsonData(data);
	
	data->value = malloc(sizeof(JD_TYPE_BOOL));
	DATA_MALLOC_ASSERT(data->value, "jdataSetBool");
	
	data->dtype = JDTYPE_BOOLEAN;
	*(JD_TYPE_BOOL*)data->value = val;
	
	return data;
}


int jdataGetType(JSONDATA* data){
	NULL_CHECK(data, "jdataGetType");
	
	return data->dtype;
}


JD_TYPE_INT jdataGetInt(JSONDATA* data){
	NULL_CHECK(data, "jdataGetInt");
	ifassert((data->dtype != JDTYPE_INTEGER), 
		"jdataGetInt", "this jsondata is not integer");
	
	return *(JD_TYPE_INT*)data->value;
}


JD_TYPE_FLOAT jdataGetFloat(JSONDATA* data){
	NULL_CHECK(data, "jdataGetFloat");
	ifassert((data->dtype != JDTYPE_FLOAT),
		"jdataGetFloat", "this jsondata is not float");
	
	return *(JD_TYPE_FLOAT*)data->value;
}


char* jdataGetString(JSONDATA* data){
	NULL_CHECK(data, "jdataGetString");
	ifassert((data->dtype != JDTYPE_STRING),
		"jdataGetString", "this jsondata is not string");
	
	return (char*)data->value;
}


JD_TYPE_BOOL jdataGetBool(JSONDATA* data){
	NULL_CHECK(data, "jdataGetBool");
	ifassert((data->dtype != JDTYPE_BOOLEAN),
		"jdataGetBool", "this jsondata is not boolean");
	
	return ((*(JD_TYPE_BOOL*)data->value) != 0);
}


void* jdataGetValuePointer(JSONDATA* data){
	NULL_CHECK(data, "jdataGetValuePointer");
	
	return data->value;
}


int isJsonDataNull(JSONDATA* data){
	NULL_CHECK(data, "isJsonDataNull");
	
	return data->dtype == JDTYPE_NULL;
}


int checkJsonDataType(JSONDATA* data, int type){
	NULL_CHECK(data, "checkJsonDataType");
	
	return data->dtype == type;
}
