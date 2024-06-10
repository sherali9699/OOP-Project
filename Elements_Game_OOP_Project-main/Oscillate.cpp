#include "Oscillator.hpp"
#include<iostream>
using namespace std;


void Oscillator::Oscillate()
{
    double time = SDL_GetTicks() / 1000.0;   // time in seconds
    double amplitude = 2.75;
    double frequency = 0.25;
    int yOffset = amplitude * std::sin(2 * M_PI * frequency * time);  // y offset from sin wave
    
    setpos(getpos().x,getpos().y + yOffset); // set the position of the object


}