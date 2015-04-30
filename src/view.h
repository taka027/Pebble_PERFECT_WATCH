#include <pebble.h>
void show_main_layout(void);
void hide_main_layout(void);
extern TextLayer *s_footer;
extern TextLayer *s_header;
extern TextLayer *s_top;
extern TextLayer *s_right;
extern TextLayer *s_left;
extern Layer *g_canvas_layer;
typedef struct {
  int hour12;
  int hours;
  int minutes;
  int seconds;
} Time;
extern Time ti;
void render_hand_sec(Layer *layer, GContext *ctx, Time ti) ;
void render_hand_min(Layer *layer, GContext *ctx, Time ti) ;
void render_hand_hour(Layer *layer, GContext *ctx, Time ti) ;