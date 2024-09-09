/* key.cpp --- 
 * 
 * Filename: key.cpp
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

/* Code: */
#include <ncurses.h> 
#include "key.hpp"

int read_escape(int *read_char) {
  int c; 
  if ((c = getch()) == ERR) {
    return (NOCHAR);
  }
  else if (c==0x1b) {
    if ((c = getch()) == '[') {
      c=getch();
      if (c == 'a')
        return (A);
      else if( c=='s')
        return (S);
      else if( c=='d')
        return (D);
      else if( c=='w')
        return (W);
      
      switch (c) {
        case 'A':
          return (UP);
          break;
        case 'B':
          return (DOWN);
          break;
        case 'C':
          return (RIGHT);
          break;
        case 'D':
          return (LEFT);
          break;
        default: 
          return (BADESC);
      }
    }
  }
  else {
    *read_char = c;
    switch(c){
      case 'a':
      case 'A': 
        return A;

      case 'w':
      case 'W': 
        return W;
        
      case 's':
      case 'S': 
        return S;
        
      case 'd':
      case 'D': 
        return D;
        
      default:
        return (REGCHAR);
    }
  }
  return (REGCHAR);
}

/* key.cpp ends here */
