#include "critter.hpp"

Critter::Critter(Grid* grid, int x, int y) {
    this->grid = grid;
    this->x = x;
    this->y = y;
}

bool Critter::has_moved() const {
    return moved;
}

void Critter::set_moved(bool moved) {
    this->moved = moved;
}
