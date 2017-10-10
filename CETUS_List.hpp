#include <string>
#include <iostream>

#ifndef CETUS_LIST_HPP
#define CETUS_LIST_HPP

using std::string;

class Room;

class List{
	
		
	public:

		Room* north;
		Room* south;
		Room* east;
		Room* west;
	
		List();
		~List();
		void addAdjacent(int direction, Room* current);
		Room* printAdjacent(int direction);
		void switchAdjacent(int first, int second);
		//void printAllAdjacent();
		
	
};

#endif