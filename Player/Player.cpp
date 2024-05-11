#include <iostream>
#include "Player.h"
#include "../Files/FileHandler.h"

using namespace std;

void Player::saveProgress() {
    char* buffer = this->serialize();
    FileHandler fileHandler = FileHandler();

    fileHandler.writeToFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
}

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer, int _level, int _experience) : Character(_name, _health, _attack, _defense, _speed, _isPlayer) {
    level = _level;
    experience = _experience;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health -= trueDamage;

    if (trueDamage > 0) {
        cout << name << " Recibio " << trueDamage << " de damage!" << endl;

        if (health <= 0) {
            cout << name << " Haz Sido Derrotado" << endl;
        }
    } else {
        gainExperience(10);
        cout << getName() << " Se Defendio Del Ataque" << endl;
    }
}

void Player::levelUp() {
    level++;
    cout << getName() << " HA SUBIDO DE NIVEL- NUEVO NIVEL " << level << endl;
    attack += 20;
    health += 40;
    speed += 40;
    cout << "===============================================" << endl;
    cout << "LOS ATRIBUTOS DE " << getName() << " AUMENTARON" << endl;
    cout << "===============================================" << endl;

}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = experience - 100;
    }
}

Character* Player::selectTarget(std::vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Selecciona A quien Atacar: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(std::vector<Enemy*> enemies) {
    int action = 0;
    cout << "Elige una Accion: " << endl
         << "1. Atacar" << endl
         << "2. Defenderte" << endl
         << "3. Guardar Progreso" << endl;

    //TODO: Validate input
    cin >> action;
    Action currentAction;
    Character* target = nullptr;
    unDefend();

    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target](){
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            currentAction.action = [this](){
                defend();
            };

            currentAction.speed = 9999999;
            break;
        case 3:
            saveProgress();
            return takeAction(enemies);



        default:
            cout << "Invalid action" << endl;
            break;
    }

    return currentAction;
}

char* Player::serialize() {
    char* iterator = buffer;

    memcpy(iterator, &name, sizeof(name));
    iterator += sizeof(name);

    memcpy(iterator, &health, sizeof(health));
    iterator += sizeof(health);

    memcpy(iterator, &attack, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(iterator, &defense, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(iterator, &speed, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(iterator, &isPlayer, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(iterator, &level, sizeof(level));
    iterator += sizeof(level);

    memcpy(iterator, &experience, sizeof(experience));

    return buffer;
}

Player* Player::unserialize(char* buffer) {
    char* iterator = buffer;
    char name[30];
    int health, attack, defense, speed, level, experience;
    bool isPlayer;

    memcpy(&name, iterator, sizeof(name));
    iterator += sizeof(name);

    memcpy(&health, iterator, sizeof(health));
    iterator += sizeof(health);

    memcpy(&attack, iterator, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(&defense, iterator, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(&speed, iterator, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(&isPlayer, iterator, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(&level, iterator, sizeof(level));
    iterator += sizeof(level);

    memcpy(&experience, iterator, sizeof(experience));
    iterator += sizeof(experience);

    return new Player(name, health, attack, defense, speed, isPlayer, level, experience);
}