CC=g++
EXENAME=experiment
TESTEXENAME=unittests
LIBS=-lcrypto
COPTS=-std=c++11 -I.

all: ${EXENAME} test

${EXENAME}: main.cc block.o genesisBlock.o
	${CC} ${COPTS} -o ${EXENAME} main.cc *.o ${LIBS}

test: ./tests/*.cc block.o genesisBlock.o
	${CC} ${COPTS} -o ${TESTEXENAME} ./tests/tests.cc *.o ${LIBS}

genesisBlock.o: blocks/genesisBlock.h blocks/genesisBlock.cc block.o
	${CC} ${COPTS} -c blocks/genesisBlock.cc

block.o: blocks/block.h blocks/block.cc
	${CC} ${COPTS} -c blocks/block.cc

tester.o: tests/tester.h tests/tester.cc block.o genesisBlock.o
	${CC} ${COPTS} -c tests/tester.cc
  

clean:
	rm -f *.o ${EXENAME} ${TESTEXENAME}
