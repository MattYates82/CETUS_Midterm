
#ifndef creature_class
#define creature_class

#include <string>
#include "CETUS_Items.hpp"
using std::string;

class Creature{
    
private:
    
protected:
    
    int armor;
    int health;
    string name;
    Item* heldItem;
    
public:
    Creature(int, int, string);
    virtual ~Creature();
    virtual int attack();
    virtual void defense(int);
    virtual string getName() = 0;  //True virtual function
    virtual void getRoomDesc() = 0;
    virtual bool isDead(int);
    virtual void adjName(string);
    virtual void getDesc() = 0;
    friend bool operator==(Creature&, Creature&);
    virtual int getHP();
    virtual Item* dropItem();
    
};

#endif 
