#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Screen.hpp"
#include "GameObj.hpp"



class RenderWindow {
public:
	RenderWindow(const char* p_title, int p_w, int p_h); //constructor
	void cleanUp(); //cleaning up
	void clear(); //clearing screen
	void render(GameObject& g_object); //rendering game object
    void render(Screen& g_screen); //rendering screen
	void display(); //displaying

	SDL_Window* getWindow(); //getting window
	SDL_Renderer* getRenderer(); //getting renderer

	SDL_Texture* LoadTexture(const char* filename); //loading texture

private:
	SDL_Window* window; //window
	SDL_Renderer* renderer; //renderer
};