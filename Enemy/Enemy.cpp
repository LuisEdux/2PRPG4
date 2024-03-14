#include "Enemy.h"
#include "../Utils.h"
#include <iostream>
#include <random>

using namespace std;
using namespace combat_utils;

Enemy::Enemy(string _name, int _health, int _attack, int _defense, int _speed, int _experience)
        : Character(_name, _health, _attack, _defense, _speed, false) {
    experience = _experience;
}
void Enemy::doAttack(Character* target) {
    target->takeDamage(getRolledAttack(attack));
}
void Enemy::takeDamage(int damage) {
    int trueDamage = damage - defense;

    static default_random_engine randomEngine(time(0));
    uniform_int_distribution<int> defenseRoll(0, 100);

    int defenseSuccess = defenseRoll(randomEngine);
    if (defenseSuccess <= getBlockChance()) {
        trueDamage = (int)floor(trueDamage / 2.0);
        cout << name << " se defendio y recibio " << trueDamage << " de damage!" << endl;
    } else {
        cout << name << " recibio  " << trueDamage << " de damage!" << endl;
    }

    health -= trueDamage;

    if (health <= 0) {
    }
}

int Enemy::getExperience() {
    return experience;
}

Character* Enemy::selectTarget(vector<Player*> possibleTargets) {
    int lessHealth = 9999999;
    Character* target = nullptr;
    for (auto character : possibleTargets) {
        if (character->getHealth() < lessHealth) {
            lessHealth = character->getHealth();
            target = character;
        }
    }
    return target;
}

Action Enemy::takeAction(vector<Player*> partyMembers) {
    Action currentAction;
    currentAction.speed = getSpeed();

    Character* target = selectTarget(partyMembers);
    currentAction.target = target;
    currentAction.action = [this, target]() {
        doAttack(target);
    };
    return currentAction;
}
double Enemy::getMaxHealth() {
    return 0;
}
void Enemy::setAttack(double d) {
}
double Enemy::getBaseAttack() {
    return 0;
}

int Enemy::getBlockChance() {
    return 40;
}
