#pragma once


#include "MovingObject.hpp"
#include "GameObj.hpp"
#include "Door.hpp"


class Player: public MovingObject {
    public:
    bool it_is_true=false; //for the door
    
    Player(int x, int y,SDL_Texture* p_tex);    //constructor
    void MoveRight(std::vector<GameObject*> objects); //move right
    void MoveLeft( std::vector<GameObject*> objects); //move left
    void Jump(std::vector<GameObject*> objects); //jump
};
