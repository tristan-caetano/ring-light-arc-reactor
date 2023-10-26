#include <FastLED.h>

#define LED_PIN 3
#define POT_PIN A0
#define NUM_LEDS 93
#define FRAMES_PER_SECOND 120

CRGB leds[NUM_LEDS];
bool done = true;
// bool isClear = true;
int potVal = 0;
uint8_t gHue = 0;
void setup() {

  // int whiteCenter[] = {84, 92}
  // int lightBlueRing[] = {72, 83}
  // int turquoiseRing[] = {56, 71}
  
  delay(3000); // 3 second delay for recovery
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxRefreshRate(120);

  done = false;

}

void loop() {

potVal = analogRead(POT_PIN);
EVERY_N_MILLISECONDS( 20 ) { gHue++; }

if(potVal < 500){
  
  arcReactor();
}else{
  rainbow();
}

// if(!isClear){
//   clearLEDs();
// }
}


void arcReactor(){
  if(!done){
  clearLEDs();
  // int countableRings[] = {56,71,72,83,84,92};
  int darkBlue[] = {1,2,4,6,7,9,10,12,14,15,17,18,20,22,23,25,26,28,30,31,33,35,37,39,41,43,45,47,49,51,53,55};
  int i = 56;
  int k = 0;
  int size = sizeof(darkBlue)/sizeof(darkBlue[0]);

  for(i; i<93; i++){
    FastLED.delay(1000/FRAMES_PER_SECOND);
    if(i < 72){
      leds[i] = CRGB(0,174,255);
    }else if(i > 71 && i < 84){
      leds[i] = CRGB(23,127,178);
    }else{
      //leds[i] = CRGB(255,255,255);
      leds[i] = CRGB(100,100,100);
    }
  }


  for(k; k < size; k++){
    FastLED.delay(1000/FRAMES_PER_SECOND); 
      leds[darkBlue[k]] = CRGB(9,39,223);
  }

  FastLED.show();
  done = true;
}
return;
}

void rainbow() 
{
  
  // FastLED's built-in rainbow generator
  FastLED.delay(1000/FRAMES_PER_SECOND);
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
  done = false;

}

void clearLEDs(){
  int i = 0;
  for(i;i<93;i++){
    FastLED.delay(1000/FRAMES_PER_SECOND); 
      leds[i] = CRGB(0,0,0);
  }
  // isClear = true;
}

