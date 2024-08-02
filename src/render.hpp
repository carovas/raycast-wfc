#ifndef RENDER_HPP
#define RENDER_HPP

#include <raylib.h>
#include <thread>

class Render {
public: 
    Render(int width, int height, const char* name) {
        InitWindow(width, height, name);
        SetTargetFPS(60);
    }

    ~Render() {
        CloseWindow();
    }

    void setData() {

    }


    void draw() {
        ClearBackground(PURPLE);
    }

};

#endif