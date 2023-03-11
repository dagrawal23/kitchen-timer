/*
 * kitchen_timer.c
 *
 *  Created on: Jun 18, 2021
 *      Author: Devansh Agrawal, James Hunt
 */

#include "kitchen_timer.h"

static int led0 = 0; //int to display on led 0
static int led1 = 0; //int to display on led 1
static int led2 = 0; //int to display on led 2
static int led3 = 0; //int to display on led 3
static int led0bk = 0; //bkup of int to display on led 0
static int led1bk = 0; //bkup of int to display on led 1
static int led2bk = 0; //bkup of int to display on led 2
static int led3bk = 0; //bkup of int to display on led 3
static bool hourButton = false; //boolean to check if hours or minutes are being set
static uint8_t buttons; //stores the lastest state of buttons
static bool countDown = false; //true if in countdown mode, false otherwise
uint32_t seconds = 0; //seconds elapsed in countdown mode
static bool done = false; //true if timer over, false otherwise

/******************************************************************************
 * Make sure you examine the functions that are made available to you in
 * the provided_code directory.  There are already functions provided that
 * configure timers for 1 second and 2mS.  The ISRs for these timers are
 * also provided.
 *
 * You should also make use of the functions you completed in display.c and
 * cap_sense.c
 *
 * You can add as many helper functions are you like to this file.
 *
 * DO NOT try to code all of this at once.  Break this into smaller steps.
 *
 *      -> Write  a small amount of code to accomplish a simple requirement.
 *      -> Verify your new code works.
 *      -> Verify that you did not break any of your earlier code.
 *      -> Continue to the next requirement.
 *
 * Use the debugger to verify your code!
 *
 * Suggested Development Strategy
 *
 * 1. Detect when the user presses one of the Cap Sense Buttons
 * 2. Determine which button has been pressed
 * 3. Print out a number to a single seven segment digit
 * 4. Print out a 4-digit number to the display (see video on POV)
 * 5. Blink the 4-digit number on/off at a rate of 1 second
 * 6. Modify the 4-digit number displayed using the Cap Sense Buttons
 * 6. Count down to 00:00
 * 7. Toggle the eyes/buzzer
 * 8. Complete remaining requirements.
 *****************************************************************************/
/**
 * helper function to decrement the hours/minutes on the leds
 */
void decrement()
{
    //for hour leds
    if (hourButton)
    {
        if (led3 == 0 && led2 == 0)
        {
            led3 = 9;
            led2 = 9;
        }
        else if (led2 == 0)
        {
            led2 = 9;
            led3--;
        }
        else
        {
            led2--;
        }

    }

    //for minute leds
    else
    {
        if (led1 == 0 && led0 == 0)
        {
            led0 = 9;
            led1 = 5;
        }
        else if (led0 == 0)
        {
            led0 = 9;
            led1--;
        }
        else
        {
            led0--;
        }

    }
}
/**
 * helper function to increment the hours/minutes on the leds
 */
void increment()
{
    //for hour leds
    if (hourButton)
    {
        if (led3 == 9 && led2 == 9)
        {
            led3 = 0;
            led2 = 0;
        }
        else if (led2 == 9)
        {
            led2 = 0;
            led3++;
        }
        else
        {
            led2++;
        }

    }
    //for minute leds
    else
    {
        if (led1 == 5 && led0 == 9)
        {
            led0 = 0;
            led1 = 0;
        }
        else if (led0 == 9)
        {
            led0 = 0;
            led1++;
        }
        else
        {
            led0++;
        }

    }
}
/**
 * helper function to get latest button state and check what button is pressed. button state is only read when interrupt is generated
 */
void checkButton()
{
    if (ALERT_BUTTON_PRESSED == true)
    {
        ALERT_BUTTON_PRESSED = false;
        buttons = cap_sense_get_buttons();
        buttons &= (0x0F);
        if (countDown == false)
        {
            if (buttons == 1)
                hourButton = false; //minute are being set
            if (buttons == 2)
                hourButton = true; //hours are being set
            if (buttons == 4)
                decrement(); //decrement the corresponding led
            if (buttons == 8)
                increment(); //increment the corresponding led
            if (buttons == 3) //m+h has been pressed
            {
                //begin countdown mode
                countDown = true;

                //backup led current values before countdown starts
                led0bk = led0;
                led1bk = led1;
                led2bk = led2;
                led3bk = led3;
            }

        }

    }
}
/**
 * helper function to display leds using persistence of vision (2ms delay)
 */
void display_helper()
{

    display_all_dig_off();
    display_digit(0, led0);
    ALERT_2_MILLISECOND = false;
    //wait 2 ms
    while (1)
    {
        if (ALERT_2_MILLISECOND == true)
        {
            checkButton();
            ALERT_2_MILLISECOND = false;
            break;
        }
    }
    //switch led being displayed
    display_all_dig_off();

    display_digit(1, led1);
    //wait 2 ms
    while (1)
    {
        if (ALERT_2_MILLISECOND == true)
        {
            ALERT_2_MILLISECOND = false;
            break;
        }
    }
    //switch led being displayed
    display_all_dig_off();

    display_digit(2, led2);
    //wait 2 ms
    while (1)
    {
        if (ALERT_2_MILLISECOND == true)
        {
            ALERT_2_MILLISECOND = false;
            break;
        }
    }
    //switch led being displayed
    display_all_dig_off();
    display_digit(3, led3);
    //wait 2 ms
    while (1)
    {
        if (ALERT_2_MILLISECOND == true)
        {
            ALERT_2_MILLISECOND = false;
            break;
        }
    }

    display_all_dig_off();

}
/*****************************************************
 * Allows the user to set the duration of the timer
 *****************************************************/
void kitchen_timer_mode_init(void)
{
    if (countDown == false) //only run if timer not counting down
    {
        //display for one sec
        ALERT_1_SECOND = false;
        while (ALERT_1_SECOND == false)
        {
            display_helper();
        }
        ;
        ALERT_1_SECOND = false;
        display_all_dig_off();
        //turn of for one sec
        while (ALERT_1_SECOND == false)
        {
            checkButton();
        };
    }

}
// ADD CODE

/*****************************************************
 * Starts the timer
 *****************************************************/
void kitchen_timer_mode_count_down(void)
{
    if (countDown == true) //only run if timer counting down
    {

        //if timer not over
        if (done == false)
        {
            ALERT_1_SECOND = false;
            while (ALERT_1_SECOND == false)
            {
                if (ALERT_BUTTON_PRESSED == true)
                {
                    ALERT_BUTTON_PRESSED = false;
                    buttons = cap_sense_get_buttons();
                    buttons &= (0x0F);

                    if (buttons == 3) // m+h is pressed, restore leds to backup values and return to initialisation mode
                    {
                        countDown = false;
                        led0 = led0bk;
                        led1 = led1bk;
                        led2 = led2bk;
                        led3 = led3bk;
                        return;
                    }
                }
                display_helper();
            }
            seconds++;

            if (led3 == 0 && led2 == 0 && led0 == 0 && led1 == 0)
            {
                done = true;
            }
            //if not donwe and a minute has passed, decrement accordingly
            else if (done != true && (seconds % 60 == 0))
            {
                if (led2 == 0 && led1 == 0 && led0 == 0)
                {
                    led2 = 9;
                    led1 = 5;
                    led0 = 9;
                    led3--;
                }
                else if (led1 == 0 && led0 == 0)
                {
                    led1 = 5;
                    led0 = 9;
                    led2--;

                }
                else if (led0 == 0)
                {
                    led0 = 9;
                    led1--;
                }
                else
                {
                    led0--;
                }
                seconds = 0;
            }
        }
//if timer is over
        else
        {
            ALERT_1_SECOND = false;
            //buzzer and eyes on for 1 sec
            buzzer_on();
            display_eye_left(true);
            display_eye_right(true);
            while (ALERT_1_SECOND == false)
            {
                if (ALERT_BUTTON_PRESSED == true)
                {
                    ALERT_BUTTON_PRESSED = false;
                    buttons = cap_sense_get_buttons();
                    buttons &= (0x0F);

                    if (buttons == 3) // m+h is pressed, restore leds to backup values and return to initialisation mode
                    {
                        countDown = false;
                        done = false;
                        led0 = led0bk;
                        led1 = led1bk;
                        led2 = led2bk;
                        led3 = led3bk;
                        ALERT_1_SECOND = false;
                        //turn of buzzer and eye leds before going back to initialisation mode
                        buzzer_off();
                        display_eye_left(false);
                        display_eye_right(false);
                        return;
                    }

                }
                display_helper();
            }
            ALERT_1_SECOND = false;
            //buzzer and eyes off for one second
            buzzer_off();
            display_eye_left(false);
            display_eye_right(false);
            while (ALERT_1_SECOND == false)
            {
                display_helper();
            }
        }

    }
}

