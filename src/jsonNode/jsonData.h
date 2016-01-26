#ifndef JSONDATA_H
#define JSONDATA_H

struct s_jsondata {
	int dtype;
	void* value;
};

#define JDTYPE_NULL 0
#define JDTYPE_INTEGER 1
#define JDTYPE_FLOAT 2
#define JDTYPE_STRING 3
#define JDTYPE_BOOLEAN 4

#ifndef TRUE
#	define TRUE 1
#endif
#ifndef FALSE
#	define FALSE 0
#endif

typedef struct s_jsondata JSONDATA;

typedef int JD_TYPE_INT;
typedef double JD_TYPE_FLOAT;
typedef int JD_TYPE_BOOL;


JSONDATA* createJsonData(void);
void destroyJsonData(JSONDATA* data);

void clearJsonData(JSONDATA* data);

JSONDATA* jdataSetNull(JSONDATA* data);
JSONDATA* jdataSetInt(JSONDATA* data, JD_TYPE_INT val);
JSONDATA* jdataSetFloat(JSONDATA* data, JD_TYPE_FLOAT val);
JSONDATA* jdataSetString(JSONDATA* data, char* str);
JSONDATA* jdataSetBool(JSONDATA* data, JD_TYPE_BOOL val);

int jdataGetType(JSONDATA* data);
JD_TYPE_INT jdataGetInt(JSONDATA* data);
JD_TYPE_FLOAT jdataGetFloat(JSONDATA* data);
char* jdataGetString(JSONDATA* data);
JD_TYPE_BOOL jdataGetBool(JSONDATA* data);
void* jdataGetValuePointer(JSONDATA* data);

char* jdataConvertValueString(JSONDATA* data, char* dest, int str_len);

int isJsonDataNull(JSONDATA* data);
int checkJsonDataType(JSONDATA* data, int type);

#define JD_INTEGER(val) jdataSetInt(createJsonData(), val)
#define JD_FLOAT(val) jdataSetFloat(createJsonData(), val)
#define JD_STRING(str) jdataSetString(createJsonData(), str)
#define JD_BOOLEAN(val) jdataSetBool(createJsonData(), val)

#endif
