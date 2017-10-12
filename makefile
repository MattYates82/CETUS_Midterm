all: CETUS_Main.cpp List.o Room.o Items.o
	g++ -o demo CETUS_Main.cpp List.o Room.o Items.o

Room.o: CETUS_Room.cpp
	g++ -o Room.o CETUS_Room.cpp

Items.o: CETUS_Items.cpp
	g++ -o Items.o CETUS_Items.cpp

List.o: CETUS_List.cpp
	g++ -o List.o CETUS_List.cpp

