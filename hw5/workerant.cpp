#include "workerant.hpp"
#include "grid.hpp"
#include <iostream>

using namespace std;

WorkerAnt::WorkerAnt(Grid *grid, int x, int y) : Ant(grid, x, y) {}

void WorkerAnt::print() const { cout << 'w'; }
