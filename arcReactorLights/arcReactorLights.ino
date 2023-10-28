// Tristan Caetano.0gf
// So that it will look like the arc reactor in Iron Man 1

// Using FastLED library to program WS2812 lights
#include <FastLED.h>

// Setting Pins
#define LED_PIN 3
#define POT_PIN A0
#define NUM_LEDS 93
#define FRAMES_PER_SECOND 120

// Setting global variables
CRGB leds[NUM_LEDS];
bool done = true;
int potVal = 0;
uint8_t gHue = 0;

// Runs once
void setup() {
  
  // 3 second delay for the lights to readjust
  delay(3000); 

  // Assigning the LED array to the library
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  // Making sure the lights done refresh to quickly
  FastLED.setMaxRefreshRate(120);

  // Making sure the arc reactor light setup doesn't repeat
  done = false;

}

// Loops over and over
void loop() {

// Getting analog value from potentiometer
potVal = analogRead(POT_PIN);

// Changing light hue every 20 ms
EVERY_N_MILLISECONDS( 20 ) { gHue++; }

// Init potentiometer position will show the standard arc reactor design
if(potVal < 200){
  arcReactor();

// Second potentiometer position will show rainbow glitter design
}else if(potVal < 400 && potVal > 200){
  rainbowWithGlitter();

// Third potentiometer position will show the sinelon design
} else if(potVal < 600 && potVal > 400){
  sinelon();

// Fourth potentiometer position will show the BPM arc reactor design  
}else if(potVal < 800 && potVal > 600){
  bpm();

// Fifth potentiometer position will show the juggle design  
}else if(potVal < 1000 && potVal  > 800){
  juggle();

// Final potentiometer position will turn the lights off  
}else{
  clearLEDs();
}

}

// Creating the arc reactor design
void arcReactor(){

  // Checking to make sure the design isn't already set on the lights to prevent repeats
  if(!done){

    // Turning off all LEDs
    clearLEDs();
    
    // LED numbers for outer 2 dark blue lights
    int darkBlue[] = {1,2,4,6,7,9,10,12,14,15,17,18,20,22,23,25,26,28,30,31,33,35,37,39,41,43,45,47,49,51,53,55};

    // Setting initial number for the final 3 inner rings and middle LED
    int i = 56;

    // Value for initing through darkBlue array to grab all relevent lights
    int k = 0;

    // Getting the numerical size of the darkBlue array
    int size = sizeof(darkBlue)/sizeof(darkBlue[0]);

    // For loop that will set the colors for the inner 3 rings and middle LED
    for(i; i<93; i++){
      FastLED.delay(1000/FRAMES_PER_SECOND);

      // Third to last ring will be turquoise
      if(i < 72){
        leds[i] = CRGB(0,255,255);

      // Second to last ring will be light blue  
      }else if(i > 71 && i < 84){
        leds[i] = CRGB(50,150,255);

      // Last ring and middle LED will be white
      }else{
        leds[i] = CRGB(255,255,255);
      }
    }

    // All LEDs in darkBlue will be made dark blue
    for(k; k < size; k++){
      FastLED.delay(1000/FRAMES_PER_SECOND); 
        leds[darkBlue[k]] = CRGB(0,0,223);
    }

    // Showing LEDs
    FastLED.show();

    // Setting the boolean to true to prevent repeats
    done = true;
  }
  return;
}

// The following patterns are pulled from the example file from FastLED

// Rainbow pattern
void rainbow() 
{
  
  // FastLED's built-in rainbow generator
  FastLED.delay(1000/FRAMES_PER_SECOND);
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
  done = false;

}

// Adding glitter to rainbow pattern
void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

// Sinelon pattern
void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  FastLED.delay(1000/FRAMES_PER_SECOND); 
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

// BPM pattern
void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  FastLED.delay(1000/FRAMES_PER_SECOND); 
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

// Juggle pattern
void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  FastLED.delay(1000/FRAMES_PER_SECOND); 
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

// Method that turns off all LEDs
void clearLEDs(){
  int i = 0;
  for(i;i<93;i++){
    FastLED.delay(1000/FRAMES_PER_SECOND); 
      leds[i] = CRGB(0,0,0);
  }
}

