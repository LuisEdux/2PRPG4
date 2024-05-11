#include "Enemy.h"
#include "../Utils.h"
#include <iostream>

using namespace std;
using namespace combat_utils;

Enemy::Enemy(char* _name, int _health, int _attack, int _defense, int _speed, int _experience) : Character(_name, _health, _attack, _defense, _speed, false) {
    experience = _experience;
}

void Enemy::UpgrateEnemies(){
    cout << "===================" << endl;
    cout << " ATRIBUTOS DE " << name <<  endl;
    cout << "===================" << endl;
    health += 10;
    attack += 4;
    defense += 5;
    speed += 10;
    cout << " ATRIBUTOS " << endl;
    cout << " Ataque " << attack << endl;
    cout << " salud " << health << endl;
    cout << " defensa " << defense << endl;
    cout << " velocidad " << speed << endl;
    cout << "===================" << endl;
}



void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

void Enemy::takeDamage(int damage) {
    int trueDamage = damage - defense;
    health -= trueDamage;

    cout << name << " Recibio " << trueDamage << " de damage!" << endl;
    if(health <= 0) {
        cout << name << " Ha sido Derrotado" << endl;




    }


}

int Enemy::getExperience() {



}

Character* Enemy::selectTarget(vector<Player*> possibleTargets) {
    // Selecciona el objetivo con menos salud
    int lessHealth = 9999999;
    Character* target = nullptr;
    for(auto character : possibleTargets) {
        if(character->getHealth() < lessHealth) {
            lessHealth = character->getHealth();
            target = character;
        }
    }
    return target;
}



Action Enemy::takeAction(vector<Player*> partyMembers) {
    int chance  = 1 + rand() % (101 - 1);
    Action currentAction;

    unDefend();

    if(getHealth() < getMaxHealth() * .55 && chance <= 70){
        currentAction.action = [this]() {
            defend();
        };

        currentAction.speed = 999999;

    } else {
        Character* target = selectTarget(partyMembers);
        currentAction.target = target;
        currentAction.action = [this, target](){
            doAttack(target);
        };
        currentAction.speed = getSpeed();

    }

    return currentAction;

}
