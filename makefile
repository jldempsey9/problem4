p4: p4.o
	g++ p4.o -o p4
p4.o: p4.cpp
	g++ -c p4.cpp
