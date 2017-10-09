#include <string>
#include "CETUS_Room.hpp"
#include <iostream>

#ifndef CETUS_LIST_HPP
#define CETUS_LIST_HPP

class List{
	
	private:
	
		Room* north;
		Room* south;
		Room* east;
		Room* west; 
		
	public:
	
		List();
		~List();
		void List::addAdjacent(int direction, Room* current)
		Room* List::printAdjacent(int direction);
		void List::switchAdjacent(int first, int second);
		void List::printAllAdjacent();
	
};

#endif