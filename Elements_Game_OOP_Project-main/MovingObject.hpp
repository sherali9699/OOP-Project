#pragma once 

#include "GameObj.hpp"

class MovingObject: public GameObject {
private:
    Vector2D speed;
protected:
    bool isJumping = false;  //more appropriate name is goingUp

public:
    MovingObject(int x, int y, SDL_Texture* m_tex); //constructor
    Vector2D getSpeed(); //getting speed
    void setSpeed(float m_x, float m_y); //setting speed
    void Gravity(std::vector<GameObject*> objects);         //gravity

};