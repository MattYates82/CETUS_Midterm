all: main.cpp Data.o List.o Items.o Player.o Room.o World.o Parser.o battle.o
	
	g++ -std=c++11 -o cetus main.cpp CETUS_World.o CETUS_data.o CETUS_List.o CETUS_Items.o CETUS_Player.o CETUS_Room.o CETUS_Parser.o battle.o  

battle.o: battle.cpp
	g++ -c battle.cpp -std=c++11

World.o: CETUS_World.cpp
	g++ -c CETUS_World.cpp -std=c++11
	
Data.o: CETUS_data.cpp
	g++ -c CETUS_data.cpp -std=c++11

Items.o: CETUS_Items.cpp
	g++ -c CETUS_Items.cpp -std=c++11

List.o: CETUS_List.cpp
	g++ -c CETUS_List.cpp -std=c++11

Player.o: CETUS_Player.cpp
	g++ -c CETUS_Player.cpp -std=c++11

Room.o: CETUS_Room.cpp
	g++ -c CETUS_Room.cpp -std=c++11

Parser.o: CETUS_Parser.cpp
	g++ -c CETUS_Parser.cpp -std=c++11

clean:
	$(RM) *.o
