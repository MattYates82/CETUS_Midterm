#include <string>

#define numItems 10

#ifndef CETUS_PLAYER_HPP
#define CETUS_PLAYER_HPP



class Item;
class Room;

class Player{
	
	private:
	
		int	health;
		int movesCompleted;
		Room* currentRoom;
		std::vector<Item*> inventory;
	
	public:
	
		Player::Player();
		int Player::addItem(Item* current);
		int Player::incrementMoves();
		int Player::decrementMoves();
		int Player::resurrectPlayer(Room* current);
		int Player::damagePlayer(int damage);
		int Player::healPlayer(int health);
	
};

#endif