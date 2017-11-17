#include "battle.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void battle(Player *p1, Creature* c2, int modifier){
    int atkValue;
    int ignore = 0;
    
    while (ignore < 1){
        cout << "You attack!" << endl;
        atkValue = rand()%20+1+modifier;
        c2->defense(atkValue);
        
        if(c2->isDead(1)){
            cout << endl << "The " << c2->getName() << " has died!" << endl;
            return;
        }
        
        cout << endl << "The " << c2->getName() << " attacks!" << endl;
        atkValue = c2->attack();
        if(atkValue > 12){
        	p1->damagePlayer(10);
        }
        
        if(p1->getHealth() <= 0){
            cout << "You died!" << endl;
            return;
        }
    }
}


void randomEnemyGenerator(Room* room){
    srand(time(0));
    if(room->hasEnemy()==0){
        Creature* newCreat = NULL;
        int choice = rand()%10 + 1;
        if(choice < 6){
            room->setEnemy(NULL);
        } else if(choice == 6){
            newCreat= new Ghost();
        } else if(choice == 7){
            newCreat = new Cultist();
        } else if(choice == 8){
            newCreat = new Merman();
        } else {
            return;
        }
        room->setEnemy(newCreat);
    }
    return;
}
