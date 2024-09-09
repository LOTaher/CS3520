/* key.hpp --- 
 * 
 * Filename: key.hpp
 * Description: 
 * Author: Adeel Bhutta
 * Maintainer: 
 * Created: Thu Sep 15 16:36:21 2016
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2016  Adeel Bhutta
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

#include <cstdbool>

/* Code: */
enum {NOCHAR, REGCHAR, UP, DOWN, LEFT, RIGHT, BADESC, W, A, S, D}; 

int read_escape(int *);

/* key.hpp ends here */
