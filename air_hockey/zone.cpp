/* zone.cpp --- 
 * 
 * Filename: zone.cpp
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
#include "zone.hpp"
#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>

// Initializes zone position and dimensions
zone_t *init_zone(int upper_left_x, int upper_left_y, int width, int height) {
  zone_t *z;
  z = (zone_t *) malloc(sizeof(zone_t));
  z->upper_left_x = upper_left_x + 10;    // added 10 to create some space on the left side of the zone to display messages
  z->upper_left_y = upper_left_y;
  z->width = width-10;
  z->height = height;
  z->draw_char = '#';
  z->color[0] = 0;
  z->color[1] = 0;
  z->color[2] = 0;
  return (z);
}


// Renders zone on the screen
void draw_zone(zone_t *z) {
  int row_counter, column_counter;

  // Draw the top side of the zone
  for (row_counter=z->upper_left_x;row_counter<=(z->upper_left_x + z->width);row_counter++) {
    mvprintw(z->upper_left_y,row_counter,"%c",z->draw_char);
  }


  // Draw left side of zone
  for (column_counter=z->upper_left_y;column_counter<=(z->upper_left_y + z->height);column_counter++) {
    mvprintw(column_counter,z->upper_left_x,"%c",z->draw_char);
  }

  // Draw right side of well
  for (column_counter=z->upper_left_y;column_counter<=(z->upper_left_y + z->height);column_counter++) {
    mvprintw(column_counter,(z->upper_left_x + z->width),"%c",z->draw_char);
  }
  
  // Draw Bottom of zone 
  for (row_counter=z->upper_left_x;row_counter<(z->upper_left_x + z->width);row_counter++) {
    // printf("%d\n", row_counter);
    // printf("%d\n", z->upper_left_y + z->height);
    mvprintw((z->upper_left_y + z->height),row_counter,"%c",z->draw_char);
    // printf("*****\n");
  }
}

// Replaces the zone boundary with blank spaces
void undraw_zone(zone_t *z) {
  int row_counter, column_counter;

  // Draw the top side of the zone
  for (row_counter=z->upper_left_x;row_counter<=(z->upper_left_x + z->width);row_counter++) {
    mvprintw(z->upper_left_y,row_counter," ",z->draw_char);
  }


  // Draw left side of zone
  for (column_counter=z->upper_left_y;column_counter<=(z->upper_left_y + z->height);column_counter++) {
    mvprintw(column_counter,z->upper_left_x," ",z->draw_char);
  }

  // Draw right side of well
  for (column_counter=z->upper_left_y;column_counter<=(z->upper_left_y + z->height);column_counter++) {
    mvprintw(column_counter,(z->upper_left_x + z->width)," ",z->draw_char);
  }
  
  // Draw Bottom of zone 
  for (row_counter=z->upper_left_x;row_counter<=(z->upper_left_x + z->width);row_counter++) {
    mvprintw(z->upper_left_y + z->height,row_counter," ",z->draw_char);
  }
}
