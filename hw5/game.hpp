#ifndef GAME_HPP
#define GAME_HPP

#include "grid.hpp"

/**
 * @class Game
 * @brief Represents the main simulation game.
 * 
 * The Game class manages the simulation, including initializing the grid, running the simulation,
 * and determining when the simulation is over.
 */
class Game {
public:
    /**
     * @brief Constructs a Game object.
     * 
     * @param width The width of the grid.
     * @param height The height of the grid.
     * @param num_doodlebugs The initial number of doodlebugs.
     * @param num_ants The initial number of ants.
     * @param num_queens The initial number of queens.
     * @param fast_forward If true, the simulation runs in fast-forward mode.
     */
    Game(int width, int height, int num_doodlebugs, int num_ants, int num_queens, bool fast_forward);

    /**
     * @brief Runs the simulation.
     * 
     * This method starts the simulation and continues running it until a stopping condition is met.
     */
    void run();

private:
    /**
     * @brief Initializes the grid with the specified number of doodlebugs, ants, and queens.
     * 
     * @param num_doodlebugs The number of doodlebugs to initialize.
     * @param num_ants The number of ants to initialize.
     * @param num_queens The number of queens to initialize.
     */
    void init_grid(int num_doodlebugs, int num_ants, int num_queens);

    /**
     * @brief Checks if the simulation is over.
     * 
     * @return True if the simulation is over, false otherwise.
     */
    bool is_simulation_over();

    Grid grid; ///< The grid on which the simulation runs.
    int time_step; ///< The current time step of the simulation.
    bool fast_forward; ///< Indicates whether the simulation runs in fast-forward mode.
};

#endif // GAME_HPP
