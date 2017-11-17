
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include "creature.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

/*********************************************************************
 ** Function: Creature()
 ** Description: constructor for base and all subclasses
 ** Parameters: ints for all values and a string for the name
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: subclass member variables set
 *********************************************************************/

Creature::Creature(int arm, int str, string newName){
    
    this->armor = arm;
    this->health = str;
    this->name = newName;
    this->heldItem = NULL;
}

/*********************************************************************
 ** Function: ~Creature
 ** Description: virtual Destructor
 ** Parameters: N/A
 ** Pre-Conditions: None
 ** Post-Conditions: Object destroyed
 *********************************************************************/
Creature::~Creature(){
    
}


/*********************************************************************
 ** Function: attack
 ** Description: Virtual function, generates random attack value.  
 **              
 ** Parameters: None
 ** Pre-Conditions: subclass object created
 ** Post-Conditions: returns int value
 *********************************************************************/
int Creature::attack(){
    
    return rand()%20+1;
    
}

/*********************************************************************
 ** Function: defense
 ** Description: Virtual function, if attack higher than armor, loses 1 HP
 ** Parameters: int value (opposing creatures attack roll)
 ** Pre-Conditions: opponent made attack
 ** Post-Conditions: creature obtains damage or dodges
 *********************************************************************/
void Creature::defense(int incoming){
        
    
    //If damage is 0 or less, creature "dodged"
    if(incoming < armor){
        cout << "The " << this->name << " dodged the attack!"<< endl;
        return;
    }
    
    //If not dodged, apply damage to creature
    cout << "The " << this->name << " was hit!" << endl;
    this->health -= 1;
    return;
    
}

/*********************************************************************
 ** Function: isDead()
 ** Description: Virtual function, determines if creatures has 0 or less str
 ** Parameters: none
 ** Pre-Conditions: None
 ** Post-Conditions: returns bool value of true if dead
 *********************************************************************/
bool Creature::isDead(int check = 1){
    
    //Checks if creature is dead.  Shows total health left
    if(this->health <= 0){
        return true;
    } else{
        return false;
    }
}

/*********************************************************************
 ** Function: adjName
 ** Description: Virtual function, adds to name, used when two same creatures
 **              fight
 ** Parameters: string value to add to name
 ** Pre-Conditions: None
 ** Post-Conditions: creature name altered
 *********************************************************************/
void Creature::adjName(string add){
    this->name = add;
}

/*********************************************************************
 ** Function: Overloaded == function
 ** Description: compares two creature types
 ** Parameters: two creature addresses
 ** Pre-Conditions: two creature objects created
 ** Post-Conditions: returns true or false
 *********************************************************************/
bool operator==(Creature& left, Creature& right){
    
    return (left.name == right.name);
}

/*********************************************************************
 ** Function: getHP
 ** Description: returns value of health
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int Creature::getHP(){
    return health;
}

/*********************************************************************
 ** Function: dropItem
 ** Description: returns heldItem and removes from enemy
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
Item* Creature::dropItem(){
    if(heldItem != NULL){
        Item* tempItem = this->heldItem;
        this->heldItem = NULL;
        return tempItem;
    } else {
        return NULL;
    }
}

