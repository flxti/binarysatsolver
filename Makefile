CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2 -Wextra -pedantic -Wnull-dereference \
		 -Wfloat-equal -Wundef -Wcast-qual -Wcast-align -Wold-style-cast \
		 -Wmissing-include-dirs -Wswitch-enum -Wswitch-bool -Wuninitialized \
		 -Wmissing-declarations -Wdouble-promotion -Wstrict-overflow=5
 
 
main: main.o parser.o solver.o binaryexpressiontree.o
	$(CXX) $(CFLAGS) -o sat main.o parser.o solver.o binaryexpressiontree.o
 
main.o: main.cpp parser.h solver.h binaryexpressiontree.h
	$(CXX) $(CFLAGS) -c main.cpp
 
parser.o: parser.h binaryexpressiontree.h
	$(CXX) $(CFLAGS) -c parser.cpp
solver.o: solver.h binaryexpressiontree.h
	$(CXX) $(CFLAGS) -c solver.cpp
binaryexpressiontree.o: binaryexpressiontree.h

clean:
	$(RM) sat *.o
