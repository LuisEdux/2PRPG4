//
// Created by Victor Navarro on 15/02/24.
//

#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"

using namespace std;

int main() {
    Player *player = new Player("Victor", 100, 8, 4, 10);
    Enemy *enemy = new Enemy("Estudiante de Redes", 50, 5, 2, 5, 10);

    cout << player->toString() << endl;
    cout << enemy->toString() << endl;

    cout << "=====================" << endl;

    for (int round = 1; player->getHealth() > 0 && enemy->getHealth() > 0; ++round) {
     cout << "ronda " << round << endl;

    player->doAttack(enemy);

    if (enemy->getHealth() <= 0) {
     cout << enemy->getName() << " Ha muerto" << endl;
     break;
      }

      enemy->doAttack(player);

      if (player->getHealth() <= 0) {
      cout << player->getName() << " Ha muerto" << endl;
      break;
      }

      cout << player->toString() << endl;
      cout << enemy->toString() << endl;
      }
       delete player;
       delete enemy;
       return 0;
     }
