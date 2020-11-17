#include "game.hpp"

int main(){
    Game game("Life", 600, 600);

    while(game.isRun()){
        game.clear();
        game.handleEvents();
        game.update();
        game.render();
        game.wait();
    }

    return 0;
}
