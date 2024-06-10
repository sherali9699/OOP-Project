#pragma once

#include <SDL.h>
#include <vector>
#include <cmath>
#include "vector.cpp"


class GameObject {
protected:
    Vector2D pos;
    SDL_Rect rect;
    SDL_Texture* objtex;

public:
    
    GameObject(int x, int y, SDL_Texture* o_tex);
    void changeTex(SDL_Texture* o_tex);
    SDL_Rect getRect();
    SDL_Texture* getTex();
    Vector2D getpos();
    virtual bool Collision(GameObject*  object);
    void setpos(int x, int y);
    virtual ~GameObject();
};










