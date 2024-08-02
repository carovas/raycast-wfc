#include "render.hpp"
#include "camera.hpp"
#include "wfc.hpp"

#include <stdio.h>

int main(int argc, char** argv) {

    Render render_handler(800, 600, "Game");
    
    while (!WindowShouldClose())
    {
        render_handler.setData();
        BeginDrawing();
        render_handler.draw();
        EndDrawing();
    }
}