#include <stdio.h>
#include "stringBuffer/stringBuffer.h"


int main(void){
	STRBUF* buf;
	
	buf = createStringBuffer(32);
	
	sbSetString(buf, "SUCCESS");
	sbCatString(buf, "oasifjoaifejpawoi");
	sbCatString(buf, "foeijfoei");
	
	printStringBufferInfo(buf);
	dumpStringBuffer(stdout, buf, 0);
	
	return 0;
}
	
	
