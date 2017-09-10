#include <Adafruit_NeoPixel.h>

#define NEO_PIN 0   //Neopixels conected to pin
#define NEO_NUM 16  //Number of neopixels
#define POT_PIN 1   //Pot connected to analog pin 1, Trinket pin #2

//RGBW Neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEO_NUM, NEO_PIN, NEO_RGBW + NEO_KHZ800);

int potVal = 0;
int potNew = 0;
int potDelta = 0;
int red, green, blue, white;

void setup()
{
    #ifdef LED_BUILTIN
      // Turn the onboard LED off by making the voltage LOW
      pinMode(LED_BUILTIN, OUTPUT); 
      digitalWrite(LED_BUILTIN, LOW);
    #endif

    
    strip.begin(); //Initialize the strip
    strip.show(); //Set all pixels to 'off'
}

// Main program
void loop()
{
    potNew = analogRead(POT_PIN);
    potDelta = abs(potVal - potNew);

    if (potDelta >= 1){
      potVal = potNew;  

      switch(potVal){
        case 0 ... 255: // Lowest quarter of the potentiometer's range (0-255)
        
          potVal = map(potVal, 0, 255, 0, 255);  // Normalize to 0-255
          white = 256 - potVal; // From full to off
          red = potVal;     // Red from off to full
          green = 1;        // Green from off to full
          blue = 1;       // Blue off
          
          break;
        case 256 ... 511: // Second quarter of potentiometer's range (256-511)
        
          potVal = map(potVal, 256, 511, 0, 255);  // Normalize to 0-255
          white = 1;      // White off
          red = 256 - potVal; // Red from full to off
          green = potVal;   // Green from off to full
          blue = 1;     // Blue off
          
          break; 
        case 512 ... 767: // Third quarter of potentiometer"s range (512-767)
        
          potVal = map(potVal, 512, 767, 0, 255); // Normalize to 0-255
          white = 1;        // White from off to full
          red = 1;        // Red from off to full
          green = 256 - potVal; // Green from full to off
          blue = potVal;      // Blue from off to full
          
          break;
        default:
        
          potVal = map(potVal, 767, 1023, 0, 255);  // Highest quarter of potentiometer"s range (512-767)
          white = potVal;     // White from off to full
          red = 1;        // Red from off to full
          green = 1;        // Green off
          blue = 256 - potVal;  // Blue full to off
          
          break;
      }

      //Write values to strip
      for( int i = 0; i < NEO_NUM; i++){
          strip.setPixelColor(i, red, green, blue, white);
      }

      //Show color in neopixel
      strip.show();
    }
}
