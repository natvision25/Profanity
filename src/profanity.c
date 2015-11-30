#include <pebble.h>

/*
 ____  ____   ___  _____ _    _   _ ___ _______   __
|  _ \|  _ \ / _ \|  ___/ \  | \ | |_ _|_   _\ \ / /
| |_) | |_) | | | | |_ / _ \ |  \| || |  | |  \ V / 
|  __/|  _ <| |_| |  _/ ___ \| |\  || |  | |   | |  
|_|   |_| \_\\___/|_|/_/   \_\_| \_|___| |_|   |_|  
    Censored for sensitive audiences  ~~By Natvision
 
 Anyone can take, use, modify, and distribute 
  this watchface for free, as long as they don't
  take the credit. Enjoy :) 
  
  Also i'm 14 so don't expect sheer excellence*/
  
 
  
Window *window;
TextLayer *phrase_layer;
TextLayer *text_layer;
unsigned long timer = 0;

int unix; //variable to hold the unix time
int lasthour;
int lastminute;
int lastsecond;
int hour; //variable for the hours
int minute; //something to hold the minutes
int second; //cant forget the seconds :)

void update_time(); //Pre-define update_time so other functions don't freak out


static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(); //update the time
}

void update_time(){
  time_t temp = time(NULL);  //store the unix time in temp
  unix = temp; //unix is now temp
  lasthour = hour;
  lastminute = minute;
  lastsecond = second;
  
  //calculate the current time
  hour = unix/3600%12;
  minute = unix%3600/60;
  second = unix%60;
  
  
  static char buffer[64]; //here's the buffer for the time text

    if(hour == 0 && minute < 10)snprintf(buffer, 64, "Its 12:0%d!", minute); //combine the next two if statements
    else  if(hour == 0)snprintf(buffer, 64, "Its 12:%d!", minute); //display 12 instead of 0 when it's noon or midnight, so 12:16 won't be 0:16
    else  if(minute < 10)snprintf(buffer, 64, "Its %d:0%d!", hour, minute); //add a zero if the minute is less than 10. 4:6 would be wierd.
    else snprintf(buffer, 64, "Its %d:%d!", hour, minute); //just print the plain time if none of those happen.
  
  
  
    text_layer_set_text(text_layer, buffer); //update the text
}

void handle_init(void) {
	// Create a window and text layer
	window = window_create();

  window_set_background_color(window,GColorBlack);
  
	text_layer = text_layer_create(GRect(0, 85, 144, 34)); 
  phrase_layer = text_layer_create(GRect(0,50,144,34));
  
	// Set the text, font, and text alignment
  
  text_layer_set_background_color(phrase_layer, GColorBlack);
  text_layer_set_text_color(phrase_layer, GColorWhite);
  GFont spire = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_BLOCK_32));
	text_layer_set_font(phrase_layer, spire);
	text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
	text_layer_set_text(phrase_layer, "Oh $#*!"); //just in case it don't work :P
  
  text_layer_set_background_color(text_layer, GColorBlack);
  text_layer_set_text_color(text_layer, GColorWhite);
	text_layer_set_text(text_layer, "Error!"); //just in case it don't work :P
	text_layer_set_font(text_layer, spire);
	text_layer_set_text_alignment(text_layer, GTextAlignmentRight);
	
	
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer)); // Add the text layer to the window
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(phrase_layer)); // Add the text layer to the window

  
	window_stack_push(window, true); //push the window
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler); // make sure it shows the right time all the time
	update_time(); //make sure the time is shown from the start
}

void handle_deinit(void) {
	// Destroy the layers
	text_layer_destroy(text_layer);
  	text_layer_destroy(phrase_layer);
	
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
