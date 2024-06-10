#pragma once

#include "GameObj.hpp"
#include "Player.hpp"

using namespace std;
class Door: public GameObject{
    public:
        bool active;
        Door(int x, int y , SDL_Texture* o_tex) :GameObject(x, y, o_tex){};
       
};
// if player yeet then show screen(active == 1 load screen)