#!/usr/bin/env python3
import time
from rpi_ws281x import *
import argparse

# LED strip configuration:
LED_COUNT      = 30     # Number of LED pixels.
LED_PIN        = 18     # GPIO pin connected to the pixels (18 uses PWM!).
LED_FREQ_HZ    = 800000 # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 10     # DMA channel to use for generating a signal (try 10)
LED_BRIGHTNESS = 65     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False  # True to invert the signal (when using NPN transistor level shift)
LED_CHANNEL    = 0      # set to '1' for GPIOs 13, 19, 41, 45 or 53

def displayBinary(strip, binary_string):
    """Display the binary string on the LED strip."""
    for i in range(strip.numPixels()):
        if i < len(binary_string):
            if binary_string[i] == '1':
                strip.setPixelColor(i, Color(255, 0, 0))  # Red color
            elif binary_string[i] == '0':
                strip.setPixelColor(i, Color(255, 255, 255))  # White color
            else:
                strip.setPixelColor(i, Color(0, 0, 0))  # Turn off the LED
        else:
            strip.setPixelColor(i, Color(0, 0, 0))  # Turn off the LED
    strip.show()

# Main program logic follows:
if __name__ == '__main__':
    # Process arguments
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', '--clear', action='store_true', help='clear the display on exit')
    args = parser.parse_args()

    # Create NeoPixel object with appropriate configuration.
    strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
    # Intialize the library (must be called once before other functions).
    strip.begin()

    print('Press Ctrl-C to quit.')
    if not args.clear:
        print('Use "-c" argument to clear LEDs on exit')

    try:
        while True:
            # Ask user to input a binary string
            binary_string = input('Enter a binary string: ')

            # Validate the input
            if all(c in '01' for c in binary_string) or binary_string == '':
                displayBinary(strip, binary_string)
            else:
                print('Invalid input. Please enter a binary string.')

    except KeyboardInterrupt:
        if args.clear:
            displayBinary(strip, '0' * LED_COUNT)  # Turn off all LEDs
