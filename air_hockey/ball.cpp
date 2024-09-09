/* ball.cpp --- 
 * 
 * Filename: ball.cpp
 * Description: 
 * Author: Adeel Bhutta 
 * Maintainer: 
 * Created: Wed May 15 2024
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Copyright (c) 2016 Adeel Bhutta
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
*/

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstdbool>
#include <ncurses.h>
#include "key.hpp"
#include "ball.hpp"

// Move the ball based on its speed
void moveBall(ball_t *b){
    b->upper_left_x += b->speed_x;
    b->upper_left_y += b->speed_y;
}


// Check if the ball collides with the slider.
// Change Y direction of the ball if it collides
bool checkCollisionSlider(slider_t *s, ball_t *b){
    int x_ball = b->upper_left_x;
    int y_ball = b->upper_left_y;
    int x, y;
    for (x=0;x<4;x++) {
        for (y=0;y<1;y++) {
           
            if (s->upper_left_y+y == y_ball && s->upper_left_x+x == x_ball){
                b->speed_y *= -1;
                return true;
            }
        }
    }
    return false;
}

// Check if the ball collides with the left walls of the zone.
// Change X direction of the ball if it collides
bool checkCollisionWithZone(ball_t *b, zone_t *z){
    
    if (b->upper_left_x<=z->upper_left_x || b->upper_left_x>=z->upper_left_x + z->width){
        b->speed_x *= -1;
        // b->speed_y *= -1;
        
        return true;
    }
    return false;
}


// Inititialize ball with its position and speed in the X & Y directions
ball_t *init_ball(int upper_left_x, int upper_left_y, int speed_x, int speed_y) {
    ball_t *b;
    b = (ball_t *) malloc(sizeof(ball_t));
    b->draw_char = 'O';
    b->upper_left_x = upper_left_x;
    b->upper_left_y = upper_left_y;
    b->color[0] = 0;
    b->color[1] = 0;
    b->color[2] = 0;
    b->speed_x = speed_x;
    b->speed_y = speed_y;
    // printf("%c", b->draw_char);
    return (b);
}



// Renders the ball on the screen
void draw_ball(ball_t *b){
    mvprintw(b->upper_left_y, b->upper_left_x,"%c",b->draw_char);
}

// Replaces the ball with blank space
void undraw_ball(ball_t *b){
    mvprintw(b->upper_left_y, b->upper_left_x," ",b->draw_char);
}
