#include "game.hpp"

int main(){
    Game game("Life", 120, 120);

    while(game.isRun()){
        game.clear();
        game.handleEvents();
        game.update();
        game.render();
        game.wait();
    }

    return 0;
}
