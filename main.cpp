#include "render.hpp"
#include "camera.hpp"
#include "wfc.hpp"

#include <stdio.h>

int main(int argc, char** argv) {

    Render render_handler(window_width, window_height, "Game");
    WaveFunctionCollapse WFC;
    Cam plr;
    
    render_handler.setData(WFC.grid);
    render_handler.set_player_ptr(&plr);

    while (!WindowShouldClose())
    {
        plr.update(GetFrameTime());

        //render_handler.setData();
        BeginDrawing();
        render_handler.draw();
        EndDrawing();
    }
}