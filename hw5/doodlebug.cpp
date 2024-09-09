#include "doodlebug.hpp"
#include "ant.hpp"
#include "grid.hpp"
#include <iostream>
#include <cstdlib>  

using namespace std;

Doodlebug::Doodlebug(Grid* grid, int x, int y) : Critter(grid, x, y) {
    time_since_last_eat = 0;
    time_since_last_breed = 0;
    // randomize starting clockwise position
    direction = rand() % 8;
}

void Doodlebug::move() {
    // check for adjacent ants first and move to eat them if found
    int directions[8][2] = {
        {0, -1},  // north
        {1, -1},  // northeast
        {1, 0},   // east
        {1, 1},   // southeast
        {0, 1},   // south
        {-1, 1},  // southwest
        {-1, 0},  // west
        {-1, -1}  // northwest
    };

    // first, try to find an ant to eat
    for (int i = 0; i < 8; ++i) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (new_x >= 0 && new_x < grid->get_width() && new_y >= 0 && new_y < grid->get_height()) {
            Critter* critter = grid->get_cell(new_x, new_y)->get_critter();
            if (critter && dynamic_cast<Ant*>(critter)) {
                // chance for the ant to evade the doodlebug
                if (rand() % 100 < 10) { 
                    // cout << "Ant at (" << new_x << ", " << new_y << ") evaded doodlebug at (" << x << ", " << y << ").\n";
                    continue;
                }

                delete critter;
                grid->get_cell(new_x, new_y)->set_critter(this);
                grid->get_cell(x, y)->clear();
                x = new_x;
                y = new_y;
                time_since_last_breed++;
                time_since_last_eat = 0;
                moved = true; 
                return;
            }
        }
    }

    // if no adjacent ants are found, move in the current direction
    int new_x = x + directions[direction][0];
    int new_y = y + directions[direction][1];

    // bounce logic
    if (new_x < 0 || new_x >= grid->get_width() || new_y < 0 || new_y >= grid->get_height()) {
        // reflect the position
        if (new_x < 0) new_x = -new_x;
        if (new_x >= grid->get_width()) new_x = 2 * (grid->get_width() - 1) - new_x;
        if (new_y < 0) new_y = -new_y;
        if (new_y >= grid->get_height()) new_y = 2 * (grid->get_height() - 1) - new_y;

        // if the reflected position is still out of bounds, skip the move
        if (new_x < 0 || new_x >= grid->get_width() || new_y < 0 || new_y >= grid->get_height()) {
            direction = (direction + 1) % 8;
            time_since_last_breed++;
            time_since_last_eat++;
            moved = true; 
            return;
        }

        // update the direction to continue the clockwise pattern after bouncing
        if (direction == 4) { 
            direction = 1; 
        } else if (direction == 5) { 
            direction = 2; 
        } else if (direction == 6) { 
            direction = 3; 
        } else if (direction == 7) { 
            direction = 0; 
        }
    }

    Critter* critter = grid->get_cell(new_x, new_y)->get_critter();
    if (critter == nullptr) {
        // move to the new cell if empty
        grid->get_cell(new_x, new_y)->set_critter(this);
        grid->get_cell(x, y)->clear();
        x = new_x;
        y = new_y;
    }

    // change the direction clockwise for the next move
    direction = (direction + 1) % 8;

    // increment time since last eat and breed counters
    time_since_last_eat++;
    time_since_last_breed++;

    moved = true;
}

void Doodlebug::breed() {
    if (time_since_last_breed < 10) {
        return;
    }

    // 50% chance to fail breeding
    if (rand() % 2 == 0) {
        // cout << "Doodlebug at (" << x << ", " << y << ") failed to breed.\n";
        time_since_last_breed = 0; // reset breeding counter even on failure
        return;
    }

    // check surrounding cells for empty space to breed
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int new_x = x + dx;
            int new_y = y + dy;

            if (new_x >= 0 && new_x < grid->get_width() && new_y >= 0 && new_y < grid->get_height()) {
                Cell* target_cell = grid->get_cell(new_x, new_y);
                if (target_cell->is_empty()) {
                    target_cell->set_critter(new Doodlebug(grid, new_x, new_y));
                    // cout << "Doodlebug at (" << x << ", " << y << ") bred a new doodlebug at (" << new_x << ", " << new_y << ").\n";
                    time_since_last_breed = 0;
                    return;
                }
            }
        }
    } // do nothing if there are no open cells
}

void Doodlebug::die() {
    if (time_since_last_eat >= 20) {
        grid->get_cell(x, y)->clear();
        // cout << "Doodlebug at (" << x << ", " << y << ") starved to death.\n";
        delete this;
    }
}

void Doodlebug::print() const {
    cout << 'X';
}
