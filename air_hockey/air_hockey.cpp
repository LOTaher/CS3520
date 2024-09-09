/* air_hockey.cpp --- 
 * 
 * Filename: air_hockey.cpp
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
#include "key.hpp"
#include "ball.hpp"
#include "air_hockey.hpp"
#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>


// Main Game function
void air_hockey(){
    int zone_height, zone_width;
    struct timespec tim = {0,200000000};
    struct timespec tim_ret;
    int arrow, c;
    int slider_x_speed = 5, slider_y_speed = 5;
    initscr();
    getmaxyx(stdscr,zone_height, zone_width);
    zone_height-=1;
    zone_width-=1;
    zone_t *z = init_zone(0, 0, zone_width, zone_height);
    ball_t *b = init_ball(zone_width/2, zone_height/2, 1, 1);
    slider_t *top = init_slider(zone_width/2, 5, 'T');
    slider_t *bottom = init_slider(zone_width/2, zone_height-5, 'U');
    draw_zone(z);
    draw_slider(top);
    draw_slider(bottom);
    draw_ball(b);
    refresh();
    nodelay(stdscr,TRUE);  // Do not wait for characters using getch.  
    noecho();
  while(1) {
       // Move the current piece 
    if ((arrow = read_escape(&c)) != NOCHAR) {
        switch (arrow) {

          // Functionality for Left Arrow Key that controls the bottom slider
          case LEFT:
            mvprintw(1, 5,"L");
            break;
          // Functionality for Rigth Arrow Key that controls the bottom slider
          case RIGHT:
            mvprintw(1, 5,"R");
            break;
          // Functionality for A Key that controls the top slider
          case A:
            mvprintw(1, 5,"A"); 
            break; 
          case D:
          // Functionality for D Key that controls the top slider
            mvprintw(1, 5,"D");
            break;
          default:
            mvprintw(1, 5,"%c", c);
            break;

        }
      } 
    refresh();
    undraw_zone(z);
    draw_zone(z);
    undraw_ball(b);
    moveBall(b);
    checkCollisionSlider(bottom, b);
    checkCollisionSlider(top, b);
    checkCollisionWithZone(b, z);
    draw_ball(b);
    refresh();
    // usleep(200000);
    nanosleep(&tim, &tim_ret);
  }

    
}
