#include "queenant.hpp"
#include "workerant.hpp"
#include "ant.hpp"
#include "grid.hpp"
#include <iostream>

using namespace std;

QueenAnt::QueenAnt(Grid* grid, int x, int y, bool is_cataglyphis) : Ant(grid, x, y), is_cataglyphis(is_cataglyphis) {
    time_since_last_breed = 0;
    has_found_colony = false;
    has_mated = false;
}

void QueenAnt::move() {
    if (has_found_colony && !has_mated) {
        // don't move once the colony is found and if the queen hasn't mated again
        time_since_last_breed++;
        return;
    }

    if (has_mated) {
        // if the queen ant has mated but hasn't founded the colony, it doesn't move
        time_since_last_breed++;
        return;
    }

    // move like any other ant if the colony is not found and hasn't mated
    Ant::move();

    // check if adjacent to a male ant to mark mating
    if (is_adjacent_to_male_ant()) {
        has_mated = true;
        time_since_last_breed = 0; // Reset the breeding counter after mating
    } else {
        time_since_last_breed++;
    }
}

void QueenAnt::breed() {
    if (!has_mated || time_since_last_breed < 30) {
        // not ready to breed
        return;
    }

    // check the 16-neighborhood for empty cells to spawn new ants
    int spawned = 0;
    for (int dx = -2; dx <= 2 && spawned < 10; ++dx) {
        for (int dy = -2; dy <= 2 && spawned < 10; ++dy) {
            // skip the current cell
            if (dx == 0 && dy == 0) continue;

            int new_x = x + dx;
            int new_y = y + dy;

            // ensure the new cell is within bounds
            if (new_x >= 0 && new_x < grid->get_width() && new_y >= 0 && new_y < grid->get_height()) {
                Cell* target_cell = grid->get_cell(new_x, new_y);
                if (target_cell->is_empty()) {
                    // randomly decide to spawn a worker ant, male ant, or another queen ant
                    int random_value = rand() % 10000;

                    if (random_value < 5) {
                        // less than 0.05% chance to spawn a queen ant that can reproduce without mating (cataglyphis)
                        target_cell->set_critter(new QueenAnt(grid, new_x, new_y, true));
                    } else if (random_value < 100) {
                        // less than 1% chance to spawn a new queen ant
                        target_cell->set_critter(new QueenAnt(grid, new_x, new_y, false));
                    } else if (random_value < 4000) {
                        // 20-40% chance to spawn a male ant
                        target_cell->set_critter(new Ant(grid, new_x, new_y));
                    } else {
                        // 60-80% chance to spawn a worker ant
                        target_cell->set_critter(new WorkerAnt(grid, new_x, new_y));
                    }
                    spawned++;
                    // cout << "New ant spawned at (" << new_x << ", " << new_y << ")." << endl;
                }
            }
        }
    }

    if (spawned > 0) {
        has_found_colony = true;
        // cout << "Queen ant at (" << x << ", " << y << ") has founded the colony." << endl;
    }

    if (!is_cataglyphis) {
        // reset the breeding counter
        time_since_last_breed = 0;
        has_mated = false; // reset mating status
    }
}

void QueenAnt::die() {
    if (time_since_last_breed >= 90) {
        // remove the queen ant from the grid if it hasn't bred in 90 time-steps
        grid->get_cell(x, y)->clear();
        // cout << "Queen ant at (" << x << ", " << y << ") has died." << endl;
        delete this;
    }
}

void QueenAnt::print() const {
    cout << 'Q';
}

bool QueenAnt::is_adjacent_to_male_ant() const {
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

    for (int i = 0; i < 8; ++i) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (new_x >= 0 && new_x < grid->get_width() && new_y >= 0 && new_y < grid->get_height()) {
            Critter* critter = grid->get_cell(new_x, new_y)->get_critter();
            if (critter && dynamic_cast<Ant*>(critter)) {
                return true;
            }
        }
    }
    return false;
}
