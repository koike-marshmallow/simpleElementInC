#include <stdio.h>
#include <stdlib.h>
#include "simpleElement/nodeCore.h"
#include "simpleElement/simpleElement.h"

int main(void){
	NODE *root, *test;
	char namelist[8][64];
	int i, cnt;
	
	root = createElement("root");
	test = createElement("TEST");
	addText(test, "これはテキスト１です");
	addAttribute(test, "これが属性", "アトリビュート");
	addAttribute(test, "ちがう", "属性");
	addText(test, "これはテキストです");
	appendChildNode(root, test);
	
	traceNodes(root, 0);
	deleteAttribute(test, "これが属性");
	
	cnt = getAttributeNameList(test, (char*)namelist, 8, 64);
	for( i=0; i<cnt; i++){
		printf("%d: %s\n", i, namelist[i]);
	}
	getText(test, namelist[0], 64);
	printf("gettext: %s\n", namelist[0]);
	getAttributeValue(test, "ちがう", namelist[1], 64);
	printf("getattrv: %s\n", namelist[1]);
	
	traceNodes(root, 0);
	rdestroyNode(root);
	return 0;
}
