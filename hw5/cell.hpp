#ifndef CELL_HPP
#define CELL_HPP

#include "critter.hpp"

/**
 * @class Cell
 * @brief Represents a cell in the grid.
 * 
 * The Cell class manages the state and behavior of a single cell in the grid,
 * including storing a pointer to the critter occupying the cell and the cell's coordinates.
 */
class Cell {
public:
    /**
     * @brief Constructs a Cell object.
     * 
     * @param x The x-coordinate of the cell's position.
     * @param y The y-coordinate of the cell's position.
     */
    Cell(int x, int y);

    /**
     * @brief Checks if the cell is empty.
     * 
     * @return True if the cell is empty, false otherwise.
     */
    bool is_empty() const;

    /**
     * @brief Sets the critter occupying the cell.
     * 
     * @param critter Pointer to the critter to be placed in the cell.
     */
    void set_critter(Critter* critter);

    /**
     * @brief Gets the critter occupying the cell.
     * 
     * @return Pointer to the critter occupying the cell.
     */
    Critter* get_critter() const;

    /**
     * @brief Clears the cell by removing the critter.
     */
    void clear();

    /**
     * @brief Gets the x-coordinate of the cell's position.
     * 
     * @return The x-coordinate of the cell's position.
     */
    int get_x() const;

    /**
     * @brief Gets the y-coordinate of the cell's position.
     * 
     * @return The y-coordinate of the cell's position.
     */
    int get_y() const;

private:
    Critter* critter; ///< Pointer to the critter occupying the cell, or nullptr if the cell is empty.
    int x; ///< The x-coordinate of the cell's position.
    int y; ///< The y-coordinate of the cell's position.
};

#endif // CELL_HPP
