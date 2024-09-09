#ifndef ANT_HPP
#define ANT_HPP

#include "critter.hpp"

/**
 * @class Ant
 * @brief Represents an Ant in the simulation.
 * 
 * The Ant class inherits from the Critter class and represents an ant in the grid.
 * It implements the behavior specific to ants, such as movement, breeding, and dying.
 */
class Ant : public Critter {
public:
    /**
     * @brief Constructs an Ant object.
     * 
     * @param grid Pointer to the grid in which the ant resides.
     * @param x The x-coordinate of the ant's position.
     * @param y The y-coordinate of the ant's position.
     */
    Ant(Grid* grid, int x, int y);

    /**
     * @brief Defines the movement behavior of the ant.
     * 
     * The ant moves randomly to an adjacent cell if it is empty.
     */
    void move();

    /**
     * @brief Defines the breeding behavior of the ant.
     * 
     * The ant breeds after a certain number of time steps by creating a new ant in an adjacent empty cell.
     */
    void breed();

    /**
     * @brief Defines the dying behavior of the ant.
     * 
     * The ant dies if certain conditions are met, such as not moving for a specified number of time steps.
     */
    void die();

    /**
     * @brief Prints the representation of the ant.
     * 
     * This method is used to print the ant's symbol on the grid.
     */
    void print() const;

protected:
    int time_since_last_move; ///< Tracks the number of time steps since the ant last moved.
};

#endif // ANT_HPP
