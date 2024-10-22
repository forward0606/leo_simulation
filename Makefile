
# Clean the default value of CC.
CC=

ifndef CC
    CC=g++
endif

ifndef CFLAGS
	CFLAGS=-Wall -Wextra -g 
endif  # CFLAGS


dependency= Node.o Channel.o AlgorithmBase.o AlgoLP.o

a.out: main.cpp $(dependency)
	$(CC) $(CFLAGS) main.cpp $(dependency)

test.out: Node.o test_node.cpp 
	$(CC) $(CFLAGS) test_node.cpp Node.o  -o test.out

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $<

clean:
	-rm *.out
	-rm *.o
	-rm *.gch