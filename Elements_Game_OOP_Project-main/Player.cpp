#include "Player.hpp"



Player::Player(int x, int y, SDL_Texture* p_tex):MovingObject(x,y,p_tex){}



void Player::MoveLeft(std::vector<GameObject*> objects){
    for( int i = 0; i < 8; i++){
        setpos(getpos().x - 1, getpos().y); //moving left
        for (int i = 0; i < objects.size(); i++) {
            if (Collision((objects[i]))) {
                //dynamic casting to check wheather what to whicle get touch with door
                Door* door = dynamic_cast<Door*>(objects[i]);
                if (door){
                    std::cout<<"yeah"<<std::endl;
                    it_is_true=true;
                } 
                setpos(getpos().x + 1, getpos().y); //if collision happens then set back to previous position
                break;
            }
        }
    }
}

void Player::MoveRight(std::vector<GameObject*> objects){
    for( int i = 0; i < 8; i++){
        setpos(getpos().x + 1, getpos().y); //moving right
        for (int i = 0; i < objects.size(); i++) {
            if (Collision((objects[i]))) {
                setpos(getpos().x - 1, getpos().y); //if collision happens then set back to previous position
                break;
            }
        }
    }
}

void Player::Jump(std::vector<GameObject*> objects){
    if(!isJumping){
        setSpeed(0,-13.0f); //jumping
        isJumping = true;   
    }
}

