#ifndef WFC_HPP
#define WFC_HPP

#include <random>
#include <iostream> 

const size_t grid_size = 50;

class WaveFunctionCollapse {
public:
    WaveFunctionCollapse() {
        std::fill_n(grid, grid_size*grid_size, 100);
        for(int y = 0; y < 2; y++)
					for(int x = 0; x < grid_size; x++) 
						grid[x + y * 2450] = 0;

				for(int x = 0; x < 2; x++)
					for(int y = 0; y < grid_size; y++) 
						grid[x * 49 + y * 50] = 0;
    }

    void generate() {

    }

    int grid[grid_size*grid_size];
};

#endif