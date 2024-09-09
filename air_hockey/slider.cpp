/* slider.cpp --- 
 * 
 * Filename: slider.cpp
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
#include "slider.hpp"
#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>

// This intializes the properties of the slider
const slider_t slider_types[2] = {
    {
        "top",
        {{1,1,1,1}}, 
        0,
        0,
        '%',
        {0,0,0}
    },
    {
        "bottom",
        {{1,1,1,1}}, 
        0,
        0,
        '+',
        {0,0,0}
    },
};

// Changes the location of the slider
void moveSlider(slider_t *s, int x, int y) {
    
    s->upper_left_x = x;
    s->upper_left_y = y;
}

// Intializes the slider
slider_t *init_slider (int initial_x, int initial_y, char type) {
  slider_t *s = (slider *) malloc(sizeof(slider_t));
  if (type == 'T'){
      memcpy(s, &slider_types[0], sizeof(slider_t));
  }
  else
  {
      memcpy(s, &slider_types[1], sizeof(slider_t));
  }
  
  
  s->upper_left_x = initial_x;
  s->upper_left_y = initial_y;
  return(s);
}

// Renders the slider on the screen
void draw_slider(slider_t *s){
  int x,y;
  for (x=0;x<4;x++) {
    for (y=0;y<1;y++) {
      if (s->piece[y][x]) {
        mvprintw(s->upper_left_y+y,s->upper_left_x+x,"%c",s->draw_char);
      }
    }
  }

}

// Replaces the slider with blank spaces
void undraw_slider(slider_t *s){
  int x,y;
  for (x=0;x<4;x++) {
    for (y=0;y<1;y++) {
      if (s->piece[y][x]) {
        mvprintw(s->upper_left_y+y,s->upper_left_x+x," ",s->draw_char);
      }
    }
  }

}
