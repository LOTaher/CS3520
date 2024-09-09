#ifndef CRITTER_HPP
#define CRITTER_HPP

class Grid;

/**
 * @class Critter
 * @brief Abstract base class representing a critter in the simulation.
 * 
 * The Critter class defines the common interface and behavior for all critters in the simulation.
 * It includes pure virtual methods for movement, breeding, dying, and printing, which must be 
 * implemented by derived classes.
 */
class Critter {
public:
    /**
     * @brief Constructs a Critter object.
     * 
     * @param grid Pointer to the grid in which the critter resides.
     * @param x The x-coordinate of the critter's position.
     * @param y The y-coordinate of the critter's position.
     */
    Critter(Grid* grid, int x, int y);

    /**
     * @brief Pure virtual method to move the critter.
     */
    virtual void move() = 0;

    /**
     * @brief Pure virtual method to breed the critter.
     */
    virtual void breed() = 0;

    /**
     * @brief Pure virtual method to handle the critter's death.
     */
    virtual void die() = 0;

    /**
     * @brief Pure virtual method to print the critter.
     */
    virtual void print() const = 0;

    /**
     * @brief Virtual destructor for the Critter class.
     */
    virtual ~Critter() {}

    /**
     * @brief Checks if the critter has moved.
     * 
     * @return True if the critter has moved, false otherwise.
     */
    bool has_moved() const;

    /**
     * @brief Sets the moved status of the critter.
     * 
     * @param moved The moved status to set.
     */
    void set_moved(bool moved);

protected:
    Grid* grid; ///< Pointer to the grid in which the critter resides.
    int x; ///< The x-coordinate of the critter's position.
    int y; ///< The y-coordinate of the critter's position.
    bool moved; ///< Indicates whether the critter has moved in the current time step.
};

#endif // CRITTER_HPP
