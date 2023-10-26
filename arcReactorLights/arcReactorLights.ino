#include <FastLED.h>

#define LED_PIN     4
#define NUM_LEDS    93

CRGB leds[NUM_LEDS];

void setup() {

  // int whiteCenter[] = {84, 92}
  // int lightBlueRing[] = {72, 83}
  // int turquoiseRing[] = {56, 71}
  

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {

  int countableRings[] = {56,71,72,83,84,92};
  int darkBlue[] = {1,2,4,6,7,9,10,12,14,15,17,18,20,22,23,25,26,28,30,31,33,35,37,39,41,43,45,47,49,51,53,55};

  int i = 0;
  int j = 0;
  int k = 0;
  int size = sizeof(darkBlue)/sizeof(darkBlue[0]);

  for(i; i <3; i++){
    j = countableRings[i*2];
    Serial.println(i);
    for(j; j < countableRings[i*2+2]; j++){
      Serial.println(j);
      switch(i){
        case 0: leds[j] = CRGB(0,174,255); break;
        case 1: leds[j] = CRGB(23,127,178); break;
        case 2: leds[j] = CRGB(255,255,255); break;
        default: break;
      }
    }
  }

  for(k; k < size; k++){
    leds[darkBlue[k]] = CRGB(9,39,223);
  }

FastLED.show();

delay(4000);

while(1){
  FastLED.clear();
  FastLED.show();
}
  
}
