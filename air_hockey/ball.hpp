#include "zone.hpp"
#include "slider.hpp"

// ball_t holds all properties of the ball
typedef struct ball {
  int upper_left_x;
  int upper_left_y;
  int speed_x;
  int speed_y;
  char draw_char;
  char color[3];
} ball_t;

ball_t *init_ball(int upper_left_x, int upper_left_y, int speed_x, int speed_y);
void draw_ball(ball_t *b);
void undraw_ball(ball_t *b);
bool checkCollisionWithZone(ball_t *b, zone_t *z);
bool checkCollisionSlider(slider_t *s, ball_t *b);
void moveBall(ball_t *b);
