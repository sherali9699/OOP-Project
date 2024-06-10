#pragma once

#include "GameObj.hpp"
#include "Player.hpp"

class Coin: public GameObject {
    protected:
    static int coinCounter;  //counter for the coins

    public:
    Coin(int x, int y, SDL_Texture* c_tex);
    static void ResetCoinCounter(); //reset the counter
    static int GetCoinCounter();    //get the counter
    void increaseCoinCounter();    //increase the counter
    
};


class ff_coin: public Coin{ //ff = fire coin
    public:
    ff_coin(int x, int y, SDL_Texture* c_tex): Coin(x, y, c_tex){}
};

class ww_coin: public Coin{ //ww = water coin
    public:
    ww_coin(int x, int y, SDL_Texture* c_tex): Coin(x, y, c_tex){}
};