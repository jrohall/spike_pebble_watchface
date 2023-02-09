#include <pebble.h>

Window *window;
GBitmap *icon_bitmap;
BitmapLayer *icon_layer;
//InverterLayer *inverted_layer;
TextLayer *clock_text_layer;
char buffer[] = "00:00";

// Tick handler is set to run every minute, this is how we will change the time
// MUST BE DECLARED BEFORE IT IS FIRST CALLED I.E. BEFORE WINDOW_LOAD
void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
  //Here we will update the watchface display
  //Format the buffer string using tick_time as the time source
  strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
 
  //Change the TextLayer text to show the new time!
  text_layer_set_text(clock_text_layer, buffer);
}

void window_load(Window *window){
  //Load bitmaps into GBitmap structures
  //The ID you chose when uploading is prefixed with 'RESOURCE_ID_'
  icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_SPIKE_CHALK);
   
  //Create BitmapLayers to show GBitmaps and add to Window
  //Sample images are 127 x 129 pixels
  icon_layer = bitmap_layer_create(GRect(0, 0, 180, 180));
  bitmap_layer_set_bitmap(icon_layer, icon_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(icon_layer));

  //Setting the TextLayer
  clock_text_layer = text_layer_create(GRect(0, 120, 180, 180));
  text_layer_set_background_color(clock_text_layer, GColorBlack);
  text_layer_set_text_color(clock_text_layer, GColorWhite);
  text_layer_set_text_alignment(clock_text_layer, GTextAlignmentCenter);
  text_layer_set_font(clock_text_layer, fonts_get_system_font(FONT_KEY_LECO_28_LIGHT_NUMBERS));
   
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(clock_text_layer));
  //text_layer_set_text(clock_text_layer, "Whatever happens, happens.");

  /*Inverted layer, applied after layer you want inverted
  inverted_layer = inverter_layer_create(GRect(0, 50, 180, 180));
  layer_add_child(window_get_root_layer(window), (Layer*) inverted_layer);
  */

  struct tm *t;
  time_t temp;
  temp = time(NULL);
  t = localtime(&temp);
   
  //Manually call the tick handler when the window is loading
  tick_handler(t, MINUTE_UNIT);
   
}
 
void window_unload(Window *window){
  //Destroy GBitmap
  gbitmap_destroy(icon_bitmap);
   
  //Destroy BitmapLayer
  bitmap_layer_destroy(icon_layer);

  //Destroy TextLayer
  text_layer_destroy(clock_text_layer);

  //Destroy InvertedLayer
  //inverter_layer_destroy(inverted_layer);

}
 
void init()
{
  //Initialize the app elements here!
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  //window_set_window_handlers(window, (WindowHandlers) handlers);
  window_stack_push(window, true);

  //register the tick function
  tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);
}
 
void deinit()
{
  //De-initialize elements here to save memory!
  window_destroy(window);

  //De-init the watch timer when the user is not using it to save battery!
  tick_timer_service_unsubscribe();
}
 
int main(void)
{
  init();
  app_event_loop();
  deinit();
}