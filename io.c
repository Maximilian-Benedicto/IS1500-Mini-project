extern void enable_interrupt();


// Global variables

int time_out_count = 0; // Counter to track timer timeouts

void init_io()
{
    enable_interrupt();

    volatile int *sw_pointer = (volatile int *)0x04000010; // Address for switch input
    *(sw_pointer + 2) = 0x3FF; // Set the enable IRQ bit at position 0 to enable interrupts from button #0
    *(sw_pointer + 3) = 0x3FF; // Set the enable edge capture bit at position 0 to enable edge detection from button #0

    volatile int *btn_pointer = (volatile int *)0x040000d0;
    *(btn_pointer + 2) = 0x1; // Set the enable IRQ bit at position 0 to enable interrupts from button #0
    *(btn_pointer + 3) = 0x1; // Set the enable edge capture bit at position 0 to enable edge detection from button #0
}

/* Function to get the status of button 0 */
int get_btn()
{
    volatile int *btn_pointer = (volatile int *)0x040000d0;
    int btn_result = *btn_pointer & 0x1; // Mask to get the status of button 0
    return btn_result;                   // Return button state (1 if pressed, 0 otherwise)
}

void reset_io()
{
    volatile int *sw_pointer = (volatile int *)0x04000010; // Address for switch input
    *(sw_pointer + 3) = 0x3FF; // Set the enable edge capture bit at position 0 to enable edge detection from button #0

    volatile int *btn_pointer = (volatile int *)0x040000d0;
    *(btn_pointer + 3) = 0x1;
}

/* Function to get the status of the switches */
int get_sw()
{
    volatile int *sw_pointer = (volatile int *)0x04000010; // Address for switch input
    int sw_result = *sw_pointer & 0x3FF;                   // Mask the switch input (10 switches)
    return sw_result;                                      // Return the value of the switches
}

/* Function to update LEDs with a given mask */
void set_leds(int led_mask)
{
    volatile int *led_pointer = (volatile int *)0x04000000; // Address for LEDs
    led_mask = led_mask & 0x3FF;                            // Mask the LED input to the 10 least significant bits
    *led_pointer = led_mask;                                // Set the LEDs according to the mask
}

/* Function to convert a value (0-9) to its corresponding 7-segment display encoding */
int value_to_segdisplay(int value)
{
    switch (value)
    {
    case 0:
        return 0b11000000; // 7-segment encoding for digit '0'
    case 1:
        return 0b11111001; // 7-segment encoding for digit '1'
    case 2:
        return 0b10100100; // 7-segment encoding for digit '2'
    case 3:
        return 0b10110000; // 7-segment encoding for digit '3'
    case 4:
        return 0b10011001; // 7-segment encoding for digit '4'
    case 5:
        return 0b10010010; // 7-segment encoding for digit '5'
    case 6:
        return 0b10000010; // 7-segment encoding for digit '6'
    case 7:
        return 0b11111000; // 7-segment encoding for digit '7'
    case 8:
        return 0b10000000; // 7-segment encoding for digit '8'
    case 9:
        return 0b10011000; // 7-segment encoding for digit '9'
    default:
        return 0b11111111; // Return all segments on for invalid input
    }
}

/* Function to update a specific 7-segment display with a value */
void set_displays(int display_number, int value)
{
    volatile int *display_pointer = (volatile int *)0x04000050; // Base address for the first display

    int seg_value = value_to_segdisplay(value); // Convert value to 7-segment encoding

    // Update the corresponding display based on display_number
    switch (display_number)
    {
    case 0:
        *display_pointer = seg_value; // Set the first display
        break;
    case 1:
        display_pointer = (volatile int *)0x04000060; // Set second display
        *display_pointer = seg_value;
        break;
    case 2:
        display_pointer = (volatile int *)0x04000070; // Set third display
        *display_pointer = seg_value;
        break;
    case 3:
        display_pointer = (volatile int *)0x04000080; // Set fourth display
        *display_pointer = seg_value;
        break;
    case 4:
        display_pointer = (volatile int *)0x04000090; // Set fifth display
        *display_pointer = seg_value;
        break;
    case 5:
        display_pointer = (volatile int *)0x040000a0; // Set sixth display
        *display_pointer = seg_value;
        break;
    default:
        // Do nothing for invalid display number
        break;
    }
}

/* Function to start the timer */
void start_timer()
{
    volatile int *timer_pointer = (volatile int *)0x04000020;
    *timer_pointer = 0b1;                      // Clear the timeout bit
    *(timer_pointer + 2) = 0b1100011010111111; // Load lower 16 bits of timer
    *(timer_pointer + 3) = 0b101101;           // Load higher 16 bits of timer
    *(timer_pointer + 1) = 0b111;              // Start the timer and configure the timer to reset on overflow and generate interrupts
}

/* Function to check if the timer has timed out */
int get_timer_timeout()
{
    volatile int *timer_pointer = (volatile int *)0x04000020;
    return *timer_pointer & 0b1; // Return timeout status (1 if timed out)
}
