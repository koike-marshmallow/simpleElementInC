struct s_stringBuffer {
	char* buffer;
	int buffer_len;
};
typedef struct s_stringBuffer STRBUF;

STRBUF* createStringBuffer(int length);
void initStringBuffer(STRBUF* sbuf);
void destroyStringBuffer(STRBUF* sbuf);

void sbSetString(STRBUF* sbuf, char* str);
void sbCatString(STRBUF* sbuf, char* str);

char* sbGetString(STRBUF* sbuf, char* cp, int len);

int sbStringLength(STRBUF* sbuf);
int sbLimitStringLength(STRBUF* sbuf);
int sbIsBufferFull(STRBUF* sbuf);

int sbScanFile(STRBUF* sbuf, FILE *fp);
int sbExportFile(STRBUF* sbuf, FILE *fp);

void printStringBufferInfo(STRBUF* sbuf);
void dumpStringBuffer(FILE* fp, STRBUF* sbuf, int c);
