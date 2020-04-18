#include <FastLED.h>
#include <IRremote.h>
#include <limits.h>

#define NUM_LEDS 50
#define LED_DATA_PIN 6
#define IR_RCV_PIN 11

enum led_modes {
  MOVE,
  CHASE
};

IRrecv irrecv(IR_RCV_PIN);
decode_results irresults;
CRGB leds[NUM_LEDS];
unsigned long ledInt = 1000;
unsigned long ledTime = 250;
unsigned long IRDebounceTime;
unsigned long irStoreVal;
unsigned long irIncVal;
int ledPos = 0;
int ledHue = 0;
led_modes ledmode = CHASE;
bool chaseDir = false;
bool posChange = false;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  FastLED.addLeds<WS2811, LED_DATA_PIN, BRG>(leds, NUM_LEDS);
  Serial.println("Ready!");
}

void loop() {
  if (irrecv.decode(&irresults)) {
    if (millis() > IRDebounceTime) {
      irIncVal = irresults.value;
      if (irIncVal < 0xFFFFFFFF) {
        irStoreVal = irIncVal;
      } else {
        irIncVal = irStoreVal;
      }
      Serial.print("IR: ");
      Serial.print(irIncVal, HEX);
      Serial.print(" : ");
      switch (irIncVal) {
        case 0xFFE01F:
          Serial.println("Mode Switch");
          if (ledmode == CHASE) {
            ledmode = MOVE;
          } else {
            ledmode = CHASE;
            ledInt = millis() + ledTime;
          }
          break;
        case 0xFF9867:
          Serial.print("Hue up - ");
          if (ledHue < 255) {
            ledHue++;
            posChange = true;
          }
          Serial.println(ledHue);
          break;
        case 0xFF8877:
          Serial.print("Hue down - ");
          if (ledHue > 0) {
            ledHue--;
            posChange = true;
          }
          Serial.println(ledHue);
          break;
        case 0xFFA05F:
          Serial.println("Chase faster");
          // 10ms increments, 100ms maximum speed.
          if (ledTime >= 100) {
            ledTime -= 10;
          }
          break;
        case 0xFF20DF:
          Serial.println("Chase slower");
          // 10ms increments, 10s minimum speed.
          if (ledTime <= 10000) {
            ledTime += 10;
          }
          break;
        case 0xFF708F:
          if ((ledmode == MOVE) && (ledPos > 0))  {
            Serial.print("Move back - ");
            ledPos--;
            posChange = true;
            Serial.println(ledPos);
          }
          break;
        case 0xFF30CF:
          if ((ledmode == MOVE) && (ledPos < (NUM_LEDS - 1)))  {
            Serial.print("Move forward - ");
            ledPos++;
            posChange = true;
            Serial.println(ledPos);
          }        
          break;
        default:
          Serial.println("Not coded.");
          break;
      }

      IRDebounceTime = millis() + 200;
    }

    irrecv.resume();
  }

  if (ledmode == CHASE) {
    if (millis() > ledInt) {
      if (ledPos >= (NUM_LEDS-1)) {
        chaseDir = true;
      } else if (ledPos <= 0) {
        chaseDir = false;
      }

      leds[ledPos] = CHSV(ledHue, 255, 255);
      FastLED.show();
      leds[ledPos] = CRGB::Black;

      if (chaseDir) {
        ledPos--;
      } else {
        ledPos++;
      }

      ledInt += ledTime;
      
    }
  } else if (ledmode == MOVE) {
    if (posChange) {
      leds[ledPos] = CHSV(ledHue, 255, 255);
      FastLED.show();
      leds[ledPos] = CRGB::Black;
      posChange = false;
    }
  }

  delay(40);
}
