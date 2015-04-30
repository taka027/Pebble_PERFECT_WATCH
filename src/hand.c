#include <pebble.h>
#include "view.h"

static int32_t sec_hand_length = 63;
static int32_t min_hand_length = 60;
static int32_t hour_hand_length = 44;
static int32_t hand_tail_length = 3;


void render_hand_hour(Layer *layer, GContext *ctx, Time ti) {
  static GPath *ptr;
  int32_t angle_p = (int32_t)TRIG_MAX_ANGLE * ((ti.hour12*60+ti.minutes)/12-15) / 60 -610;
  int32_t angle_n = (int32_t)TRIG_MAX_ANGLE * ((ti.hour12*60+ti.minutes)/12-15) / 60 +610;
  int32_t angle_p_t = (int32_t)TRIG_MAX_ANGLE * ((ti.hour12*60+ti.minutes)/12-15-15) / 60;
  int32_t angle_n_t = (int32_t)TRIG_MAX_ANGLE * ((ti.hour12*60+ti.minutes)/12-15-15-30) / 60;
  GPathInfo info = {.num_points=4,
                    .points=(GPoint[]){
    {(hour_hand_length)*cos_lookup(angle_p)/TRIG_MAX_RATIO+144/2,(hour_hand_length)*sin_lookup(angle_p)/TRIG_MAX_RATIO+168/2},
    {(hour_hand_length)*cos_lookup(angle_n)/TRIG_MAX_RATIO+144/2,(hour_hand_length)*sin_lookup(angle_n)/TRIG_MAX_RATIO+168/2},
    {(hand_tail_length)*cos_lookup(angle_n_t)/TRIG_MAX_RATIO+144/2,(hand_tail_length)*sin_lookup(angle_n_t)/TRIG_MAX_RATIO+168/2},
    {(hand_tail_length)*cos_lookup(angle_p_t)/TRIG_MAX_RATIO+144/2,(hand_tail_length)*sin_lookup(angle_p_t)/TRIG_MAX_RATIO+168/2}
                      }};
  ptr = gpath_create(&info);
  graphics_context_set_fill_color(ctx, GColorWhite);
  gpath_draw_filled(ctx,ptr);
  gpath_destroy(ptr);
}
void render_hand_min(Layer *layer, GContext *ctx, Time ti) {
  static GPath *ptr;
  int32_t angle_p = (int32_t)TRIG_MAX_ANGLE * (ti.minutes-15) / 60 -320;
  int32_t angle_n = (int32_t)TRIG_MAX_ANGLE * (ti.minutes-15) / 60 +320;
  int32_t angle_p_t = (int32_t)TRIG_MAX_ANGLE * (ti.minutes-15-15) / 60 ;
  int32_t angle_n_t = (int32_t)TRIG_MAX_ANGLE * (ti.minutes-15-15-30) / 60 ;
  GPathInfo info = {.num_points=4,
                    .points=(GPoint[]){
    {(min_hand_length)*cos_lookup(angle_p)/TRIG_MAX_RATIO+144/2,(min_hand_length)*sin_lookup(angle_p)/TRIG_MAX_RATIO+168/2},
    {(min_hand_length)*cos_lookup(angle_n)/TRIG_MAX_RATIO+144/2,(min_hand_length)*sin_lookup(angle_n)/TRIG_MAX_RATIO+168/2},
    {(hand_tail_length)*cos_lookup(angle_n_t)/TRIG_MAX_RATIO+144/2,(hand_tail_length)*sin_lookup(angle_n_t)/TRIG_MAX_RATIO+168/2},
    {(hand_tail_length)*cos_lookup(angle_p_t)/TRIG_MAX_RATIO+144/2,(hand_tail_length)*sin_lookup(angle_p_t)/TRIG_MAX_RATIO+168/2}
                      }};
  ptr = gpath_create(&info);
  graphics_context_set_fill_color(ctx, GColorWhite);
  gpath_draw_filled(ctx,ptr);
  gpath_destroy(ptr);
}
void render_hand_sec(Layer *layer, GContext *ctx, Time ti) {
  int32_t angle_p = (int32_t)TRIG_MAX_ANGLE * (ti.seconds-15) / 60 ;
  int32_t angle_n = (int32_t)TRIG_MAX_ANGLE * (ti.seconds-15) / 60 ;
  GPoint center = (GPoint) {
    .x = 144/2,
    .y = 168/2
  };
  GPoint hour_hand = (GPoint) {
    .x = (sec_hand_length)*cos_lookup(angle_p)/TRIG_MAX_RATIO+144/2,
    .y = (sec_hand_length)*sin_lookup(angle_p)/TRIG_MAX_RATIO+168/2,
  };
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_draw_line(ctx, center, hour_hand);
  //GPath *ptr;
  //int32_t angle_p = (int32_t)TRIG_MAX_ANGLE * (ti.seconds-15) / 60 -150;
  //int32_t angle_n = (int32_t)TRIG_MAX_ANGLE * (ti.seconds-15) / 60 +150;
  //int32_t angle_p_t = (int32_t)TRIG_MAX_ANGLE * (ti.seconds-15-15) / 60 ;
  //int32_t angle_n_t = (int32_t)TRIG_MAX_ANGLE * (ti.seconds-15-15-30) / 60 ;
  //GPathInfo info = {.num_points=4,
  //                  .points=(GPoint[]){
  //  {(sec_hand_length)*cos_lookup(angle_p)/TRIG_MAX_RATIO+144/2,(sec_hand_length)*sin_lookup(angle_p)/TRIG_MAX_RATIO+168/2},
  //  {(sec_hand_length)*cos_lookup(angle_n)/TRIG_MAX_RATIO+144/2,(sec_hand_length)*sin_lookup(angle_n)/TRIG_MAX_RATIO+168/2},
  //  {(hand_tail_length)*cos_lookup(angle_n_t)/TRIG_MAX_RATIO+144/2,(hand_tail_length)*sin_lookup(angle_n_t)/TRIG_MAX_RATIO+168/2},
  //  {(hand_tail_length)*cos_lookup(angle_p_t)/TRIG_MAX_RATIO+144/2,(hand_tail_length)*sin_lookup(angle_p_t)/TRIG_MAX_RATIO+168/2}
  //                    }};
  //ptr = gpath_create(&info);
  //graphics_context_set_fill_color(ctx, GColorWhite);
  //gpath_draw_filled(ctx,ptr);
 // gpath_destroy(ptr);
}
