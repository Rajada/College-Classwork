main: Inventory.o Store.o Pipe.o Plastic.o Hardware.o Fastener.o Hinge.o Lumber.o Hardwood.o Date.o main.o
	g++ Date.o Inventory.o Store.o Pipe.o Plastic.o Hardware.o Fastener.o Hinge.o Lumber.o Hardwood.o Softwood.o main.o -o main
main.o: main.cpp Pipe.o Plastic.o Hardware.o Fastener.o Hinge.o Lumber.o Hardwood.o Softwood.o Store.o
	g++ -Wall main.cpp -c
Store.o: Store.cpp Store.h Pipe.o Plastic.o Hardware.o Fastener.o Hinge.o Lumber.o Hardwood.o Softwood.o
	g++ -Wall Store.cpp -c
Plastic.o: Pipe.o Plastic.h Plastic.cpp
	g++ -Wall Plastic.cpp -c
Pipe.o: Inventory.o Pipe.h Pipe.cpp
	g++ -Wall Pipe.cpp -c
Hinge.o: Hardware.o Hinge.h Hinge.cpp
	g++ -Wall Hinge.cpp -c
Fastener.o: Hardware.o Fastener.h Fastener.cpp
	g++ -Wall Fastener.cpp -c
Hardware.o: Inventory.o Hardware.h Hardware.cpp
	g++ -Wall Hardware.cpp -c
Hardwood.o: Lumber.o Hardwood.h Hardwood.cpp
	g++ -Wall Hardwood.cpp -c
Softwood.o: Lumber.o Softwood.h Softwood.cpp
	g++ -Wall Softwood.cpp -c
Lumber.o: Inventory.o Lumber.h Lumber.cpp
	g++ -Wall Lumber.cpp -c