#include <string>
#include "CETUS_Items.hpp"

using std::string;

Item::Item(string newName, string newDesc, int newPower, int newHealing, bool newWeapon){
	
	this->Name = newName;
	this->Description = newDesc;
	this->Power = newPower;
	this->Healing = newHealing;
	this->weapon = newWeapon;
	return;	
	
}