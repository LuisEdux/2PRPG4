#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"

int main() {
    Player *player = new Player("Alexis", 100, 8, 3, 10);
    Enemy *enemy = new Enemy("Destello absoluto", 50, 6, 2, 5, 10);
    int cont = 0;
    int auxPlayer, auxEnemy;

    while(player->getHealth() > 0 && enemy->getHealth() > 0){
        auxPlayer = player->getHealth();
        auxEnemy = enemy->getHealth();

        cont++;
        cout<<"\n\n\tTurno "<<cont<<"."<<endl;


        cout<<player->toString()<<endl;
        cout<<enemy->toString()<<endl;

        player->doAttack(enemy);
        enemy->doAttack(player);

        cout<<"\n";

        cout<<"\t"<<player->getName()<<" ha atacado a "<<enemy->getName()<<" con "<<auxEnemy - enemy->getHealth()<<" puntos de vida"<<endl;
        cout<<"\t"<<enemy->getName()<<" ha atacado a "<<player->getName()<<" con "<<auxPlayer - player->getHealth()<<" puntos de vida"<<endl<<endl;

        cout<<"---------------------";
    }

    cout<<"\n"<<player->toString()<<endl;
    cout<<enemy->toString()<<endl;

    if(auxPlayer <= 0) cout<<"\n\tEl jugador ha perdido ";
    else cout<<"\n\tEl enemigo ha perdido ";

    cout<<"en "<<cont<<" turnos."<<endl;

    delete player;
    delete enemy;
    return 0;
}
