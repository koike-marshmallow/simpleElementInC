## sources
src_error_h = error/error.h
src_error_c = error/error.c

src_stringBuffer_h = stringBuffer/stringBuffer.h
src_stringBuffer_c = stringBuffer/stringBuffer.c

src_nodeCore_h = simpleElement/nodeCore.h
src_nodeCore_c = simpleElement/nodeCore.c
src_nodeIterator_h = simpleElement/nodeIterator.h
src_nodeIterator_c = simpleElement/nodeIterator.c
src_simpleNode_h = simpleElement/simpleNode.h
src_simpleNode_c = simpleElement/simpleNode.c
src_simpleElement_h = simpleElement/simpleElement.h
src_simpleElement_c = simpleElement/simpleElement.c
src_markupTransformer_h = simpleElement/markupTransformer.h
src_markupTransformer_c = simpleElement/markupTransformer.c

src_jsonData_h = jsonNode/jsonData.h
src_jsonData_c = jsonNode/jsonData.c
src_jsonNode_h = jsonNode/jsonNode.h
src_jsonNode_c = jsonNode/jsonNode.c
src_jsonObject_h = jsonNode/jsonObject.h
src_jsonObject_c = jsonNode/jsonObject.c
src_jsonTransformer_h = jsonNode/jsonTransformer.h
src_jsonTransformer_c = jsonNode/jsonTransformer.c

src_stringCell_h = stringCell/stringCell.h
src_stringCell_c = stringCell/stringCell.c

src_outputStream_h = stream/outputStream.h
src_outputStream_c = stream/outputStream.c


## module rules
nodeCore.o : $(src_error_h) $(src_nodeCore_h) $(src_nodeCore_c)
	cc -c $(src_nodeCore_c)
nodeIterator.o : $(src_error_h) $(src_nodeCore_h) $(src_nodeIterator_h) $(src_nodeIterator_c)
	cc -c $(src_nodeIterator_c)
simpleNode.o : $(src_error_h) $(src_nodeCore_h) $(src_nodeIterator_h) $(src_simpleNode_h) $(src_simpleNode_c)
	cc -c $(src_simpleNode_c)
simpleElement.o : $(src_nodeCore_h) $(src_simpleNode_h) $(src_simpleElement_h) $(src_simpleElement_c)
	cc -c $(src_simpleElement_c)
error.o : $(src_error_h) $(src_error_c)
	cc -c $(src_error_c)
stringBuffer.o : $(src_error_h) $(src_stringBuffer_h) 
	cc -c $(src_stringBuffer_c)
markupTransformer.o : $(src_markupTransformer_c) $(src_markupTransformer_h) $(src_nodeCore_h) $(src_simpleNode_h) $(src_simpleElement_h) $(src_stringBuffer_h) 
	cc -c $(src_markupTransformer_c)
jsonData.o : $(src_jsonData_h) $(src_jsonData_c) $(src_error_h)
	cc -c $(src_jsonData_c)
jsonNode.o : $(src_jsonNode_h) $(src_jsonNode_c) $(src_jsonData_h) $(src_error_h) $(src_nodeCore_h)
	cc -c $(src_jsonNode_c)
jsonObject.o : $(src_jsonObject_h) $(src_jsonObject_c) $(src_jsonNode_h) $(src_nodeCore_h) $(src_error_h)
	cc -c $(src_jsonObject_c)
jsonTransformer.o : $(src_jsonTransformer_h) $(src_jsonTransformer_c) $(src_nodeCore_h) $(src_outputStream_h) $(src_error_h) $(src_jsonData_h) $(src_jsonNode_h) $(src_jsonObject_h)
	cc -c $(src_jsonTransformer_c)

stringCell.o : $(src_error_h) $(src_stringCell_h) $(src_stringCell_c)
	cc -c $(src_stringCell_c)

outputStream.o : $(src_outputStream_h) $(src_outputStream_c)
	cc -c $(src_outputStream_c)


testSimpleNode.o : $(src_nodeCore_h) $(src_nodeIterator_h) $(src_simpleNode_h) testSimpleNode.c
	cc -c testSimpleNode.c
objs_testSimpleNode = testSimpleNode.o nodeCore.o nodeIterator.o simpleNode.o error.o
testSimpleNode : $(objs_testSimpleNode)
	cc -o testSimpleNode $(objs_testSimpleNode)
testSimpleElement.o : $(src_nodeCore_h) $(src_simpleNode_h) $(src_simpleElement_h) testSimpleElement.c 
	cc -c testSimpleElement.c
objs_testSimpleElement = testSimpleElement.o nodeCore.o nodeIterator.o simpleNode.o simpleElement.o error.o
testSimpleElement : $(objs_testSimpleElement)
	cc -o testSimpleElement $(objs_testSimpleElement)

testStringBuffer.o : $(src_stringBuffer_h) testStringBuffer.c
	cc -c testStringBuffer.c
objs_testStringBuffer = testStringBuffer.o stringBuffer.o error.o
testStringBuffer : $(objs_testStringBuffer)
	cc -o testStringBuffer $(objs_testStringBuffer)
testMarkupTransformer.o : $(src_stringBuffer_h) $(src_nodeCore_h) $(src_simpleElement_h) $(src_markupTransformer_h) testMarkupTransformer.c
	cc -c testMarkupTransformer.c
objs_testMarkupTransformer = testMarkupTransformer.o nodeCore.o simpleNode.o simpleElement.o error.o stringBuffer.o markupTransformer.o
testMarkupTransformer : $(objs_testMarkupTransformer)
	cc -o testMarkupTransformer $(objs_testMarkupTransformer)
	
testJsonData.o : $(src_jsonNode_h) testJsonData.c
	cc -c testJsonData.c
objs_testJsonData = error.o jsonData.o testJsonData.o
testJsonData : $(objs_testJsonData)
	cc -o testJsonData $(objs_testJsonData)
testJsonNode.o : $(src_nodeCore_h) $(src_jsonData_h) $(src_jsonNode_h) testJsonNode.c
	cc -c testJsonNode.c
objs_testJsonNode = error.o jsonData.o jsonNode.o nodeCore.o testJsonNode.o
testJsonNode : $(objs_testJsonNode)
	cc -o testJsonNode $(objs_testJsonNode)
testJsonObject.o : $(src_jsonNode_h) $(src_jsonObject_h) testJsonObject.c
	cc -c testJsonObject.c
objs_testJsonNode = error.o nodeCore.o jsonData.o jsonNode.o jsonObject.o testJsonObject.o
testJsonObject : $(objs_testJsonNode)
	cc -o testJsonObject $(objs_testJsonNode)
testJsonTransformer.o : $(src_jsonNode_h) $(src_jsonObject_h) $(src_outputStream_h) $(src_jsonTransformer_h) testJsonTransformer.c
	cc -c testJsonTransformer.c
objs_testJsonTransformer = error.o nodeCore.o jsonData.o jsonNode.o jsonObject.o jsonTransformer.o outputStream.o testJsonTransformer.o
testJsonTransformer : $(objs_testJsonTransformer)
	cc -o testJsonTransformer $(objs_testJsonTransformer)

testStringCell.o : $(src_stringCell_h) testStringCell.c
	cc -c testStringCell.c
objs_testStringCell = error.o stringCell.o testStringCell.o
testStringCell : $(objs_testStringCell)
	cc -o testStringCell $(objs_testStringCell)

testOutputStream.o : $(src_outputStream_h) testOutputStream.c
	cc -c testOutputStream.c
objs_testOutputStream = outputStream.o testOutputStream.o
testOutputStream : $(objs_testOutputStream)
	cc -o testOutputStream $(objs_testOutputStream)
