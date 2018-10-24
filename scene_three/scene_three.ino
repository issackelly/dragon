#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_RGB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


int16_t firefly1 = 0;
int16_t firefly2 = 0;
int16_t firefly3 = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  // Which position for the fireflies who got eaten?
  firefly1 = random(30) + 25;
  firefly2 = random(50) + 50;
  firefly3 = random(50) + 50;

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

int16_t j = 0, j_direction = 0;
uint16_t firefly_offset = 0;
long random_jump;

const int16_t EYES_START = 0;
const int16_t EYES_END = 15;
const int16_t BODY_STARTS = 25;

void loop() {

  updateEyes(j);
  updateHead(j);
  update(j);
  strip.show();

  if(j_direction == 1){
    if(j > 80) j_direction = 0;
    else j += 1;
  } else {
    if(j < 2) j_direction = 1;
    j -= 1;
  }

  random_jump = random(10);
  if (random_jump == 1) {
    firefly1++;
    firefly2++;
    firefly3++;
    if (firefly1 > strip.numPixels()) firefly1 = EYES_END;
    if (firefly2 > strip.numPixels()) firefly2 = EYES_END;
    if (firefly3 > strip.numPixels()) firefly3 = EYES_END;
  }

  
  delay(20);
}

void updateEyes(int16_t j){

  if (j < 25 && j >= 0){
    for(uint8_t i=0; i < 5; i++) {
      strip.setPixelColor(i, strip.Color(45-j, 255-(j * 4), 55-j));
      strip.setPixelColor(i+9, strip.Color(45-j, 255-(j * 4), 55-j));
    } 
  }
  else {
    // right eye
    for(uint8_t i=0; i < 5; i++) {
      strip.setPixelColor(i, strip.Color(55, 255, 55));
      strip.setPixelColor(i+9, strip.Color(55, 255, 55));
    } 
  }
  
}

void updateHead(int16_t j){
  for(uint16_t i=EYES_END; i< BODY_STARTS; i++) {
    if((i == firefly1) || (i == firefly2) || (i == firefly3)){
      strip.setPixelColor(i + firefly_offset, strip.Color(30-j, 80, 30));
    }
    if(i % 4 == 0) {
      strip.setPixelColor(i, strip.Color(90 + j, 125+j, 5));    }
    if(i % 4 == 1) {
      strip.setPixelColor(i, strip.Color(120 + j, 50+j, 0));
    }
    if(i % 4 == 2) {
      strip.setPixelColor(i, strip.Color(25 + j, 0, 60 + j));    }
    if(i % 4 == 3) {
      strip.setPixelColor(i, strip.Color(20, 20, 25 + j));    }
    
  }
}

void update(int16_t j) {
  uint16_t i;

  for(i=BODY_STARTS; i< strip.numPixels(); i++) {
    if((i == firefly1) || (i == firefly2) || (i == firefly3)){
      strip.setPixelColor(i + firefly_offset, strip.Color(30-j, 80, 30));
    }
    if(i % 4 == 0) {
      strip.setPixelColor(i, strip.Color(90 + j, 125+j, 5));    }
    if(i % 4 == 1) {
      strip.setPixelColor(i, strip.Color(120 + j, 50+j, 0));
    }
    if(i % 4 == 2) {
      strip.setPixelColor(i, strip.Color(25 + j, 0, 60 + j));    }
    if(i % 4 == 3) {
      strip.setPixelColor(i, strip.Color(20, 20, 25 + j));    }
    
    
  }
}
