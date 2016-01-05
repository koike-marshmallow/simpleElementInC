nodeCore.o : error/error.h simpleElement/nodeCore.h simpleElement/nodeCore.c
	cc -c simpleElement/nodeCore.c
simpleElement.o : simpleElement/nodeCore.h simpleElement/simpleElement.h simpleElement/simpleElement.c
	cc -c simpleElement/simpleElement.c
error.o : error/error.h error/error.c
	cc -c error/error.c
stringBuffer.o : error/error.h stringBuffer/stringBuffer.h stringBuffer/stringBuffer.c
	cc -c stringBuffer/stringBuffer.c
markupTransformer.o : simpleElement/markupTransformer.c simpleElement/markupTransformer.h simpleElement/nodeCore.h simpleElement/simpleElement.h stringBuffer/stringBuffer.h
	cc -c simpleElement/markupTransformer.c

testStringBuffer.o : stringBuffer/stringBuffer.h testStringBuffer.c
	cc -c testStringBuffer.c
testStringBuffer : testStringBuffer.o stringBuffer.o error.o
	cc -o testStringBuffer testStringBuffer.o stringBuffer.o error.o
testMarkupTransformer.o : testMarkupTransformer.c stringBuffer/stringBuffer.h simpleElement/nodeCore.h simpleElement/simpleElement.h simpleElement/markupTransformer.h
	cc -c testMarkupTransformer.c
testMarkupTransformer : testMarkupTransformer.o nodeCore.o simpleElement.o error.o stringBuffer.o markupTransformer.o
	cc -o testMarkupTransformer testMarkupTransformer.o nodeCore.o simpleElement.o error.o stringBuffer.o markupTransformer.o
