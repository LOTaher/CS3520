#include "game.hpp"
#include "doodlebug.hpp"
#include "ant.hpp"
#include "queenant.hpp"
#include "workerant.hpp"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

Game::Game(int width, int height, int num_doodlebugs, int num_ants, int num_queens, bool fast_forward)
    : grid(width, height), time_step(1), fast_forward(fast_forward) {
    init_grid(num_doodlebugs, num_ants, num_queens);
}

void Game::init_grid(int num_doodlebugs, int num_ants, int num_queens) {
    for (int i = 0; i < num_doodlebugs; ++i) {
        int x = rand() % grid.get_width();
        int y = rand() % grid.get_height();
        if (grid.get_cell(x, y)->get_critter() == nullptr) {
            grid.get_cell(x, y)->set_critter(new Doodlebug(&grid, x, y));
        } else {
            --i; 
        }
    }

    for (int i = 0; i < num_ants; ++i) {
        int x = rand() % grid.get_width();
        int y = rand() % grid.get_height();
        if (grid.get_cell(x, y)->get_critter() == nullptr) {
            grid.get_cell(x, y)->set_critter(new WorkerAnt(&grid, x, y));
        } else {
            --i; 
        }
    }

    for (int i = 0; i < num_ants; ++i) {
        int x = rand() % grid.get_width();
        int y = rand() % grid.get_height();
        if (grid.get_cell(x, y)->get_critter() == nullptr) {
            grid.get_cell(x, y)->set_critter(new Ant(&grid, x, y));
        } else {
            --i; 
        }
    }

    for (int i = 0; i < num_queens; ++i) {
        int x = rand() % grid.get_width();
        int y = rand() % grid.get_height();
        if (grid.get_cell(x, y)->get_critter() == nullptr) {
            bool is_cataglyphis = (rand() % 1000 < 5); // 0.5% chance to be a cataglyphis
            grid.get_cell(x, y)->set_critter(new QueenAnt(&grid, x, y, is_cataglyphis));
        } else {
            --i; 
        }
    }
}

bool Game::is_simulation_over() {
    // check if there are no more doodlebugs or no more ants
    bool no_doodlebugs = true;
    bool no_ants = true;

    // iterate through the grid and check for the presence of doodlebugs and ants
    for (int x = 0; x < grid.get_width(); ++x) {
        for (int y = 0; y < grid.get_height(); ++y) {
            Critter* critter = grid.get_cell(x, y)->get_critter();
            if (critter) {
                if (dynamic_cast<Doodlebug*>(critter)) {
                    no_doodlebugs = false;
                }
                if (dynamic_cast<Ant*>(critter)) {
                    no_ants = false;
                }
                // if both species are present, do not exit until the user does
                if (!no_doodlebugs && !no_ants) {
                    return false;
                }
            }
        }
    }

    // if either species is completely gone, the simulation is over
    if (no_doodlebugs) {
        cout << "All doodlebugs are dead. Game over. Ended in " << (time_step - 1) << " time steps." << endl;
    }
    if (no_ants) {
        cout << "All ants are dead. Game over. Ended in " << (time_step - 1) << " time steps." << endl;
    }
    return no_doodlebugs || no_ants;
}

void Game::run() {
    while (!is_simulation_over()) {
        grid.update();
        grid.print(time_step);
        ++time_step;

        if (!fast_forward) {
            // this sleeps the program every second to slow down the simulation
            this_thread::sleep_for(chrono::seconds(1));
        }

        if (time_step == 5000) {
            cout << "Cycle detected. The simulation would last forever. Exiting." << endl;
            return;
        }
    }
}
