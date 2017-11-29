CC=g++
EXENAME=ledger
TESTEXENAME=unittests
LIBS=-lcrypto
COPTS=-std=c++11

all: ${EXENAME} test

${EXENAME}: main.cc block.o genesisBlock.o
	${CC} ${COPTS} -o ${EXENAME} main.cc *.o ${LIBS}

test: ./tests/*.cc block.o genesisBlock.o
	${CC} ${COPTS} -o ${TESTEXENAME} ./tests/tests.cc *.o ${LIBS}

genesisBlock.o: genesisBlock.h genesisBlock.cc block.o
	${CC} ${COPTS} -c genesisBlock.cc

block.o: block.h block.cc
	${CC} ${COPTS} -c block.cc

tester.o: tests/tester.h tests/tester.cc block.o genesisBlock.o
	${CC} ${COPTS} -c tests/tester.cc
  

clean:
	rm -f *.o ${EXENAME} ${TESTEXENAME}
