#ifndef RENDER_HPP
#define RENDER_HPP

#include "wfc.hpp"
#include "camera.hpp"

#include <raylib.h>

#define P2 PI / 2
#define P3 3*PI /2
#define DR 0.0174533

const int window_width = 800;
const int window_height = 600;

class Render {
public: 
    Render(int width, int height, const char* name) {
        InitWindow(width, height, name);
        SetTargetFPS(60);
        map_texture = LoadTexture("./Graphics/blank.png");
    }

    ~Render() {
        UnloadTexture(map_texture);
        CloseWindow();
    }

    void setData(int* data) {
        map_data = data;

        
        /*
        Image tmpImage = LoadImageFromTexture(map_texture);
        for(int x = 0; x < grid_size; x++) {
            for(int y = 0; y < grid_size; y++) {
                ImageDrawPixel(&tmpImage, x, y, {map_data[x+y*grid_size]*2.55f, map_data[x+y*grid_size]*2.55f, map_data[x+y*grid_size]*2.55f, 255}); // ignore the error, it works fine
            }
        }
        map_texture = LoadTextureFromImage(tmpImage);
        UnloadImage(tmpImage);
        */
        
    }

    void set_player_ptr(Cam* ptr) {
        player = ptr;
    }

    float dist(float ax, float ay, float bx, float by, float ang) {
        return (sqrt((bx-ax) * (bx-ax) + (by - ay) * (by - ay)));
    }

    void draw() {
        Vector2 ppos = player->getpos();
        Vector2 pdelta = player->getdelta();
        ClearBackground(BLACK);

        // 2d representation
        //DrawTexturePro(map_texture, {0, 0, 50, 50}, {0, 0, window_width, window_height}, {0, 0}, 0, WHITE);
        //DrawCircleV(ppos, 20.F, RED);
        //DrawLineV(ppos, {ppos.x + pdelta.x * 5, ppos.y + pdelta.y * 5}, YELLOW);

        // going 3d
        
        int r, mx, my, mp, dof;
        float rx, ry, ra, xo, yo, distT;
        ra = player->getangle() - DR*45;
        if(ra < 0)
            ra += 2*PI;
        if(ra>2*PI)
            ra-= 2*PI;

        for(r = 0; r < 90; r++) {
            //HORIZONTAL LINES
            dof = 0;
            float atant = -1/tan(ra);
            float distH = 100000.f, hx=ppos.x, hy = ppos.y;

            if(ra>PI) {
                ry = (((int)ppos.y >> 6) << 6) - 0.0001f; // looking up
                rx = (ppos.y-ry)*atant+ppos.x;
                yo = -50;
                xo = -yo * atant;
            }
            if (ra<PI) {
                ry = (((int)ppos.y >> 6) << 6) + 64.f; // looking down
                rx = (ppos.y-ry)*atant+ppos.x;
                yo = 50;
                xo = -yo * atant;
            }
            if(ra == 0 || ra == PI) {
                rx = ppos.x;
                ry = ppos.y;
                dof = 8;
            }
            while (dof < 8)
            {
                mx = (int)(rx) >> 6;
                my = (int)(ry) >> 6;
                mp = my*grid_size+mx; // MAP POS
                if(mp > 0 && mp < grid_size * grid_size && map_data[mp] == 0) { // hit wall
                    hx = rx;
                    hy = ry;
                    distH = dist(ppos.x, ppos.y, hx, hy, ra);
                    dof = 8;
                } else {
                    rx = rx + xo;
                    ry = ry + yo;
                    dof++;
                }
            }
            // 2d line
            //DrawLineEx(ppos, {rx, ry}, 10.f, GREEN);

            // VERTICAL LINE
            dof = 0;
            float ntant = -tan(ra);
            float distV = 100000.f, vx=ppos.x, vy = ppos.y;

            if(ra>P2 && ra < P3) {
                rx = (((int)ppos.x >> 6) << 6) - 0.0001f; // lef
                ry = (ppos.x-rx)*ntant+ppos.y;
                xo = -50;
                yo = -xo * ntant;
            }
            if (ra<P2 || ra>P3) {
                rx = (((int)ppos.x >> 6) << 6) + 64.f; // looking right
                ry = (ppos.x-rx)*ntant+ppos.y;
                yo = 50;
                yo = -xo * ntant;
            }
            if(ra == 0 || ra == PI) {
                rx = ppos.x;
                ry = ppos.y;
                dof = 8;
            }
            while (dof < 8)
            {
                mx = (int)(rx) >> 6;
                my = (int)(ry) >> 6;
                mp = my*grid_size+mx; // MAP POS
                if(mp > 0 && mp < grid_size * grid_size && map_data[mp] == 0) { // hit wall
                    vx = rx;
                    vy = ry;
                    distV = dist(ppos.x, ppos.y, vx, vy, ra);
                    dof = 8;
                } else {
                    rx = rx + xo;
                    ry = ry + yo;
                    dof++;
                }
            }
            if(distV<distH) {
                rx = vx;
                ry = vy;
                distT = distV;
            } else if (distH> distV) {
                rx = hx;
                ry = hy;
                distT = distH;
            }
            // 2d line
            DrawLineV(ppos, {rx, ry}, RED);

            // actually drawing in 3d before it was just ray calc
            float lineH = (50*window_width*2)/distT;
            if(lineH > window_height*2)
                lineH = window_height*2;
            
            float lineO = window_height-lineH/2;

            DrawLineEx({r*8, lineO}, {r*8, lineH + lineO}, 8, WHITE);

            ra = ra + DR;
            if(ra < 0)
                ra += 2*PI;
            if(ra>2*PI)
                ra-= 2*PI;
        }

    }

private:
    Texture2D map_texture;
    int* map_data;
    Cam* player;
};

#endif