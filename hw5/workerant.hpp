#ifndef WORKERANT_HPP
#define WORKERANT_HPP

#include "ant.hpp"

/**
 * @class WorkerAnt
 * @brief Represents a worker ant in the simulation.
 * 
 * The WorkerAnt class handles the behavior specific to worker ants.
 */
class WorkerAnt : public Ant {
public:
    /**
     * @brief Constructs a WorkerAnt object.
     * 
     * @param grid A pointer to the grid where the worker ant resides.
     * @param x The x-coordinate of the worker ant's position.
     * @param y The y-coordinate of the worker ant's position.
     */
    WorkerAnt(Grid* grid, int x, int y);

    /**
     * @brief Prints the representation of the worker ant.
     * 
     * This method overrides the print method in the Ant class. It outputs the character representing the worker ant.
     */
    void print() const override;
};

#endif // WORKERANT_HPP
