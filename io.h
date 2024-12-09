#ifndef IO_H
#define IO_H

void init_io();
int get_btn();                                    // Function to get button status
void reset_io();
int get_sw();                                     // Function to get switch status
int value_to_segdisplay(int value);               // Function to convert a value to 7-segment display encoding
void set_displays(int display_number, int value); // Update specific 7-segment display
void set_leds(int led_mask);                      // Update LEDs with a given mask
void start_timer();                               // Function to start the timer
int get_timer_timeout();                          // Function to check if the timer has timed out

#endif