#ifndef QUEENANT_HPP
#define QUEENANT_HPP

#include "ant.hpp"

/**
 * @class QueenAnt
 * @brief Represents a queen ant in the simulation.
 * 
 * The QueenAnt class handles the behavior specific to queen ants, such as mating, breeding, and founding colonies.
 */
class QueenAnt : public Ant {
public:
    /**
     * @brief Constructs a QueenAnt object.
     * 
     * @param grid A pointer to the grid where the queen ant resides.
     * @param x The x-coordinate of the queen ant's position.
     * @param y The y-coordinate of the queen ant's position.
     * @param is_cataglyphis A flag indicating if the queen ant can reproduce without mating (default is false).
     */
    QueenAnt(Grid* grid, int x, int y, bool is_cataglyphis = false);

    /**
     * @brief Moves the queen ant.
     * 
     * This method overrides the move method in the Ant class. The queen ant has specific movement rules based on mating and colony founding.
     */
    void move() override;

    /**
     * @brief Breeds new ants if conditions are met.
     * 
     * This method overrides the breed method in the Ant class. It handles the breeding logic specific to queen ants, including the creation of new ants.
     */
    void breed() override;

    /**
     * @brief Handles the death of the queen ant.
     * 
     * This method overrides the die method in the Ant class. It removes the queen ant from the grid if it hasn't bred in 90 time-steps.
     */
    void die() override;

    /**
     * @brief Prints the representation of the queen ant.
     * 
     * This method overrides the print method in the Ant class. It outputs the character representing the queen ant.
     */
    void print() const override;

private:
    int time_since_last_breed; ///< Tracks the time since the queen ant last bred.
    bool has_found_colony; ///< Indicates if the queen ant has founded a colony.
    bool has_mated; ///< Indicates if the queen ant has mated.
    bool is_cataglyphis; ///< Indicates if the queen ant can reproduce without mating.

    /**
     * @brief Checks if there is a male ant adjacent to the queen ant.
     * 
     * @return True if there is a male ant adjacent, false otherwise.
     */
    bool is_adjacent_to_male_ant() const;
};

#endif // QUEENANT_HPP
