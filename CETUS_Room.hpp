#include <string>
#include <algorithm>
#include <vector>
#include "CETUS_List.hpp"
#include "CETUS_Items.hpp"


#ifndef CETUS_ROOM_HPP
#define CETUS_ROOM_HPP

using std::string;

class List;

class Room {
	
	private:
	
		string	longDesc;
		string	shortDesc;
		bool	visited;
		std::vector<Item*> roomItems;
					
	public:
	
		List* 	neighbors;
		Room();
		~Room();
		void addDescriptions(string longDesc, string shortDesc);
		void createNeighbors(List* neighborList);
		void addItem(Item* current);
		void removeItem(Item* current);
		void addNeighbor(int direction, Room* neigbor);
		void printLong();
		void printShort();
		//void getNeighbors();
};
#endif