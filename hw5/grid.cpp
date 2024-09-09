#include "grid.hpp"
#include "cell.hpp"
#include "doodlebug.hpp"
#include "ant.hpp"
#include <iostream>
#include <vector> 

using namespace std;

Grid::Grid(int width, int height) {
    this->width = width;
    this->height = height;
    cells = vector<std::vector<Cell*>>(width, vector<Cell*>(height, nullptr));

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            cells[x][y] = new Cell(x, y);
        }
    }
}

Grid::~Grid() {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            delete cells[x][y];
        }
    }
}

void Grid::update() {
    // mark all critters as not moved
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Critter* critter = cells[x][y]->get_critter();
            if (critter) {
                critter->set_moved(false);
            }
        }
    }

    // move doodlebugs
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Critter* critter = cells[x][y]->get_critter();
            if (critter && dynamic_cast<Doodlebug*>(critter) && !critter->has_moved()) {
                critter->move();
            }
        }
    }

    // doodlebugs breed
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Critter* critter = cells[x][y]->get_critter();
            if (critter && dynamic_cast<Doodlebug*>(critter)) {
                critter->breed();
            }
        }
    }

    // doodlebugs die
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Critter* critter = cells[x][y]->get_critter();
            if (critter && dynamic_cast<Doodlebug*>(critter)) {
                critter->die();
            }
        }
    }

    // move ants
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Critter* critter = cells[x][y]->get_critter();
            if (critter && dynamic_cast<Ant*>(critter) && !critter->has_moved()) {
                critter->move();
            }
        }
    }

    // ants breed
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Critter* critter = cells[x][y]->get_critter();
            if (critter && dynamic_cast<Ant*>(critter)) {
                critter->breed();
            }
        }
    }

    // ants die
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Critter* critter = cells[x][y]->get_critter();
            if (critter && dynamic_cast<Ant*>(critter)) {
                critter->die();
            }
        }
    }
}

void Grid::print(int time_step) const {
    // print out the time step
    cout << "Time step: " << time_step << endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Critter* critter = cells[x][y]->get_critter();
            if (critter) {
                critter->print();
            } else {
                cout << '-';
            }
            cout << ' ';
        }
        cout << endl;
    }
}

Cell* Grid::get_cell(int x, int y) {
    return cells[x][y];
}

void Grid::set_cell(int x, int y, Cell* cell) {
    cells[x][y] = cell;
}

int Grid::get_width() const {
    return width;
}

int Grid::get_height() const {
    return height;
}
