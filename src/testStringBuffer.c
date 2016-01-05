#include <stdio.h>
#include "stringBuffer/stringBuffer.h"


int main(void){
	STRBUF* buf;
	FILE* fp;

	buf = createStringBuffer(32);
	
	/*
	fp = fopen("test.txt", "r");
	sbScanFile(buf, fp);
	fclose(fp);
	*/
		
	sbCatString(buf, "SUCCESS");
	sbCatString(buf, "oasifjoaifejpawoi");
	sbCatString(buf, "foeijfoei");
	
	printStringBufferInfo(buf);
	dumpStringBuffer(stdout, buf, 0);
	
	return 0;
}
	
	
