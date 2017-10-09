#include "CETUS_Room.hpp"
#include <iostream>

using std::endl;
using std::cout;

void Room::Room(){
	
	visited = false;
	return;
	
}


void Room::addDescriptions(string longDesc, string shortDesc){
	
	this->longDesc = longDesc;
	this->shortDesc = shortDesc;
	return;	
	
}

void Room::addItem(Item* current){
	
	this->roomItems.push_back(current);
	
	return;
	
}

void Room::removeItem(Item* current){
	
	return;
	
}

void Room::addNeighbor(int direction, Room* neigbor){
	
	this->neighbors.addAdjacent(direction, neighbor);
	return;
	
}

void Room::printLong(){

		cout<<this->longDesc;
		return;
	
}

void Room::printShort(){

	cout<<this->shortDesc;
	return;
	
}

void Room::getNeighbors(){
	
	this->neighbors.printAllAdjacent();
	return;
	
}