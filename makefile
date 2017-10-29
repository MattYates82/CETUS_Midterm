all: main.cpp CETUS_Room.o CETUS_List.o CETUS_Items.o CETUS_Player.o CETUS_data.o

	g++ -std=c++11 -o CETUS.o main.cpp CETUS_Room.o CETUS_List.o CETUS_Items.o CETUS_Player.o CETUS_data.o 

Room.o: CETUS_Room.cpp
	g++ -c CETUS_Room.cpp -std=c++11

Items.o: CETUS_Items.cpp
	g++ -c CETUS_Items.cpp -std=c++11

List.o: CETUS_List.cpp
	g++ -c CETUS_List.cpp -std=c++11

Player.o: CETUS_Player.cpp
	g++ -c CETUS_Player.cpp -std=c++11

Data.o: CETUS_data.cpp
	g++ -c CETUS_data.cpp -std=c++11

