#include <iostream>
#include <vector>
#include <cstdlib>
#include "Player/Player.h"
#include "Enemy/Enemy.h"

using namespace std;

int main() {

    vector<Enemy> enemies;
    enemies.push_back(Enemy("Ludex Gundyr", 20, 5, 2, 5, 10));
    enemies.push_back(Enemy("Vordt", 30, 7, 3, 7, 15));

    Player *player = new Player("Winter", 100, 12, 4, 10);

    cout << player->toString() << endl << endl;

    while (player->getHealth() > 0 && !enemies.empty()) {
    cout << "Turno del jugador --> selecciona una opcion: " << endl;
  cout << "1. Atacar\n";
   cout << "2. Defender n";

  int choice;
   do {
   cout << " Accion (1-2): ";
   cin >> choice;
  } while (choice < 1 || choice > 2);

  if (choice == 1) {

 for (int i = 0; i < enemies.size(); ++i) {
 cout << i + 1 << ". " << enemies[i].toString() << endl;
 }


 int enemyChoice;
 do {
 cout << "Elige al enemigo que quieres atacar (1-" << enemies.size() << "): ";
  cin >> enemyChoice;
} while (enemyChoice < 1 || enemyChoice > enemies.size());

player->doAttack(&enemies[enemyChoice - 1]);

   if (enemies[enemyChoice - 1].getHealth() <= 0) {
 cout << enemies[enemyChoice - 1].getName() << " Ha muerto" << endl;
 enemies.erase(enemies.begin() + enemyChoice - 1);
 continue;
}
        } else {

   player->setDefense(player->getDefense() * 1.2);
}

        cout << endl << "Enemigos Atacando : " << endl;

        for (int i = 0; i < enemies.size(); ++i) {
  if (enemies[i].getHealth() <= enemies[i].getMaxHealth() * 0.15) {

 if (rand() % 100 < 40) {
  cout << enemies[i].getName() << " se defiende!" << endl;
   continue;
  }
}


  enemies[i].doAttack(player);
  }

  player->setDefense(player->getBaseDefense());
  cout << player->toString() << endl;
  for (Enemy enemy : enemies) {
  cout << enemy.toString() << endl;
  }
 cout << endl;
 }

 if (player->getHealth() <= 0) {
 cout << "Haz Muerto" << endl;
 } else {
 cout << "Haz Ganado" << endl;
}

    delete player;
    return 0;
}
