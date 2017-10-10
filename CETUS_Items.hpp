#include <string>

#ifndef CETUS_ITEMS_HPP
#define CETUS_ITEMS_HPP

using std::string;

class Item {
	
	private:
	
		string	Name;
		string	Description;
		int		Power;
		int		Healing;
		bool	weapon;
		
	public:
	
		Item(string Name, string Description, int Power, int Healing, bool weapon);
		//~Item();
		//int damageItem(int damage);
	
	
};
#endif