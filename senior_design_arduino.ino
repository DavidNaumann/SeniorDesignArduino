#include <FastLED.h>
#define LED_PIN 7
#define NUM_LEDS 3
#define NUM_STEPS 120000

boolean setDIR=LOW;
int driverPUL=9;
int driverDIR=8;
int lag = 100;

CRGB leds[NUM_LEDS];
int curr_led = 0;
int r = 0, g = 255, b = 0; // Global colors for LEDS

void setup() {

    Serial.begin(9600);
    // pin setup
    pinMode(driverPUL, OUTPUT);
    pinMode(driverDIR, OUTPUT);

    // Use 5V and grnd, pin out is 7
    FastLED.addLeds<WS2812, LED_PIN,GRB>(leds, NUM_LEDS);
    leds[0] = CRGB::Red;
    leds[1] = CRGB::Red;
    leds[2] = CRGB::Red;
    FastLED.show();
}

void openDrawer()
{
    setDIR=HIGH;

    for(long steps=0;steps< NUM_STEPS;steps++){
        digitalWrite(driverDIR, setDIR);
        digitalWrite(driverPUL, HIGH);
        delayMicroseconds(lag);
        digitalWrite(driverPUL, LOW);
        delayMicroseconds(lag);
    }
}


void closeDrawer()
{
    setDIR=LOW;

    for(long steps=0;steps< NUM_STEPS;steps++){
        digitalWrite(driverDIR, setDIR);
        digitalWrite(driverPUL, HIGH);
        delayMicroseconds(lag);
        digitalWrite(driverPUL, LOW);
        delayMicroseconds(lag);
    }

    Serial.print("done\n");
}

void setLED(int led, int state)
{
    //3.)Activate the appropriate LED
    if(led < NUM_LEDS && led >= 0)
    {
        if(state == 1)
        {
            leds[led]=CRGB::Blue;
        }
        else
        {
            leds[led]=CRGB::Red;
        }
    }
    FastLED.show(); //Show the active LED
}


void loop()
{
    //Steps:
    //1.)Wait for user input
    if(Serial.available()){
        //2.)Read the ID sent by the application
        String mode_str = Serial.readStringUntil('\n'); //LED number
        String led_str =Serial.readStringUntil('\n'); //LED number
        // drawer = Serial.readStringUntil('\n');
        int led = led_str.toInt();
        int mode = mode_str.toInt();

        //6.)Close the appropriate drawer
        //stepp.step(-NUM_ROTATIONS); //may be NUM_ROTATIONS*StepsPerRev

        if(mode == 0)
        {
            openDrawer();

            setLED(led,1);
        }
        else
        {
            setLED(led,0);
            closeDrawer();
        }

    }
    delay(10);

}
