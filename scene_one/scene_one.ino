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
  firefly1 = random(30) + 15;
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
  update(j);
  strip.show();

  if(j_direction == 1){
    if(j > 80) j_direction = 0;
    else j += 4;
  } else {
    if(j < 2) j_direction = 1;
    j -= 4;
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

  
  delay(190);
}

void updateEyes(int16_t j){

  // right eye
  strip.setPixelColor(0, strip.Color(255, 255, 255);
  strip.setPixelColor(1, strip.Color(255, 255, 255);
  strip.setPixelColor(2, strip.Color(255, 255, 255);
  strip.setPixelColor(3, strip.Color(255, 255, 255);
  strip.setPixelColor(4, strip.Color(255, 255, 255);

  // left eye
  strip.setPixelColor(10, strip.Color(255, 255, 255);
  strip.setPixelColor(11, strip.Color(255, 255, 255);
  strip.setPixelColor(12, strip.Color(255, 255, 255);
  strip.setPixelColor(13, strip.Color(255, 255, 255);
  strip.setPixelColor(14, strip.Color(255, 255, 255);

}

void updateHead(int16_t j){
  for(i=EYES_END; i< BODY_STARTS; i++) {
    if(i % 3 == 0) {
      strip.setPixelColor(i, strip.Color(90 + j, 25+j, 5));    }
    if(i % 3 == 1) {
      strip.setPixelColor(i, strip.Color(120 + j, 50+j, 0));
    }
    if(i % 3 == 2) {
      strip.setPixelColor(i, strip.Color(140 + j, 0, 0));    }
    
    if(i % 28 == 0) {
      //if ((i + firefly_offset) > strip.numPixels()) random_jump++;
      //else 
      strip.setPixelColor(i + firefly_offset, strip.Color(30-j, 80, 30));
    }
    
  }
}

void update(int16_t j) {
  uint16_t i;

  for(i=BODY_STARTS; i< strip.numPixels(); i++) {
    if((i == firefly1) || (i == firefly2) || (i == firefly3)){
      strip.setPixelColor(i + firefly_offset, strip.Color(30-j, 80, 30));
    }
    if(i % 2 == 0) {
      strip.setPixelColor(i, strip.Color(90 + j, 0, 170 + j));
    }
    else {
      strip.setPixelColor(i, strip.Color(40+j, 0, 150+j));
    }
    
  }
}
