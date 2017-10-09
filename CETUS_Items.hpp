#include <string>
#include "CETUS_Room.hpp"
#include "CETUS_World.hpp"

#ifndef CETUS_ITEM_HPP
#define CETUS_ITEM_HPP

class Item {
	
	private:
	
		string	Name;
		string	Description;
		int		Power;
		int		Healing;
		bool	weapon;
		
	public:
	
		Item::Item(string Name, string Description, int Power, int Healing, bool weapon);
		Item::~Item();
		int Item::damageItem(int damage);
	
	
};
#endif