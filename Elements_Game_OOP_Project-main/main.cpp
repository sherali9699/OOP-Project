

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "GameObj.hpp"
#include <vector>
#include "RenderWindow.hpp"
#include "Player.hpp"
#include "Coin.hpp"
#include "Door.hpp"
#include "Oscillator.hpp"




float getCurrentTime(){
    return SDL_GetTicks()/1000.0f;
}

bool has_touched_with_door=false;
void is_yes(){
    has_touched_with_door=true;
}

int main(int argc, char* args[]){
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl; //flag to check SDL initialized

	srand(time(0));


    /*------------------WINDOW & RENDERER---------------*/
	RenderWindow window("Elements", 800, 600);
	SDL_Renderer* renderer = window.getRenderer();

   
    //upload music
    Mix_Music *music = nullptr;
    // Load other sound effects
    Mix_Chunk* coinCollisionSound = nullptr;
    Mix_Chunk* jumpMusic = nullptr;


    /*--------------LOAD TEXTURE-----------------*/
    SDL_Texture* p_fire_tex = window.LoadTexture("assets/FireChar.png");
    SDL_Texture* p_water_tex = window.LoadTexture("assets/WaterChar.png");
    SDL_Texture* game_bg = window.LoadTexture("assets/bg.png");
    SDL_Texture* mainscreen = window.LoadTexture("assets/gameStart.png");
    SDL_Texture* border = window.LoadTexture("assets/borders.png");
    SDL_Texture* w_coin = window.LoadTexture("assets/s_jewel.png");
    SDL_Texture* f_coin = window.LoadTexture("assets/f_jewel.png");
    SDL_Texture* platform  = window.LoadTexture("assets/platform.png"); 
    SDL_Texture* top = window.LoadTexture("assets/top_bound.png");
    SDL_Texture* ground = window.LoadTexture("assets/ground.png");
    SDL_Texture* water_platform = window.LoadTexture("assets/water_plat.png");
    SDL_Texture* fire_platform = window.LoadTexture("assets/fire_plat.png");
    SDL_Texture*  s_platform = window.LoadTexture("assets/platform_small.png");
    SDL_Texture*  box = window.LoadTexture("assets/box.png");
    SDL_Texture*  door = window.LoadTexture("assets/door.png");
    SDL_Texture*  f_platform = window.LoadTexture("assets/f_platform.png");
    SDL_Texture*  endScreen = window.LoadTexture("assets/endScreen.png");
    SDL_Texture*  failScreen = window.LoadTexture("assets/failScreen.png");

   
    /*-------------INITIALIZE PLAYER & LEVEL VECTORS-------------------*/
    Player player2(50,500,p_water_tex); //player constructor for player 2(always Water Character)
    Player player1(100,500,p_fire_tex); //player constructor for player 1(always Fire Character)


    std::vector<GameObject*> platforms ; //vector of platforms
    std::vector<Coin*> coins ; //vector of coins
    std::vector<Door*> doors ; //vector of doors
    std::vector<GameObject*> firePlatform; //vector of firePlatforms
    std::vector<GameObject*> waterPlatform; //vector of waterPlatforms

  
    GameObject* plat_1 = new GameObject(0,600,ground);
    GameObject* plat_2 = new GameObject(0,400,s_platform);
    GameObject* plat_3 = new GameObject(200,400,s_platform);

    GameObject* plat_4 = new GameObject(400,400,s_platform);
    GameObject* plat_5 = new GameObject(400,275,s_platform);
    GameObject* plat_6 = new GameObject(600,275,s_platform);

    GameObject* plat_7 = new GameObject(200,120,s_platform);
    GameObject* plat_8 = new GameObject(400,120,s_platform);
    GameObject* plat_9 = new GameObject(0,120,s_platform);
    GameObject* plat_10 = new GameObject(200,275,s_platform);

    GameObject* plat_11 = new Oscillator(600,190,s_platform);
    GameObject* plat_12 = new   Oscillator(200,500,f_platform);
   

    GameObject* top1 = new GameObject(0,0,top);
    GameObject* wall1 = new GameObject(0,500,border);
    GameObject* wall2 = new GameObject(800,500,border);

    GameObject* Door1 = new Door(10,90,door);

    GameObject* fireplat_1 = new GameObject(0,500,fire_platform);
    GameObject* fireplat_2 = new GameObject(0,300,fire_platform);
    GameObject* water_plat1 = new GameObject(0,100,water_platform);
    GameObject* water_plat2 = new GameObject(200,100,water_platform);


    Coin* c1 = new ff_coin(100,450,f_coin);
    Coin* c2 = new ww_coin(250,450,w_coin);
    Coin* c3 = new ww_coin(400,450,w_coin);
    Coin* c4 = new ff_coin(550,450,f_coin);
    Coin* c5 = new ww_coin(700,450,w_coin);
    Coin* c6 = new ff_coin(100,250,f_coin);
    Coin* c7 = new ww_coin(250,250,w_coin);
    Coin* c8 = new ff_coin(400,250,f_coin);
    Coin* c9 = new ww_coin(550,250,w_coin);
    Coin* c10 = new ff_coin(700,250,f_coin);
    Coin* c11 = new ww_coin(100,50,w_coin);
    Coin* c12 = new ff_coin(250,50,f_coin);

        // Initialize SDL_mixer for audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

    // Load the audio file
    music = Mix_LoadMUS("assets/Hitman(chosic.com).mp3");
    coinCollisionSound=Mix_LoadWAV("assets/coinSound.wav");
    jumpMusic=Mix_LoadWAV("assets/jumpSound.wav");


    if (!music || !coinCollisionSound || !jumpMusic) {
        std::cout << "Failed to load audio files! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return -1;
    }
    
    Mix_PlayMusic(music, -1); // Play the background music infinitely
        


    /*-------------------INITIALIZING OTHER GAME VALUES--------------------*/
    
    /*-------Game States---------*/
    bool isReset = false ;
    bool isInMenu = true ;// main menu screen is default screen   
    bool isInGame = false;
    bool isWin = false;
    bool isLose = false;

    int totalCoins = 12;
    

    bool gamerun = true; //To run the game 
 
    Screen background(mainscreen);

    SDL_Event event; //to poll events 

    const Uint8* keyboard = SDL_GetKeyboardState(NULL); //Keyboard inputs 

    float currentTime = getCurrentTime();


    

    /*------GAME LOOP------*/

    while(gamerun){
        currentTime = getCurrentTime();
        if (SDL_PollEvent(&event) && (event.type == SDL_QUIT)){
            gamerun = false;
        }

        if(isInMenu){
            window.clear();
            window.render(background);
            window.display();
        
        if(keyboard[SDL_SCANCODE_RETURN]){
            isInMenu = false;
            isInGame = true;
            background.switch_screen(game_bg);
            }
        } 
        else if(isInGame){
            if(!isReset){
                window.clear();
                window.render(background);

                /*------------------ADDING/RESETING PLATFORMS-----------------*/
                platforms.push_back(plat_12);
                platforms.push_back(plat_1);
                platforms.push_back(plat_2);
                platforms.push_back(plat_3);
                platforms.push_back(plat_4);
                platforms.push_back(plat_5);
                platforms.push_back(plat_6);
                platforms.push_back(plat_7);
                platforms.push_back(plat_8);
                platforms.push_back(plat_9);
                platforms.push_back(plat_10);
                platforms.push_back(plat_11);
               

                platforms.push_back(top1);
                platforms.push_back(wall1);
                platforms.push_back(wall2);
                platforms.push_back(Door1); 
                /*----------------ADDING/RESTING COINS---------------------*/
                coins.push_back(c1);
                coins.push_back(c2);
                coins.push_back(c3);
                coins.push_back(c4);
                coins.push_back(c5);
                coins.push_back(c6);
                coins.push_back(c7);
                coins.push_back(c8);
                coins.push_back(c9);
                coins.push_back(c10);
                coins.push_back(c11);
                coins.push_back(c12);




                /*----------------INTIALIZING/RESTING PLAYER LOCATION---------------------*/
                player1.setpos(100,475);
                player2.setpos(50,475);



                
                window.display();

                isReset = true; //resetting the game
            }
            else{
            /*                              HANDLE PLAYER CONTROLS                                     */

				if(keyboard[SDL_SCANCODE_LEFT]){ //player 1 goes left
					player1.MoveLeft(platforms);
				}
				if(keyboard[SDL_SCANCODE_RIGHT]){   //player 1 goes right
					player1.MoveRight(platforms);
                    
				}
                if(keyboard[SDL_SCANCODE_UP]){ //player 1 jumps

                    player1.Jump(platforms);
                }
                if(keyboard[SDL_SCANCODE_A]){ //player 2 goes left
                    player2.MoveLeft(platforms);
                }
                if(keyboard[SDL_SCANCODE_D]){  //player 2 goes right
                    Mix_PlayChannel(2, jumpMusic, 0);
                    player2.MoveRight(platforms);
                }
                if(keyboard[SDL_SCANCODE_W]){ //player 2 jumps
                    Mix_PlayChannel(2, jumpMusic, 0);
                    player2.Jump(platforms);
                }
                if(keyboard[SDL_SCANCODE_R]){
                    isReset = false;
                    coins[0]->ResetCoinCounter();
                    platforms.clear();
                    coins.clear();
                }

            }

            /*---------------GAME UPDATES---------------*/
            player1.Gravity(platforms);
            player2.Gravity(platforms);

          

            /*------------COIN HANDLING---------------*/
             for (int i = 0; i < coins.size(); i++) {
                ff_coin* ffCoin = dynamic_cast<ff_coin*>(coins[i]);
                ww_coin* wwCoin = dynamic_cast<ww_coin*>(coins[i]);
                if (coins[i]->Collision(&player1) && ffCoin) {
                
                    // Process other collision-related actions
                    Mix_PlayChannel(1, coinCollisionSound, 0);
                    coins.erase(coins.begin() + i);
                    coins[i]->increaseCoinCounter();
                    std::cout << coins[i]->GetCoinCounter();
                
                }  else if (coins[i]->Collision(&player2) && wwCoin) {
                
                    // Process other collision-related actions
                    Mix_PlayChannel(1, coinCollisionSound, 0);
                    coins.erase(coins.begin() + i);
                    coins[i]->increaseCoinCounter();
                    std::cout << coins[i]->GetCoinCounter();
                }             
             }

            /*------------WIN---------------*/
            //winning condition checking
            
            if(coins[0]->GetCoinCounter() == totalCoins){
                if (player1.it_is_true || player2.it_is_true){
                isWin = true;
                isInGame = false;
                coins[0]->ResetCoinCounter();

              
                for (auto it = platforms.begin(); it != platforms.end(); ) {
                  
                    if (*it == plat_12 || *it == plat_11 || *it == plat_10 || *it == plat_9 || *it == plat_8 || *it == plat_7 || *it == plat_6 || *it == plat_5 || *it == plat_4 || *it == plat_3 || *it == plat_2 || *it == plat_1 || *it == top1 || *it == wall1 || *it == wall2 || *it == Door1) {
                       // delete *it; // Free memory
                        it = platforms.erase(it); // Remove from vector
                    } else {
                        ++it;
                    }
                }
                background.switch_screen(endScreen);
         
            }
            }
            

            /*------------Oscillator---------------*/

            Oscillator* o = dynamic_cast<Oscillator*>(plat_11);
            o->Oscillate();
            Oscillator* o2 = dynamic_cast<Oscillator*>(plat_12);
            o2->Oscillate();


            /*-----------------RENDERING ALL THINGS------------------*/
            window.clear();
            window.render(background);
            for (int i = 0; i < platforms.size(); i++) {
                window.render(*platforms[i]);
            }

            for(auto& coin: coins){
                window.render(*coin);
            }
            window.render(player1);
            window.render(player2);
            window.display();
		}
    


        if (isWin) {
            window.clear();
            window.render(background);
            window.display();
            if(keyboard[SDL_SCANCODE_R]){
                platforms.clear();
                coins.clear();
                isWin = false;
                isInGame = true;
                isReset = false;
                background.switch_screen(game_bg);
            }
        }
        if (isLose) {
            window.clear();
            window.render(background);
            window.display();
            if(keyboard[SDL_SCANCODE_R]){
                platforms.clear();
                coins.clear();
                isLose = false;
                isInGame = true;
                isReset = false;
                background.switch_screen(game_bg);
            }
        }

    }


	window.cleanUp(); // DELETE EVERYTHING ON SCREEN


    /*------------------FREE MEMORY-----------------*/
    for(int i = 0 ; i < platforms.size(); i ++)
    {
        delete platforms[i];
        platforms[i] = nullptr;
    }

    for(int i = 0; i < coins.size(); i++)
    {
        delete coins[i];
        coins[i] = nullptr;
    }
	
  

	SDL_Quit(); 

    return 0; 
}

