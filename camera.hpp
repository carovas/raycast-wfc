#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "wfc.hpp"

#include <raylib.h>

#include <math.h>

class Cam {
public:
    Cam(): pos_x(grid_size/2.f), pos_y(grid_size/2.f), speed(45.f), angle_speed(5.f)
    {

    }  

    Vector2 getpos() {
        return {pos_x, pos_y};
    }

    Vector2 getdelta() {
        return {delta_x, delta_y};
    }

		float getangle() {
			return angle;
		}

    void update(float dt) {

        if(IsKeyDown(KEY_W))
        {
            pos_x = pos_x + delta_x * dt * speed;
            pos_y = pos_y + delta_y * dt * speed;
        }
        if(IsKeyDown(KEY_S))
        {
            pos_x = pos_x - delta_x * dt * speed;
            pos_y = pos_y - delta_y * dt * speed;
        }
        if(IsKeyDown(KEY_D))
        {
            angle = angle + angle_speed * dt;
            if(angle > 2.f*PI)
                angle = angle - 2.f*PI;
            delta_x = cos(angle) * 5.f;
            delta_y = sin(angle) * 5.f;
        }
        if(IsKeyDown(KEY_A))
        {	
            angle = angle - angle_speed * dt;
            if(angle < 0.f)
                angle = angle + 2.f*PI;
            delta_x = cos(angle) * 5.f;
            delta_y = sin(angle) * 5.f;
        }        
    }

private:
    float pos_x;
    float pos_y;
    float delta_x;
    float delta_y;
    float angle; // angle of the player
    float speed;
		float angle_speed;
};

#endif