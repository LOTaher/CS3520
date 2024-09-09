#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "critter.hpp"

/**
 * @class Doodlebug
 * @brief Represents a Doodlebug in the simulation.
 * 
 * The Doodlebug class defines the behavior and attributes specific to Doodlebugs,
 * including movement, breeding, and dying.
 */
class Doodlebug : public Critter {
public:
    /**
     * @brief Constructs a Doodlebug object.
     * 
     * @param grid Pointer to the grid in which the doodlebug resides.
     * @param x The x-coordinate of the doodlebug's position.
     * @param y The y-coordinate of the doodlebug's position.
     */
    Doodlebug(Grid* grid, int x, int y);

    /**
     * @brief Moves the doodlebug.
     * 
     * Doodlebugs move in a specific pattern and attempt to eat ants in adjacent cells.
     * If no ants are found, they move in their current direction, with special rules for
     * bouncing off the grid boundaries.
     */
    void move();

    /**
     * @brief Breeds the doodlebug.
     * 
     * If the doodlebug has survived for enough time steps, it attempts to breed by creating
     * a new doodlebug in an adjacent empty cell.
     */
    void breed();

    /**
     * @brief Handles the doodlebug's death.
     * 
     * If the doodlebug has not eaten in a certain number of time steps, it starves and dies.
     */
    void die();

    /**
     * @brief Prints the doodlebug.
     * 
     * Outputs a character representation of the doodlebug for display purposes.
     */
    void print() const;

private:
    int time_since_last_eat; ///< The number of time steps since the doodlebug last ate.
    int time_since_last_breed; ///< The number of time steps since the doodlebug last bred.
    int direction; ///< The current direction of movement for the doodlebug.
};

#endif // DOODLEBUG_HPP
