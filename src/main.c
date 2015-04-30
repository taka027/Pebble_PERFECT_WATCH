#include <pebble.h>
#include "view.h"


static char date_text[]="2014/12/31";
static char time_text[]="23:59";
static char second_text[]="59";
static char weekday[10];

static void handle_tick(struct tm *tick_time, TimeUnits changed) {
  strftime(weekday, sizeof(weekday), "%a", tick_time);
  snprintf(date_text,sizeof(date_text),"%d/%02d/%02d"
           ,tick_time->tm_year+1900,tick_time->tm_mon+1,tick_time->tm_mday);
  snprintf(time_text,sizeof(time_text),"%02d:%02d"
           ,tick_time->tm_hour,tick_time->tm_min);
  snprintf(second_text,sizeof(second_text),"%02d"
           ,tick_time->tm_sec);

  text_layer_set_text(s_header, date_text);
  text_layer_set_text(s_top, time_text);
  text_layer_set_text(s_right, weekday);
  text_layer_set_text(s_left, second_text);


  layer_mark_dirty(g_canvas_layer);

  ti.hours = tick_time->tm_hour;
  ti.hour12 = tick_time->tm_hour;
  if (ti.hours >= 12) {
    ti.hour12 = tick_time->tm_hour-12;
  }
  ti.minutes = tick_time->tm_min;
  ti.seconds = tick_time->tm_sec;
}

void handle_init(void) {
  show_main_layout();

  tick_timer_service_subscribe(SECOND_UNIT, handle_tick);
}

void handle_deinit(void) {
  hide_main_layout();
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
