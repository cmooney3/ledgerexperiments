CC=g++
EXENAME=ledgertest
LIBS=-lcrypto

all: main.cc block.o genesisBlock.o
	${CC} -o ${EXENAME} main.cc *.o ${LIBS}

genesisBlock.o: genesisBlock.h genesisBlock.cc block.o
	${CC} -c genesisBlock.cc

block.o: block.h block.cc
	${CC} -c block.cc

clean:
	rm -f *.o ${EXENAME}
