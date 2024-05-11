#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Files/FileHandler.h"

void Player::displayStats() const {
    using namespace std;

    cout << "=====================================" << endl;
    cout << "Estadisticas del Jugador:" << endl;
    cout << "Name: " << name << endl;
    cout << "Health: " << health << endl;
    cout << "Attack: " << attack << endl;
    cout << "Defense: " << defense << endl;
    cout << "Speed: " << speed << endl;
    cout << "=====================================" << endl;


}

Player* loadPlayerInfo() {
    try {
        char buffer[Player::BUFFER_SIZE];
        FileHandler fileHandler = FileHandler();
        fileHandler.readFromFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
        return Player::unserialize(buffer);
    } catch(int error) {
        return new Player("SOLID", 50, 18, 7, 8);
    }
}

int main() {
    Player *player = loadPlayerInfo();
    Enemy *enemy = new Enemy("DEMONIO 1", 10, 10, 7, 8, 10);
    Enemy *enemy2 = new Enemy("DEMONIO 2", 10, 10, 7, 8, 10);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    player->displayStats();

    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;
    return 0;
}
