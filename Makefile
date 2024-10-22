
# Clean the default value of CC.
CC=

ifndef CC
    CC=g++
endif

ifndef CFLAGS
	CFLAGS=-Wall -Wextra -g 
endif  # CFLAGS


test.out: Node.o test_node.cpp 
	$(CC) $(CFLAGS) test_node.cpp Node.o  -o test.out

Node.o: Node.h Node.cpp Container.h
	$(CC) $(CFLAGS) -c  Node.h Node.cpp  Container.h

Channel.o: Channel.h Channel.cpp
	$(CC) $(CFLAGS) -c Channel.h Channel.cpp

AlgorithmBase.o: AlgorithmBase.h AlgorithmBase.cpp
	$(CC) $(CFLAGS) -c AlgorithmBase.h AlgorithmBase.cpp

clean:
	-rm *.out
	-rm *.o
	-rm *.gch