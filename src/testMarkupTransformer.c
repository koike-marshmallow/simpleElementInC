#include <stdio.h>
#include <stdlib.h>
#include "stringBuffer/stringBuffer.h"
#include "simpleElement/nodeCore.h"
#include "simpleElement/simpleElement.h"
#include "simpleElement/markupTransformer.h"

#define ADD_BRAKE_TAG(e) appendChildElement(e, createElement("br"));
#define ADD_TEXT_ELEMENT(e, name, text) dtmp=createElement(name); addText(dtmp, text); appendChildElement(e, dtmp);

int main(void){
	NODE *e_html, *e_head, *e_body;
	NODE *e_title, *e_meta;
	NODE *e_h1, *e_p1, *e_p2;
	NODE *dtmp;
	STRBUF* st;
	FILE* out;
	
	e_html = createElement("html");
	e_head = createElement("head");
	e_body = createElement("body");
	
	e_title = createElement("title");
	addText(e_title, "テスト");
	e_meta = createElement("meta");
	addAttribute(e_meta, "charset", "UTF-8");
	
	e_h1 = createElement("h1");
	addText(e_h1, "マークアップトランスフォーマーのテスト");
	e_p1 = createElement("p1");
	addText(e_p1, "このページはマークアップトランスフォーマーのテストです");
	ADD_BRAKE_TAG(e_p1);
	addText(e_p1, "これは段落１です");
	e_p2 = createElement("p2");
	addText(e_p2, "これは段落２です");
	ADD_BRAKE_TAG(e_p2);
	addText(e_p2, "brは");
	ADD_TEXT_ELEMENT(e_p2, "b", "BR");
	addText(e_p2, "eak(");
	ADD_TEXT_ELEMENT(e_p2, "i", "改行");
	addText(e_p2, ")の略称です。テキストをこの位置で改行します");
	
	
	appendChildElement(e_html, e_head);
	appendChildElement(e_html, e_body);
	appendChildElement(e_head, e_title);
	appendChildElement(e_head, e_meta);
	appendChildElement(e_body, e_h1);
	appendChildElement(e_body, e_p1);
	appendChildElement(e_body, e_p2);

	
	TRANSFORM_INDENT = 4;
	TRANSFORM_LINEFEED = 1;
	st = createStringBuffer(1024);
	transform(st, e_html);
	
	if( (out = fopen("output.html", "w")) == NULL ){
		fprintf(stderr, "ファイルオープンに失敗しました");
	}
	fprintf(out, "<!DOCTYPE html>\n");
	sbExportFile(st, out);
	printf("output.htmlに出力しました\n");
	fclose(out);
	
	
	return 0;
}
