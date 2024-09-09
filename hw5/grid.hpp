#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include "cell.hpp"

using namespace std;

/**
 * @class Grid
 * @brief Represents the grid in which the simulation takes place.
 * 
 * The Grid class manages the 2D grid of cells where critters live and interact.
 */
class Grid {
public:
    /**
     * @brief Constructs a Grid object with specified dimensions.
     * 
     * @param width The width of the grid.
     * @param height The height of the grid.
     */
    Grid(int width, int height);

    /**
     * @brief Destroys the Grid object, cleaning up allocated memory.
     */
    ~Grid();

    /**
     * @brief Updates the state of the grid.
     * 
     * This method updates all cells in the grid according to the simulation rules.
     */
    void update();

    /**
     * @brief Prints the current state of the grid.
     * 
     * @param time_step The current time step of the simulation.
     */
    void print(int time_step) const;

    /**
     * @brief Gets the cell at the specified coordinates.
     * 
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @return A pointer to the cell at the specified coordinates.
     */
    Cell* get_cell(int x, int y);

    /**
     * @brief Sets the cell at the specified coordinates.
     * 
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @param cell A pointer to the cell to set at the specified coordinates.
     */
    void set_cell(int x, int y, Cell* cell);

    /**
     * @brief Gets the width of the grid.
     * 
     * @return The width of the grid.
     */
    int get_width() const;

    /**
     * @brief Gets the height of the grid.
     * 
     * @return The height of the grid.
     */
    int get_height() const;

private:
    vector<vector<Cell*>> cells; ///< 2D vector of pointers to cells in the grid.
    int width; ///< The width of the grid.
    int height; ///< The height of the grid.
};

#endif // GRID_HPP
