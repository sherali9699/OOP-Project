#pragma once

#include <SDL.h>
#include <cmath>
#include "GameObj.hpp"


class Oscillator: public GameObject
{
    public:

        Oscillator(int x, int y, SDL_Texture* o_tex):GameObject(x,y,o_tex){}; //constructor
        void Oscillate(); //oscillate the object


};
