#include "ant.hpp"
#include "grid.hpp"
#include <iostream>

using namespace std;

Ant::Ant(Grid* grid, int x, int y) : Critter(grid, x, y) {
    time_since_last_move = 0;
}

void Ant::move() {
    // predefined directions ant can move
    int directions[8][2] = {
        {0, -1},  // up
        {1, -1},  // up-right
        {1, 0},   // right
        {1, 1},   // down-right
        {0, 1},   // down
        {-1, 1},  // down-left
        {-1, 0},  // left
        {-1, -1}  // up-left
    };

    // randomly select one of those directions
    int direction = rand() % 8;
    int new_x = x + directions[direction][0];
    int new_y = y + directions[direction][1];

    // check if the new cell is within grid bounds
    if (new_x >= 0 && new_x < grid->get_width() && new_y >= 0 && new_y < grid->get_height()) {
        // check if the new cell is empty
        if (grid->get_cell(new_x, new_y)->is_empty()) {
            // move to the new cell
            grid->get_cell(new_x, new_y)->set_critter(this);
            grid->get_cell(x, y)->clear();
            x = new_x;
            y = new_y;
            // reset the starvation counter
            time_since_last_move = 0; 
        } else {
            // if the cell is occupied, the ant stays in its current cell
            time_since_last_move++;
        }
    } else {
        // handle bouncing off walls 
        if (new_x < 0) new_x = -new_x;
        if (new_x >= grid->get_width()) new_x = 2 * (grid->get_width() - 1) - new_x;
        if (new_y < 0) new_y = -new_y;
        if (new_y >= grid->get_height()) new_y = 2 * (grid->get_height() - 1) - new_y;

        if (grid->get_cell(new_x, new_y)->is_empty()) {
            // move to the new cell after bounce
            grid->get_cell(new_x, new_y)->set_critter(this);
            grid->get_cell(x, y)->clear();
            x = new_x;
            y = new_y;
            // reset the starvation counter
            time_since_last_move = 0; 
        } else {
            // if the bounced cell is occupied, the ant stays in its current cell
            time_since_last_move++;
        }
    }

    // set moved flag
    moved = true;
}

void Ant::breed() {
    // normal ants can't breed
    return;
}

void Ant::die() {
    if (time_since_last_move >= 5) {
        grid->get_cell(x, y)->clear();
        delete this;
    }
}

void Ant::print() const {
    cout << 'o'; 
}
