//
// Created by Victor Navarro on 15/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include <string>

using namespace std;

class Character {
protected:
    char name[30];
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    int maxHealth;
    int maxDefense;
public:
    Character(char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer); // Cambio de string a char en el constructor

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    //TODO: Implementar metodo de defensa
    //Incrementar la defensa un 20% solo por el turno actual

    bool flee(Character* target);
    char* getName();
    int getHealth();

    int getAttack();
    int getDefense();
    void defend();
    void unDefend();
    int getMaxHealth();
    int getMaxDefense();
    bool getIsPlayer();
    int getSpeed();
    char* toString();
};


#endif //RPG_CHARACTER_H
