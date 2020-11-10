#include "game.hpp"

int main(){
    Game game("Life", 400, 250);    

    while(game.isRun()){
        game.clear();
        //Check input       TODO:Game.input(); 
        game.update();
        game.render();
        game.wait();
    }

    return 0;
}