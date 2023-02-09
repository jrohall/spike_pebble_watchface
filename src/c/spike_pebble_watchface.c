#include <pebble.h>

Window *window;
GBitmap *icon_bitmap;
BitmapLayer *icon_layer;
//Layer *date_layer;
TextLayer *clock_text_layer, *day_text_layer, *date_text_layer, *mon_text_layer, *quote_text_layer, *slash;

char date_buffer[4], day_buffer[6], mon_buffer[4];
char buffer[] = "00:00";

// Tick handler is set to run every minute, this is how we will change the time
// MUST BE DECLARED BEFORE IT IS FIRST CALLED I.E. BEFORE WINDOW_LOAD
void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  //Here we will update the watchface display
  //Format the buffer string using tick_time as the time source
  strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
 
  //Change the TextLayer clock_text_layer to show the updated time
  text_layer_set_text(clock_text_layer, buffer);
}

void days_tick_handler(struct tm *tii, TimeUnits units_changed){
  //Here we will be updating the watchface date display
  //Changing the TextLayer day text to show the updated day
  strftime(day_buffer, sizeof(day_buffer), "%a", tii);
  text_layer_set_text(day_text_layer, day_buffer);

  //Updating the TextLayer date_text_layer text to show the updated day of month
  strftime(date_buffer, sizeof(date_buffer), "%d", tii);
  text_layer_set_text(date_text_layer, date_buffer);

  //Updating the TextLayer mon_text_layer to show the updated month
  strftime(mon_buffer, sizeof(mon_buffer), "%m", tii);
  text_layer_set_text(mon_text_layer, mon_buffer);
}

/*
void mon_tick_handler(struct tm *tii, TimeUnits units_changed){
  //Here we will be updating the watchface date display
  //Changing the TextLayer mon_text_layer to show the updated month
  strftime(mon_buffer, sizeof(mon_buffer), "%m", tii);
  text_layer_set_text(mon_text_layer, mon_buffer);

}
*/

void window_load(Window *window){
  //Load bitmaps into GBitmap structures
  //The ID you chose when uploading is prefixed with 'RESOURCE_ID_'
  icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_SPIKE_CHALK);
   
  //Create BitmapLayers to show GBitmaps and add to Window
  //Pebble time round is 180 x 180 pixels
  icon_layer = bitmap_layer_create(GRect(0, 0, 180, 180));
  bitmap_layer_set_bitmap(icon_layer, icon_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(icon_layer));

  //Setting the clock TextLayer
  clock_text_layer = text_layer_create(GRect(0, 120, 180, 180));
  text_layer_set_background_color(clock_text_layer, GColorBlack);
  text_layer_set_text_color(clock_text_layer, GColorWhite);
  text_layer_set_text_alignment(clock_text_layer, GTextAlignmentCenter);
  text_layer_set_font(clock_text_layer, fonts_get_system_font(FONT_KEY_LECO_28_LIGHT_NUMBERS));
   
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(clock_text_layer));

  //Setting the Layer date_layer
  //date_layer = layer_create(layer_get_bounds(window_get_root_layer(window)));
  //layer_set_update_proc(date_layer, date_update_proc);
  //layer_add_child(window_get_root_layer(window), date_layer);

  //Setting the quote TextLayer
  quote_text_layer = text_layer_create(GRect(0, 105, 180, 180));
  text_layer_set_background_color(quote_text_layer, GColorClear);
  text_layer_set_text_color(quote_text_layer, GColorYellow);
  text_layer_set_text_alignment(quote_text_layer, GTextAlignmentCenter);
  text_layer_set_font(quote_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(quote_text_layer, "Whatever happens, happens.");

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(quote_text_layer));

  
  //Setting the day TextLayer
  day_text_layer = text_layer_create(GRect(60, 145, 180, 180));
  text_layer_set_text(day_text_layer, day_buffer);
  text_layer_set_background_color(day_text_layer, GColorClear);
  //text_layer_set_text_alignment(day_text_layer, GTextAlignmentCenter);
  text_layer_set_text_color(day_text_layer, GColorWhite);
  text_layer_set_font(day_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(day_text_layer)); 

  
  //Setting the date (number) TextLayer
  date_text_layer = text_layer_create(GRect(105, 145, 180, 180));
  text_layer_set_text(date_text_layer, date_buffer);
  text_layer_set_background_color(date_text_layer, GColorClear);
  //text_layer_set_text_alignment(date_text_layer, GTextAlignmentCenter);
  text_layer_set_text_color(date_text_layer, GColorWhite);
  text_layer_set_font(date_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(date_text_layer));

  
  //Setting the month TextLayer
  mon_text_layer = text_layer_create(GRect(85, 145, 180, 180));
  text_layer_set_text(mon_text_layer, mon_buffer);
  text_layer_set_background_color(mon_text_layer, GColorClear);
  text_layer_set_text_color(mon_text_layer, GColorWhite);
  text_layer_set_font(mon_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(mon_text_layer));

  //Setting the slash in the middle of the date (i know it is likely inefficient)
  slash = text_layer_create(GRect(98, 145, 180, 180));
  text_layer_set_text(slash, "/");
  text_layer_set_background_color(slash, GColorClear);
  text_layer_set_text_color(slash, GColorWhite);
  text_layer_set_font(slash, fonts_get_system_font(FONT_KEY_GOTHIC_18));

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(slash));
  
  
  //Minute Clock Time
  struct tm *t;
  time_t temp;
  temp = time(NULL);
  t = localtime(&temp);
   
  //Manually call the tick handler when the window is loading
  tick_handler(t, MINUTE_UNIT);
  days_tick_handler(t, DAY_UNIT);
  //mon_tick_handler(t, MONTH_UNIT);

   
}
 
void window_unload(Window *window){
  //Destroy GBitmap
  gbitmap_destroy(icon_bitmap);
   
  //Destroy BitmapLayer
  bitmap_layer_destroy(icon_layer);

  //Destroy TextLayers
  text_layer_destroy(clock_text_layer);
  text_layer_destroy(quote_text_layer);
  text_layer_destroy(day_text_layer);
  text_layer_destroy(mon_text_layer);
  text_layer_destroy(date_text_layer);

  //Destroy Layers
  //layer_destroy(date_layer);

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

  //initialize the day and month buffers
  day_buffer[0] = '\0';
  date_buffer[0] = '\0';
  mon_buffer[0] = '\0';

  //register the tick function
  tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);
  tick_timer_service_subscribe(DAY_UNIT, (TickHandler) days_tick_handler);
  //tick_timer_service_subscribe(MONTH_UNIT, (TickHandler) mon_tick_handler);
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