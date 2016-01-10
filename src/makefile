## sources
src_error_h = error/error.h
src_error_c = error/error.c

src_nodeCore_h = simpleElement/nodeCore.h
src_nodeCore_c = simpleElement/nodeCore.c
src_nodeIterator_h = simpleElement/nodeIterator.h
src_nodeIterator_c = simpleElement/nodeIterator.c
src_simpleNode_h = simpleElement/simpleNode.h
src_simpleNode_c = simpleElement/simpleNode.c



## module rules
nodeCore.o : $(src_error_h) $(src_nodeCore_h) $(src_nodeCore_c)
	cc -c $(src_nodeCore_c)
nodeIterator.o : $(src_error_h) $(src_nodeCore_h) $(src_nodeIterator_h) $(src_nodeIterator_c)
	cc -c $(src_nodeIterator_c)
simpleNode.o : $(src_error_h) $(src_nodeCore_h) $(src_nodeIterator_h) $(src_simpleNode_h) $(src_simpleNode_c)
	cc -c $(src_simpleNode_c)
simpleElement.o : simpleElement/nodeCore.h simpleElement/simpleElement.h simpleElement/simpleElement.c
	cc -c simpleElement/simpleElement.c
error.o : error/error.h error/error.c
	cc -c error/error.c
stringBuffer.o : error/error.h stringBuffer/stringBuffer.h stringBuffer/stringBuffer.c
	cc -c stringBuffer/stringBuffer.c


testSimpleNode.o : $(src_nodeCore_h) $(src_nodeIterator_h) $(src_simpleNode_h) testSimpleNode.c
	cc -c testSimpleNode.c
objs_testSimpleNode = testSimpleNode.o nodeCore.o nodeIterator.o simpleNode.o error.o
testSimpleNode : $(objs_testSimpleNode)
	cc -o testSimpleNode $(objs_testSimpleNode)

testStringBuffer.o : stringBuffer/stringBuffer.h testStringBuffer.c
	cc -c testStringBuffer.c
testStringBuffer : testStringBuffer.o stringBuffer.o error.o
	cc -o testStringBuffer testStringBuffer.o stringBuffer.o error.o
