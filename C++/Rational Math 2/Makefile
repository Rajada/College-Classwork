rmain: RationalMain.o Rational.o
	g++ -pedantic RationalMain.o Rational.o -o rmain
RationalMain.o: RationalMain.cpp Rational.o
	g++ -Wall -pedantic  RationalMain.cpp -c
Rational.o: Rational.cpp Rational.h
	g++ -Wall -pedantic Rational.cpp -c