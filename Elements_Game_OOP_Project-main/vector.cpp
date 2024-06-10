#pragma once
#include <iostream>

class Vector2D{ // 2D vector class for position and velocity
public:
    float x, y;
    Vector2D(){x = 0; y = 0;}

	Vector2D(float p_x, float p_y):x(p_x), y(p_y){}

	void print(){
		std::cout << x << ", " << y << std::endl;
	}
};