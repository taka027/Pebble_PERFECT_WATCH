#include <pebble.h>
#include "view.h"

static Window *s_window;
static GFont s_res_gothic_24;
static GFont s_res_gothic_14;
static GBitmap *background_image;
static BitmapLayer *background_image_container;
TextLayer *s_footer;
TextLayer *s_header;
TextLayer *s_top;
TextLayer *s_right;
TextLayer *s_left;

Layer *g_canvas_layer;
Time ti;
GPoint g_center;

void update_proc(Layer *layer, GContext *ctx) {
  //right
/*
  static GPath *g_right;
  GPathInfo RIGHT_PATH_INFO = {
  .num_points = 4,
  .points = (GPoint []) {{96, 80}, {96+27, 80}, {96+27, 80+20}, {96, 80+20}}
  };
  g_right = gpath_create(&RIGHT_PATH_INFO);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  gpath_draw_outline(ctx, g_right);
*/
  //left
/*
  static GPath *g_left;
  GPathInfo LEFT_PATH_INFO = {
  .num_points = 4,
  .points = (GPoint []) {{19, 80}, {19+27, 80}, {19+27, 80+20}, {19, 80+20}}
  };
  g_left = gpath_create(&LEFT_PATH_INFO);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  gpath_draw_outline(ctx, g_left);
*/

  //center
  GPoint center = (GPoint) {
    .x = 144/2,
    .y = 168/2
  };
  graphics_context_set_fill_color(ctx,GColorWhite);
  graphics_fill_circle(ctx, center, 3);

  render_hand_hour(layer,ctx,ti);
  render_hand_min(layer,ctx,ti);
  render_hand_sec(layer,ctx,ti);
}

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 1);

  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // background_image_container
  background_image = gbitmap_create_with_resource(RESOURCE_ID_WATCH_BG);
  background_image_container = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(background_image_container, background_image);
  bitmap_layer_set_compositing_mode(background_image_container,GCompOpAssignInverted);
  layer_add_child(window_get_root_layer(s_window), bitmap_layer_get_layer(background_image_container));

  // s_footer
  s_footer = text_layer_create(GRect(0, 112, 144, 20));
  text_layer_set_background_color(s_footer, GColorClear);
  text_layer_set_text_color(s_footer, GColorWhite);
  text_layer_set_text(s_footer, "");
  text_layer_set_text_alignment(s_footer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_footer);

  // s_header
  s_header = text_layer_create(GRect(0, 0, 144, 16));
  text_layer_set_background_color(s_header, GColorBlack);
  text_layer_set_text_color(s_header, GColorWhite);
  text_layer_set_text(s_header, "");
  text_layer_set_text_alignment(s_header, GTextAlignmentCenter);
  text_layer_set_font(s_header, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_header);

  // s_top
  s_top = text_layer_create(GRect(0, 34, 144, 35));
  text_layer_set_background_color(s_top, GColorClear);
  text_layer_set_text_color(s_top, GColorWhite);
  text_layer_set_text(s_top, "");
  text_layer_set_text_alignment(s_top, GTextAlignmentCenter);
  text_layer_set_font(s_top, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_top);

  // s_right
  s_right = text_layer_create(GRect(96, 80, 27, 25));
  text_layer_set_background_color(s_right, GColorBlack);//White);
  text_layer_set_text_color(s_right, GColorWhite);//Black);
  text_layer_set_text(s_right, "");
  text_layer_set_text_alignment(s_right, GTextAlignmentCenter);
  text_layer_set_font(s_right, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_right);

  // s_left
  s_left = text_layer_create(GRect(19, 80, 27, 25));
  text_layer_set_background_color(s_left, GColorBlack);
  text_layer_set_text_color(s_left, GColorWhite);
  text_layer_set_text(s_left, "");
  text_layer_set_text_alignment(s_left, GTextAlignmentCenter);
  text_layer_set_font(s_left, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_left);

  //clock hands
  Layer *window_layer = window_get_root_layer(s_window);
  GRect window_bounds = layer_get_bounds(window_layer);

  g_center = grect_center_point(&window_bounds);

  g_canvas_layer = layer_create(window_bounds);
  layer_set_update_proc(g_canvas_layer, update_proc);
  layer_add_child(window_layer, g_canvas_layer);

}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(background_image_container);
  gbitmap_destroy(background_image);
  text_layer_destroy(s_footer);
  text_layer_destroy(s_header);
  text_layer_destroy(s_top);
  text_layer_destroy(s_right);
  text_layer_destroy(s_left);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_main_layout(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main_layout(void) {
  window_stack_remove(s_window, true);
}
