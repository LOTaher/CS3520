#include "cell.hpp"

Cell::Cell(int x, int y) {
    this->x = x;
    this->y = y;
    critter = nullptr;
}

bool Cell::is_empty() const {
    return critter == nullptr;
}

void Cell::set_critter(Critter* critter) {
    this->critter = critter;
}

Critter* Cell::get_critter() const {
    return critter;
}

void Cell::clear() {
    critter = nullptr;
}

int Cell::get_x() const {
    return x;
}

int Cell::get_y() const {
    return y;
}
