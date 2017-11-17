/****************************************************************************
 **Program Filename:  CETUS_Parser.cpp
 **Author:  Josh Sears
 **Date:  11/12/17
 **Description:  Parses user commands into game actions and items
 ****************************************************************************/

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <string.h>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>

#include "CETUS_World.hpp"
#include "CETUS_data.hpp"
#include "CETUS_Items.hpp"
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"
#include "creature.hpp"
#include "ghost.hpp"
#include "battle.hpp"
#include "CETUS_Print.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;

/*
 Required verbs:
 look - repeats the long form explanation of the room
 look at <feature/object> - gives a fictionally interesting explanation of the specified feature/object. Player should be able to “look at” items in inventory
 Directional verbs - player should be able to specify “go north” or “north” to be able to move north. Other room travel verbs should be considered, such as “jump north”
 take - acquire an object and place it in player’s inventory
 help - list a set of verbs the game understands. Not all verbs must be disclosed within this action in case some actions should remain fictionally hidden.
 inventory - list contents of inventory
 savegame - saves the state of the current game to a file
 Loadgame - confirms with the user that this really is desired, then loads the game state from the file
 */

//functions to create verb and noun lists for searching
World* loadhelper(World* current){
    int choice;
    while(1){
        cout << "\nPlease pick a number:\n1. Load from Save.\n2. Load New Game.\nAny other number to cancel load.\nEnter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                return loadWorld("save");
                break;
            case 2:
                return loadWorld("source");
                break;
            default:
                return current;
                break;
        }
        std::cin.seekg(0,std::ios::end);
        std::cin.clear();
    }
}
void helper(){
    
    //cout << yellow;
    string spacer = "\t\t\t\t\t\t\t[";
    cout << "\nCommand Help List\n----------------------------------------------------------------------------------\n";
    cout << "Quit" << spacer << "Exits the game.]\n";
    cout << "Look" << spacer << "View the room and objects in the current area.]\n";
    cout << "Look At <object>" << "\t\t\t\t["  << "Inspect the <object>.]\n";
    cout << "Attack <target>" << "\t\t\t\t\t[" << "Tries to punch <target> with fists.]\n";
    cout << "Attack <target> with <object>\t[" << "Hit <target> with <object>.]\n";
    cout << "North/South/East/West/Up/Down\t[" << "Move in that direction.]\n";
    cout << "Take <object>" << "\t\t\t\t\t[" << "Try to pick up <object>.]\n";
    cout << "Drop <object>" << "\t\t\t\t\t[" << "Drop <object> from inventory.]\n";
    cout << "Inventory" << "\t\t\t\t\t\t[" << "Browse contents of inventory.]\n";
    cout << "Savegame" << "\t\t\t\t\t\t[" << "Saves current game progress.]\n";
    cout << "Loadgame" << "\t\t\t\t\t\t[" << "Loads last saved state.]\n";
    cout << "----------------------------------------------------------------------------------\n";
    //cout << reset;
    
}

void mapMaker(std::map<std::string, int> *map){
    map->insert (std::pair<std::string, int>("quit", 0));
    map->insert (std::pair<std::string, int>("attack", 1));
    map->insert (std::pair<std::string, int>("hit", 1));
    map->insert (std::pair<std::string, int>("north", 2));
    map->insert (std::pair<std::string, int>("n", 2));
    map->insert (std::pair<std::string, int>("south", 3));
    map->insert (std::pair<std::string, int>("s", 3));
    map->insert (std::pair<std::string, int>("east", 4));
    map->insert (std::pair<std::string, int>("e", 4));
    map->insert (std::pair<std::string, int>("west", 5));
    map->insert (std::pair<std::string, int>("w", 5));
    map->insert (std::pair<std::string, int>("up", 6));
    map->insert (std::pair<std::string, int>("u", 6));
    map->insert (std::pair<std::string, int>("down", 7));
    map->insert (std::pair<std::string, int>("d", 7));
    map->insert (std::pair<std::string, int>("take", 8));
    map->insert (std::pair<std::string, int>("grab", 8));
    map->insert (std::pair<std::string, int>("pick up", 8));
    map->insert (std::pair<std::string, int>("inv", 9));
    map->insert (std::pair<std::string, int>("inventory", 9));
    map->insert (std::pair<std::string, int>("help", 10));
    map->insert (std::pair<std::string, int>("savegame", 11));
    map->insert (std::pair<std::string, int>("loadgame", 12));
    map->insert (std::pair<std::string, int>("l", 13));
    map->insert (std::pair<std::string, int>("look", 13));
    map->insert (std::pair<std::string, int>("look_at", 14));
    map->insert (std::pair<std::string, int>("inspect", 14));
    map->insert (std::pair<std::string, int>("drop", 15));
    return;
}

void displayRoom(World* world, int look){
    Player* player = world->getPlayer();
    string temp;
    
    cout << "\n" << player->getCurrentRoom()->getName() << std::endl << std::endl;
    if((player->getCurrentRoom()->getVisited()==true) && (look==0)){
        player->getCurrentRoom()->getShort();
    }else {
        player->getCurrentRoom()->getLong();
        player->getCurrentRoom()->setVisited(true);
    }
    
    
    world->printRoomInventory();//Prints room description of items under room appearance paragraph
    
    
    if(player->getCurrentRoom()->hasEnemy()){
        std::cout <<"\n\n";
        player->getCurrentRoom()->getEnemy()->getRoomDesc();
    } else {
        cout << "\n";
    }
    
    std::cout << "\nExits:\n";
    world->printAllAdjacent();
    
    
    std::cout << "\n";
}


void verbFinder(std::map<std::string, int> mymap, string* verb, bool*foundVerb, bool* found, const string first){
    if(mymap.count(first)>0){
        *foundVerb = true;
        *verb = first;
        *found = true;
    }
    
    return;
}

Creature* enemySearch(Player* player, bool* found, bool* foundEnemy, const string first){
    std::string enemyName = player->getCurrentRoom()->getEnemy()->getName();
    std::transform(enemyName.begin(), enemyName.end(), enemyName.begin(), ::tolower);
    if(enemyName == first){
        *found = true;
        *foundEnemy=true;
        return player->getCurrentRoom()->getEnemy();
    }
    return NULL;
}

void checkPlayerInv(World* world, bool *foundNoun1, bool* foundNoun2, bool* found, bool* foundInv, Item* noun1, Item* noun2, const string first){
    Item* temp = NULL;
    if(world->findItem(first,0) != NULL)
        temp = world->findItem(first,0);
    if(temp != NULL){
        if(!(*foundNoun1)){
            //printf("Found a noun match!\n");
            *foundNoun1=true;
            *noun1 = *temp;
            *foundInv = true;
            *found=true;
        } else {
            //printf("Found a second noun match!\n");
            *foundNoun2=true;
            *noun2 = *temp;
            *foundInv = true;
            *found = true;
        }
    }
    temp = NULL;
}

void checkRoomInv(World* world, bool *foundNoun1, bool* foundNoun2, bool* found, bool* foundRoom, Item* noun1, Item* noun2, const string first){
    Player* player=world->getPlayer();
    Item* temp = player->getCurrentRoom()->findItem(first, 0);
    if(temp != NULL){
        if(!(*foundNoun1)){
            //printf("Found a noun match!\n");
            *foundNoun1=true;
            *noun1 = *temp;
            *foundRoom = true;
            *found = true;
        } else {
            //printf("Found a second noun match!\n");
            *foundNoun2=true;
            *noun2 = *temp;
            *foundRoom = true;
            *found = true;
        }
    }
    temp = NULL;
}


int parser(World* world){
    
    
    //create variables to simulate a room, actions, items, etc
    std::string input, first, verb, prev, combo;
    Item* noun1 = new Item;
    Item* noun2 = new Item;
    Creature* baddie = NULL;
    int choice;
    Player* player = world->getPlayer();
    std::map<std::string, int> mymap;
    mapMaker(&mymap);
    
    std::stringstream sstream;
    displayRoom(world, 0);
    
    while(1){
        
        sstream.str("");
        sstream.clear();
        first.clear();
        verb.clear();
        combo.clear();
        
        choice = -1;
        bool foundVerb = false;
        bool foundEnemy = false;
        bool foundNoun1 = false;
        bool foundNoun2 = false;
        bool withFlag = false;
        bool foundInv = false;
        bool foundRoom = false;
        bool found=false;
        
        printf("\nWhat are you going to do?\n");
        
        //Parse the input
        
        input.clear();
        std::cin.seekg(0,std::ios::end);
        std::cin.clear();
        
        
        std::getline(std::cin, input);
        
        //move to uppercase for matching purposes
        for(int i=0; i<input.size(); i++){
            input.at(i) = std::tolower(input.at(i));
        }
        sstream.str(input);
        
        //Look through all words for key verbs or nouns
        while(sstream >> first){
            found = false;
            
            //check for special case "with"
            if(first == "with"){
                withFlag = true;
                found = true;
            }
            
            //check for special case "look at"
            if(verb == "look" && first == "at"){
                verb="look_at";
                found = true;
                foundVerb = true;
            }
            
            //check for special case "pick up"
            if(prev == "pick" && first == "up"){
                verb="pick up";
                found = true;
                foundVerb = true;
            }
            
            if(!foundVerb && !found){
                verbFinder(mymap, &verb, &foundVerb, &found, first);
            }
            
            //search for enemy
            if(!found && (verb == "look_at" || verb=="attack") && !foundEnemy && player->getCurrentRoom()->hasEnemy()){
                baddie = enemySearch(player, &found, &foundEnemy, first);
                
            }
            
            //search player inventory
            if(!found && !player->invIsEmpty()){
                checkPlayerInv(world, &foundNoun1, &foundNoun2, &found, &foundInv, noun1, noun2, first);
            }
            
            //search room inventory
            if(!found && !player->getCurrentRoom()->invIsEmpty()){
                checkRoomInv(world, &foundNoun1, &foundNoun2, &found, &foundRoom, noun1, noun2, first);
                
            }
            
            if(!found && (prev.empty() == false) ){
                combo = prev + " " + first;
                
                //look for two word action
                if(!found && !foundVerb){
                    verbFinder(mymap, &verb, &foundVerb, &found, combo);
                    
                }
                
                
                //search for enemy
                if(!found && (verb == "look_at" || verb=="attack") && !foundEnemy && player->getCurrentRoom()->hasEnemy()){
                    baddie = enemySearch(player, &found, &foundEnemy, combo);
                    
                }
                
                //search player inventory
                if(!found && !player->invIsEmpty()){
                    checkPlayerInv(world, &foundNoun1, &foundNoun2, &found, &foundInv, noun1, noun2, combo);
                }
                
                //search room inventory
                if(!found && !player->getCurrentRoom()->invIsEmpty()){
                    checkRoomInv(world, &foundNoun1, &foundNoun2, &found, &foundRoom, noun1, noun2, combo);
                    
                }
                
            }
            
            
            if(!found ){
                prev=first;
            } else {
                prev.clear();
            }
            
            
        }
        
        if(mymap.count(verb) > 0){
            
            choice = mymap.find(verb)->second;
        }
        
        switch(choice){
            case 0:  //Quit game
                std::cout << "So sad to see you leave...\n";
                return 0;
            case 1:  //Attack, Hit
                if(foundNoun1 && withFlag && foundEnemy && noun1->getWeapon()){
                    battle(player, baddie, noun1->getPower());
                }else if(foundNoun1 && withFlag && foundEnemy && !noun1->getWeapon()){
                    cout << "You didn't pick a valid weapon.\n";
                } else if (foundEnemy){
                    battle(player, baddie, 0);
                } else {
                    cout << "What do you want to attack?\n";
                    
                }
                break;
            case 2: //North, n
                world->move(0);
                randomEnemyGenerator(world->getCurrentRoom());
                displayRoom(world, 0);
                break;
            case 3:  //South, s
                world->move(1);
                randomEnemyGenerator(world->getCurrentRoom());
                displayRoom(world, 0);
                break;
                
            case 4:  //East, e
                world->move(2);
                randomEnemyGenerator(world->getCurrentRoom());
                displayRoom(world, 0);
                break;
            case 5:  //West, w
                world->move(3);
                randomEnemyGenerator(world->getCurrentRoom());
                displayRoom(world, 0);
                break;
            case 6:  //Up, u
                world->move(4);
                randomEnemyGenerator(world->getCurrentRoom());
                displayRoom(world, 0);
                break;
            case 7:  //Down, d
                world->move(5);
                randomEnemyGenerator(world->getCurrentRoom());
                displayRoom(world, 0);
                break;
            case 8:  //Grab, Take
                if(foundRoom && foundNoun1 && noun1->getCollectible()){
                    player->addItem(player->getCurrentRoom()->removeItem(noun1));
                    
                }else if(foundRoom && foundNoun1 && !noun1->getCollectible()){
                    cout << "You cannot take that.\n";
                }else {
                    cout << "I don't see that in the room.\n";
                }
                break;
            case 9:  //Inventory, inv
                world->printInventory();
                break;
            case 10:  //Help
                helper();
                break;
            case 11:  //Savegame
                saveWorld(world);
                break;
            case 12:  //Loadgame
                world = loadhelper(world);
                if(world!=NULL){
                    player = world->getPlayer();
                } else {
                    cout << "Error loading game!\n";
                }
                break;
            case 13:  //Look
                //Display the correct room description.
                displayRoom(world, 1);
                
                break;
            case 14:  //Look At
                if(foundNoun1){
                    cout << noun1->getDescription() << "\n";
                }else if(foundEnemy){
                    baddie->getDesc();
                } else {
                    cout << "I don't know what you want to look at.\n";
                }
                break;
            case 15: //Drop
                if(foundInv && foundNoun1){
                    world->dropItem(noun1->getName());
                } else {
                    cout << "I don't see that in your inventory.\n";
                }
                break;
            default:
                std::cout << "I don't know what you are asking for.\n";
        }
    }
    
    return 0;
    
    
}
