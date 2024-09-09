// This structure holds the properties of the zone such as position and dimesions
typedef struct zone {
  int upper_left_x;
  int upper_left_y;
  int width;
  int height;
  char draw_char;
  char color[3];
} zone_t;


void undraw_zone(zone_t *z);
void draw_zone(zone_t *z);
zone_t *init_zone(int upper_left_x, int upper_left_y, int width, int height);