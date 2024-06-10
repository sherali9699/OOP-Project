#include <SDL.h> 
#include "vector.cpp"

class Screen{  //Screen class for switching between screens
    SDL_Texture* s_tex;
    
    public:
    Screen(SDL_Texture* start_text); //constructor
    void switch_screen(SDL_Texture* s_tex); //switching screen
    SDL_Texture* getTex(); //getting texture
};
