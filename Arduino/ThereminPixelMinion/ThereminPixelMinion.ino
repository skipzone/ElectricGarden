/****************************************************************************
 *                                                                          *
 * Theremin Pixel Pattern Generator                                         *
 *                                                                          *
 * Created at JUMP (Jack's Urban Meeting Place) -- jumpboise.org            *
 *                                                                          *
 * Contributors(s):  Ross Butler, Justin Maier                              *
 *                                                                          *
 * January 2020                                                             *
 *                                                                          *
 * based on RF_mesh_TREES_receiver_side (Feb. 2019 version) by Jesse Cordtz *
 * and GardenSpinner (Dec. 2019 version) by Ross Butler                     *
 *                                                                          *
 ****************************************************************************/


// TODO:  get status led stuff from JohnsKaleidoscopeMirror


/***********
 * Options *
 ***********/

//#define ENABLE_DEBUG_PRINT
#define ENABLE_RADIO
#define ENABLE_WATCHDOG



/************
 * Includes *
 ************/

#include <avr/pgmspace.h>

#ifdef ENABLE_WATCHDOG
  #include <avr/wdt.h>
#endif

#include <FastLED.h>
#include <SPI.h>

#ifdef ENABLE_RADIO
#include "RF24.h"
#endif

#ifdef ENABLE_DEBUG_PRINT
  #include "printf.h"
#endif

#include "PixelPattern.h"
#include "pixelPatternFactory.h"



/******************************
 * Target Structure Selection *
 ******************************/

// Enable only one of these.
//#define TARGET_IS_OLD_TREE
#define TARGET_IS_NEW_TREE
//#define TARGET_IS_CLOUD
//#define TARGET_IS_LARGE_GIRAFFE_BODY
//#define TARGET_IS_SMALL_GIRAFFE_BODY
//#define TARGET_IS_LARGE_GIRAFFE_LEGS
//#define TARGET_IS_SMALL_GIRAFFE_LEGS
//#define TARGET_IS_ROSS_DEVL
//#define TARGET_IS_STRIP_TESTER



/*********************************************
 * Implementation and Behavior Configuration *
 *********************************************/

#define LAMP_TEST_PIN A0
#define RGB_LED_RED_PIN 3
#define RGB_LED_GREEN_PIN 5
#define RGB_LED_BLUE_PIN 6
#define SIMULATION_PIN A1 

// ---------- old trees ----------
#if defined(TARGET_IS_OLD_TREE)
  #define NUM_STRIPS 1
  #define MAX_SECTIONS_PER_STRIP 2
  constexpr uint8_t numSectionPixels[NUM_STRIPS][MAX_SECTIONS_PER_STRIP] = { {150, 50} };
  constexpr uint8_t overallBrightness = 200;
  constexpr uint32_t colorCorrection = 0xFFFF66;
// ---------- new trees ----------
#elif defined(TARGET_IS_NEW_TREE)
  #define NUM_STRIPS 2
  #define MAX_SECTIONS_PER_STRIP 1
  constexpr uint8_t numSectionPixels[NUM_STRIPS][MAX_SECTIONS_PER_STRIP] = { {150}, {50} };
  constexpr uint8_t overallBrightness = 255;
  constexpr uint32_t colorCorrection = 0xFFFF66;
// ---------- clouds ----------
#elif defined(TARGET_IS_CLOUD)
  #define NUM_STRIPS 1
  #define MAX_SECTIONS_PER_STRIP 1
  constexpr uint8_t numSectionPixels[NUM_STRIPS][MAX_SECTIONS_PER_STRIP] = { {255} };
  constexpr uint8_t overallBrightness = 255;
// ---------- large giraffe body ----------
#elif defined(TARGET_IS_LARGE_GIRAFFE_BODY)
  #define NUM_STRIPS 1
  #define MAX_SECTIONS_PER_STRIP 1
  constexpr uint8_t numSectionPixels[NUM_STRIPS][MAX_SECTIONS_PER_STRIP] = { {250} };
  constexpr uint8_t overallBrightness = 255;
  constexpr uint32_t colorCorrection = 0xFFFF66;
// ---------- small giraffe body ----------
#elif defined(TARGET_IS_SMALL_GIRAFFE_BODY)
  #define NUM_STRIPS 1
  #define MAX_SECTIONS_PER_STRIP 1
  constexpr uint8_t numSectionPixels[NUM_STRIPS][MAX_SECTIONS_PER_STRIP] = { {248} };
  constexpr uint8_t overallBrightness = 255;
  constexpr uint32_t colorCorrection = 0xFFFF66;
// ---------- large giraffe legs ----------
#elif defined(TARGET_IS_LARGE_GIRAFFE_LEGS)
  #define NUM_STRIPS 1
  #define MAX_SECTIONS_PER_STRIP 1
  constexpr uint8_t numSectionPixels[NUM_STRIPS][MAX_SECTIONS_PER_STRIP] = { {150} };
  constexpr uint8_t overallBrightness = 255;
  constexpr uint32_t colorCorrection = 0xFFFF66;
// ---------- small giraffe legs ----------
#elif defined(TARGET_IS_SMALL_GIRAFFE_LEGS)
  #define NUM_STRIPS 1
  #define MAX_SECTIONS_PER_STRIP 1
  constexpr uint8_t numSectionPixels[NUM_STRIPS][MAX_SECTIONS_PER_STRIP] = { {75} };
  constexpr uint8_t overallBrightness = 255;
  constexpr uint32_t colorCorrection = 0xFFFF66;
// ---------- strip tester ----------
#elif defined(TARGET_IS_STRIP_TESTER)
  #define NUM_STRIPS 1
  #define MAX_SECTIONS_PER_STRIP 1
  constexpr uint8_t numSectionPixels[NUM_STRIPS][MAX_SECTIONS_PER_STRIP] = { {150} };
  constexpr uint8_t overallBrightness = 255;
  constexpr uint32_t colorCorrection = 0xFFFF66;
// ---------- Ross's development board ----------
#elif defined(TARGET_IS_ROSS_DEVL)
  #define NUM_STRIPS 1
  #define MAX_SECTIONS_PER_STRIP 2
  constexpr uint8_t numSectionPixels[NUM_STRIPS][MAX_SECTIONS_PER_STRIP] = { {30, 66} };
  constexpr uint8_t overallBrightness = 48;
  constexpr uint32_t colorCorrection = 0xFFFF66;
#else
  #error No target defined.
#endif

#define STRIP_0_CHIPSET WS2812B
#define STRIP_0_COLOR_ORDER GRB
#define STRIP_0_PIN 2
#define STRIP_1_CHIPSET WS2812B
#define STRIP_1_COLOR_ORDER GRB
#define STRIP_1_PIN 4
#define STRIP_2_CHIPSET WS2812B
#define STRIP_2_COLOR_ORDER GRB
#define STRIP_2_PIN 7

#define LED_FRAMES_PER_SECOND 24
#define PATTERN_UPDATE_INTERVAL_MS 30

#define LAMP_TEST_ACTIVE LOW

// Use these for common-anode RGB LED.
//constexpr uint8_t rgbLedLowIntensity = 255;
//constexpr uint8_t rgbLedHighIntensity = 0;
// Use these for common-cathode RGB LED.
constexpr uint8_t rgbLedLowIntensity = 0;
constexpr uint8_t rgbLedHighIntensity = 255;

// The theremin collects and sends three distance measurements.
constexpr uint8_t numDistanceMeasmts = 3;

#define SIMULATION_ACTIVE LOW
constexpr uint8_t simulationPatternId = Rainbow::id;
// A simulated measurement is incremented or decremented once per interval.
// The intervals are measured in milliseconds.  With an interval of 1 ms,
// a 10-bit distance measurement will step up and down through its complete
// range in about 2 seconds.
constexpr uint32_t simulatedMeasmtUpdateIntervals[numDistanceMeasmts] = {2, 4, 6};

// distance measurement range that can be mapped into
// another range, such as 0-255 hue or intensity
// (also defines the range of simulated measurements)
constexpr int16_t minDistance[numDistanceMeasmts] = {0, 0, 0};
constexpr int16_t maxDistance[numDistanceMeasmts] = {1023, 1023, 1023};

// We need to receive at least newPatternRepetitionThreshold consecutive
// messages with the same new pattern number before we change the pattern.
// This should prevent unwanted flashing if a bad message is received.  (It
// isn't rare that a corrupt message makes it through the NRF24L01's CRC check.)
constexpr uint8_t newPatternRepetitionThreshold = 3;

// free memory that must remain after allocating pixel data arrays
constexpr uint16_t reservedRamSize = 128;

// for rejecting bad messages that make it past the CRC check
// (which happens with the NRF24L01+ way more than you'd think)
constexpr int16_t minValidPatternNum = 0;
constexpr int16_t maxValidPatternNum = 255;
constexpr int16_t minValidDistance = 0;
constexpr int16_t maxValidDistance = 4000;

constexpr uint8_t allOffPatternId = 255;
constexpr uint8_t testPatternIdRangeStart = 250;

// This is the list of patterns that can be selected and displayed.
// Test patterns must appear last.  The sequence of non-test patterns
// in this array should result in a dramatic change each time the
// pattern number is changed by one.
constexpr uint8_t patternIds[] = {
  Rainbow::id,
  MiddleOut::id,
  PlasmaBall::id,
  OutsideIn::id,
  Stripes::id,
  YellowGiraffe::id,
  // test patterns
  SectionLocator::id,
  StripTest::id
};
constexpr uint8_t numPatternIds = sizeof(patternIds) / sizeof(uint8_t);

#define USE_PATTERN_XREF
constexpr uint8_t selectedPatternIdIdx = 0;
constexpr uint8_t displayPatternIdIdx = 1;

// Always put a different pattern on the giraffes so that they stand out from the trees.
#if    defined(TARGET_IS_LARGE_GIRAFFE_BODY) \
    || defined(TARGET_IS_SMALL_GIRAFFE_BODY) \
    || defined(TARGET_IS_LARGE_GIRAFFE_LEGS) \
    || defined(TARGET_IS_SMALL_GIRAFFE_LEGS)
  constexpr uint8_t displayPatternIdXref[numPatternIds][2] = {
    {MiddleOut::id     , Rainbow::id       },
    {OutsideIn::id     , PlasmaBall::id    },
    {PlasmaBall::id    , Stripes::id       },
    {Rainbow::id       , OutsideIn::id     },
    {Stripes::id       , MiddleOut::id     },
    {YellowGiraffe::id , YellowGiraffe::id },
    // These are test patterns and should always be mapped to the same.
    {SectionLocator::id, SectionLocator::id},
    {StripTest::id     , StripTest::id     },
  };
#else
  // Everything that is not a giraffe does not do YellowGiraffe.
  constexpr uint8_t displayPatternIdXref[numPatternIds][2] = {
    {MiddleOut::id     , MiddleOut::id     },
    {OutsideIn::id     , OutsideIn::id     },
    {PlasmaBall::id    , PlasmaBall::id    },
    {Rainbow::id       , Rainbow::id       },
    {Stripes::id       , Stripes::id       },
    {YellowGiraffe::id , Rainbow::id       },
    // These are test patterns and should always be mapped to the same.
    {SectionLocator::id, SectionLocator::id},
    {StripTest::id     , StripTest::id     },
  };
#endif

// The defaut pattern is the active pattern upon startup and remains the active
// pattern until measurements with a different pattern id are received or simulated.
constexpr uint8_t defaultPatternId = Rainbow::id;



/***********************
 * Radio Configuration *
 ***********************/

// Possible data rates are RF24_250KBPS, RF24_1MBPS, or RF24_2MBPS (genuine Noric chips only).
#define DATA_RATE RF24_250KBPS

// Valid CRC length values are RF24_CRC_8, RF24_CRC_16, and RF24_CRC_DISABLED
#define CRC_LENGTH RF24_CRC_16

// nRF24 frequency range:  2400 to 2525 MHz (channels 0 to 125)
// ISM: 2400-2500;  ham: 2390-2450
// WiFi ch. centers: 1:2412, 2:2417, 3:2422, 4:2427, 5:2432, 6:2437, 7:2442,
//                   8:2447, 9:2452, 10:2457, 11:2462, 12:2467, 13:2472, 14:2484
// The Electric Garden theremin uses channel 80.  Illumicone uses channel 97.
#define RF_CHANNEL 80

// Nwdgt, where N indicates the pipe number (0-6) and payload type (0: stress test;
// 1: position & velocity; 2: measurement vector; 3,4: undefined; 5: custom
//constexpr uint8_t readPipeAddresses[][6] = {"0wdgt", "1wdgt", "2wdgt", "3wdgt", "4wdgt", "5wdgt"};
//constexpr int numReadPipes = sizeof(readPipeAddresses) / (sizeof(uint8_t) * 6);
// We only need measurement vector messages on 2wdgt.
constexpr uint8_t readPipeAddresses[][6] = {"2wdgt"};
constexpr int numReadPipes = sizeof(readPipeAddresses) / (sizeof(uint8_t) * 6);

// Probably no need to ever set auto acknowledgement to false because the sender
// can control whether or not acks are sent by using the NO_ACK bit.  However . . .
// There may be a problem where bad packets that make it through the CRC check have
// the NO_ACK bit reset, causing unintended acks that jam up the channel.  We'll
// turn off ACK_WIDGET_PACKETS in an attempt to avoid that possible problem.
#define ACK_WIDGET_PACKETS false

// RF24_PA_MIN = -18 dBm, RF24_PA_LOW = -12 dBm, RF24_PA_HIGH = -6 dBm, RF24_PA_MAX = 0 dBm
#define RF_POWER_LEVEL RF24_PA_MAX

// 250 us additional delay multiplier (0-15)
#define TX_RETRY_DELAY_MULTIPLIER 15

// max retries (0-15)
#define TX_MAX_RETRIES 15



/**********************************************************
 * Widget Packet Header and Payload Structure Definitions *
 **********************************************************/

union WidgetHeader {
  struct {
    uint8_t id       : 5;
    uint8_t channel  : 2;
    bool    isActive : 1;
  };
  uint8_t raw;
};

// pipe 0
struct StressTestPayload {
  WidgetHeader widgetHeader;
  uint32_t     payloadNum;
  uint32_t     numTxFailures;
};

// pipe 1
struct PositionVelocityPayload {
  WidgetHeader widgetHeader;
  int16_t      position;
  int16_t      velocity;
};

// pipe 2
struct MeasurementVectorPayload {
  WidgetHeader widgetHeader;
  int16_t      measurements[15];
};

// pipe 5
struct CustomPayload {
  WidgetHeader widgetHeader;
  uint8_t      buf[31];
};



/***********************
 * Types and Constants *
 ***********************/



/***********
 * Globals *
 ***********/

static uint8_t numPixels[NUM_STRIPS];
static CRGB* pixels[NUM_STRIPS];

static bool widgetIsActive;
static uint8_t activePatternId;
static int16_t currentDistance[numDistanceMeasmts];

static bool shiftForward = true;
static int16_t waveMeasmt[1];

#ifdef ENABLE_RADIO
static RF24 radio(9, 10);    // CE on pin 9, CSN on pin 10, also uses SPI bus (SCK on 13, MISO on 12, MOSI on 11)
#endif

static bool usingSimulatedMeasmts;

static PixelPattern* patternObjects[numPatternIds][NUM_STRIPS][MAX_SECTIONS_PER_STRIP];



/***********
 * Helpers *
 ***********/

uint16_t freeRam() 
{
  // Based on code retrieved on 1 April 2015 from
  // https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory

  extern int __heap_start, *__brkval; 
  int v; 
  return (uint16_t) &v - (__brkval == 0 ? (uint16_t) &__heap_start : (uint16_t) __brkval); 
}



/*********************
 * Pattern Rendering *
 *********************/

uint8_t convertThereminPatternNumberToPatternId(uint8_t patternNum)
{
  static uint8_t patternIdxModulus;

  if (patternIdxModulus == 0) {
    // The modulus is the number of non-test patterns in patternIds.
    // Note that the test patterns must appear last in patternIds.
    for (patternIdxModulus = 0;
         patternIdxModulus < numPatternIds && patternIds[patternIdxModulus] < testPatternIdRangeStart;
         ++patternIdxModulus);
#ifdef ENABLE_DEBUG_PRINT
    Serial.print(F("numPatternIds="));
    Serial.print(numPatternIds);
    Serial.print(F(" patternIdxModulus="));
    Serial.println(patternIdxModulus);
#endif
  }

  return patternNum < testPatternIdRangeStart ? patternIds[patternNum % patternIdxModulus] : patternNum;
}


// Some target structures should display a different set or subset of patterns
// rather than the full set.  For those structures, a cross reference table maps the
// selected pattern id to the id of the pattern that should be displayed.  Given the
// selected pattern id, this function returns the id of the pattern to display.
uint8_t resolveDisplayPatternId(uint8_t selectedPatternId) {
#ifdef USE_PATTERN_XREF
  for (uint8_t i = 0; i < numPatternIds; ++i) {
    if (displayPatternIdXref[i][selectedPatternIdIdx] == selectedPatternId) {
      return displayPatternIdXref[i][displayPatternIdIdx];
    }
  }
  // If there is no xref entry for the selected pattern, turn off the display.
  return allOffPatternId;
#else
  // We're not using the xref table, so we display the selected pattern.
  return selectedPatternId;
#endif
}


void startPattern()
{
  uint8_t displayPatternId = resolveDisplayPatternId(activePatternId);
  for (uint8_t iPattern = 0; iPattern < numPatternIds; ++iPattern) {
    if (patternIds[iPattern] != displayPatternId) {
      continue;
    }
    for (uint8_t iStrip = 0; iStrip < NUM_STRIPS; ++iStrip) {
      if (pixels[iStrip] == nullptr) {
        continue;
      }
      for (uint8_t iSection = 0; iSection < MAX_SECTIONS_PER_STRIP; ++iSection) {
        if (numSectionPixels[iStrip][iSection] == 0) {
          continue;
        }
        if (patternObjects[iPattern][iStrip][iSection] != nullptr) {
#ifdef ENABLE_DEBUG_PRINT
          Serial.print(F("calling start for pattern id "));
          Serial.print(patternIds[iPattern]);
          Serial.print(F(", strip "));
          Serial.print(iStrip);
          Serial.print(F(", section "));
          Serial.println(iSection);
#endif
          patternObjects[iPattern][iStrip][iSection]->start();
        }
      }
    }
  }

}


void updatePattern()
{
  // Lamp test mode overrides the current pattern.
  if (digitalRead(LAMP_TEST_PIN) == LAMP_TEST_ACTIVE) {
    // Set all pixels in all strips to white at overallBrightness.
    CRGB lampTestColor = CRGB::White;
    lampTestColor.nscale8_video(overallBrightness);
    for (uint8_t i = 0; i < NUM_STRIPS; ++i) {
      if (pixels[i] != nullptr) {
        fill_solid(pixels[i], numPixels[i], lampTestColor);
      }
    }
    return;
  }

  uint8_t displayPatternId = resolveDisplayPatternId(activePatternId);

  // Pattern id allOffPatternId turns everything off.
  if (displayPatternId == allOffPatternId) {
    for (uint8_t iStrip = 0; iStrip < NUM_STRIPS; ++iStrip) {
      if (pixels[iStrip] != nullptr) {
        fill_solid(pixels[iStrip], numPixels[iStrip], CRGB::Black);
      }
    }
  }

  for (uint8_t iPattern = 0; iPattern < numPatternIds; ++iPattern) {
    if (patternIds[iPattern] != displayPatternId) {
      continue;
    }
    for (uint8_t iStrip = 0; iStrip < NUM_STRIPS; ++iStrip) {
      if (pixels[iStrip] == nullptr) {
        continue;
      }
      for (uint8_t iSection = 0; iSection < MAX_SECTIONS_PER_STRIP; ++iSection) {
        if (numSectionPixels[iStrip][iSection] == 0) {
          continue;
        }
        if (patternObjects[iPattern][iStrip][iSection] != nullptr) {
          patternObjects[iPattern][iStrip][iSection]->update(widgetIsActive);
        }
      }
    }
  }

}

void shiftWave () {
  waveMeasmt[0] += (shiftForward ? 1 : -1);
  if (waveMeasmt[0] == 100 || waveMeasmt[0] == 0) shiftForward = waveMeasmt[0] != 100;
}



/***********************
 * Radio Communication *
 ***********************/

bool handleMeasurementVectorPayload(const MeasurementVectorPayload* payload, uint8_t payloadSize)
{
  // Returns true if we got a valid measurement vector payload.

  static uint8_t newPatternRepetitionCount;

  // The theremin sends the pattern number plus a predefined number of distance measurements.
  constexpr uint16_t expectedPayloadSize = sizeof(WidgetHeader) + sizeof(int16_t) * (numDistanceMeasmts + 1);
  if (payloadSize != expectedPayloadSize) {
#ifdef ENABLE_DEBUG_PRINT
    Serial.print(F("got MeasurementVectorPayload from widget "));
    Serial.print(payload->widgetHeader.id);
    Serial.print(F(" with "));
    Serial.print(payloadSize);
    Serial.print(F(" bytes but expected "));
    Serial.print(expectedPayloadSize);
    Serial.println(F(" bytes"));    
#endif
    return false;
  }

  // Sanity check the data in case a bad message made it past the CRC check.
  bool gotValidData = (payload->measurements[0] >= minValidPatternNum && payload->measurements[0] <= maxValidPatternNum);
  for (uint8_t i = 1; gotValidData && i <= numDistanceMeasmts; ++i) {
    gotValidData = (payload->measurements[i] >= minValidDistance && payload->measurements[i] <= maxValidDistance);
  }
  if (!gotValidData) {
#ifdef ENABLE_DEBUG_PRINT
    Serial.println(F("got message with invalid data"));
#endif
    return false;
  }
  
  // There is only one theremin, so we don't worry about the widget id in payload->widgetHeader.id.

  if (payload->widgetHeader.isActive) {
    widgetIsActive = true;

    // Update activePatternId only if we've received the same new pattern number multiple times.
    uint8_t newPatternId = convertThereminPatternNumberToPatternId((uint8_t) payload->measurements[0]);
    if (newPatternId != activePatternId && ++newPatternRepetitionCount >= newPatternRepetitionThreshold) {
      newPatternRepetitionCount = 0;
      activePatternId = newPatternId;
#ifdef ENABLE_DEBUG_PRINT
      Serial.print(F("got new pattern id "));
      Serial.println(newPatternId);
#endif
      startPattern();
    }

    for (uint8_t i = 0; i < numDistanceMeasmts; ++i) {
      currentDistance[i] = payload->measurements[i + 1];
    }

#ifdef ENABLE_DEBUG_PRINT
  Serial.print(F("got distances"));
  for (uint8_t i = 0; i < numDistanceMeasmts; ++i) {
    Serial.print(" ");
    Serial.print(currentDistance[i]);
  }
  Serial.println();
#endif

  }
  else {
    widgetIsActive = false;
  }

  return true;
}


void pollRadio()
{
#ifdef ENABLE_RADIO

  uint8_t pipeNum;
  if (!radio.available(&pipeNum)) {
    return;
  }

  constexpr uint8_t maxPayloadSize = 32 + sizeof(WidgetHeader);
  uint8_t payload[maxPayloadSize];
  uint8_t payloadSize = radio.getDynamicPayloadSize();
  if (payloadSize > maxPayloadSize) {
#ifdef ENABLE_DEBUG_PRINT
    Serial.print(F("got message on pipe "));
    Serial.print(pipeNum);
    Serial.print(F(" with payload size "));
    Serial.print(payloadSize);
    Serial.print(F(" but maximum payload size is "));
    Serial.println(maxPayloadSize);
#endif
    return;
  }
//#ifdef ENABLE_DEBUG_PRINT
//  Serial.print(F("got message on pipe "));
//  Serial.println(pipeNum);
//#endif

  radio.read(payload, payloadSize);

  bool gotValidPayload = false;
  switch(pipeNum) {
    //case 2:
    // We're subscribed to 2wdgt on pipe 0, so the measurement vector payloads will come in on that pipe.
    // TODO:  need to rework this here and in Illumicone to decouple the Xwdgt addresses from the pipe numbers.
    case 0:
        gotValidPayload = handleMeasurementVectorPayload((MeasurementVectorPayload*) payload, payloadSize);
        break;
    default:
#ifdef ENABLE_DEBUG_PRINT
      Serial.print(F("got message on unsupported pipe "));
      Serial.println(pipeNum);
#endif
      break;
  }

  // TODO:  turn the status LED red if we didn't get a valid payload

#endif
}



/**************************
 * Measurement Simulation *
 **************************/

void updateSimulatedMeasmts(bool doInit)
{
  static bool simulatedMeasmtGoingUp[numDistanceMeasmts];
  static int32_t nextSimulatedMeasmtUpdateMs[numDistanceMeasmts];

  uint32_t now = millis();

  if (doInit) {
    for (uint8_t i = 0; i < numDistanceMeasmts; ++i) {
      nextSimulatedMeasmtUpdateMs[i] = now;
    }
      activePatternId = simulationPatternId;
      startPattern();
  }

  for (uint8_t i = 0; i < numDistanceMeasmts; ++i) {
    if ((int32_t) (now - nextSimulatedMeasmtUpdateMs[i]) >= 0) {
      nextSimulatedMeasmtUpdateMs[i] += simulatedMeasmtUpdateIntervals[i];

      // Reverse direction if the current measurement is at or outside its range.
      if (simulatedMeasmtGoingUp[i] && currentDistance[i] >= maxDistance[i]) {
        simulatedMeasmtGoingUp[i] = false;
      }
      else if (!simulatedMeasmtGoingUp[i] && currentDistance[i] <= minDistance[i]) {
        simulatedMeasmtGoingUp[i] = true;
      }

      if (simulatedMeasmtGoingUp[i]) {
        ++currentDistance[i];
      }
      else {
        --currentDistance[i];
      }
    }
  }

  widgetIsActive = true;
}



/******************
 * Initialization *
 ******************/

void initGpios()
{
  // FastLED takes care of setting up the pixel data output pins.

  pinMode(LAMP_TEST_PIN, INPUT_PULLUP);
  pinMode(RGB_LED_RED_PIN, OUTPUT);
  pinMode(RGB_LED_GREEN_PIN, OUTPUT);
  pinMode(RGB_LED_BLUE_PIN, OUTPUT);
  pinMode(SIMULATION_PIN, INPUT_PULLUP);

  // Turn the status LED half-intensity white.
  analogWrite(RGB_LED_RED_PIN , map(128, 0, 255, rgbLedLowIntensity, rgbLedHighIntensity));
  analogWrite(RGB_LED_GREEN_PIN , map(128, 0, 255, rgbLedLowIntensity, rgbLedHighIntensity));
  analogWrite(RGB_LED_BLUE_PIN , map(128, 0, 255, rgbLedLowIntensity, rgbLedHighIntensity));
}


void initRadio()
{
#ifdef ENABLE_RADIO

  Serial.println(F("Initializing radio..."));    
  radio.begin();

  radio.setPALevel(RF_POWER_LEVEL);
  radio.setRetries(TX_RETRY_DELAY_MULTIPLIER, TX_MAX_RETRIES);
  radio.setDataRate(DATA_RATE);
  radio.setChannel(RF_CHANNEL);
  radio.setAutoAck(ACK_WIDGET_PACKETS);
  radio.enableDynamicPayloads();
  radio.setCRCLength(CRC_LENGTH);

  for (uint8_t i = 0; i < numReadPipes; ++i) {
      radio.openReadingPipe(i, readPipeAddresses[i]);
  }

#ifdef ENABLE_DEBUG_PRINT 
  radio.printDetails();
#endif
  
  radio.startListening();

  Serial.println(F("Radio initialized."));    

#endif
}


bool initPixels()
{
  // Returns false if any strip has too many pixels, or
  // there isn't sufficient memory for the pixel data.
  bool retval = true;

  // For each pixel strip, calculate the total number of pixels in the strip,
  // allocate memory for the pixels, and tell FastLED about the strip.
  for (uint8_t i = 0; i < NUM_STRIPS; ++i) {

    // Any strip with a null pixel data pointer or zero pixels will be ignored when
    // generating patterns and writing data to the strips.  This approach allows us
    // to attempt to continue operating when one or more strips are misconfigured.
    pixels[i] = nullptr;
    numPixels[i] = 0;

    // Calculate the number of pixels in the strip.
    uint16_t numStripPixels = 0;
    for (uint8_t j = 0; j < MAX_SECTIONS_PER_STRIP; ++j) {
      numStripPixels += numSectionPixels[i][j];
    }
    // Ignore a strip that doesn't have any pixels.
    if (numStripPixels == 0) {
      continue;
    }
    // We use 8-bit unsigned integers for pixel indexing, so the number of
    // pixels in any one strip can't exceed the maximum 8-bit value (255).
    if (numStripPixels > UINT8_MAX) {
#ifdef ENABLE_DEBUG_PRINT
    Serial.print(F("Pixel strip "));
    Serial.print(i);
    Serial.print(F(" has too many pixels ("));
    Serial.print(numStripPixels);
    Serial.println(F(")"));
#endif
      retval = false;
      continue;
    }
    numPixels[i] = numStripPixels;

    // If there is sufficient memory available, allocate memory for the strip's pixels.
    uint16_t availableRam = freeRam() > reservedRamSize ? freeRam() - reservedRamSize : 0;
    uint16_t requiredRam = numPixels[i] * sizeof(CRGB);
#ifdef ENABLE_DEBUG_PRINT
    Serial.print(F("Pixel strip "));
    Serial.print(i);
    Serial.print(F(" requires "));
    Serial.print(requiredRam);
    Serial.print(F(" bytes; "));
    Serial.print(availableRam);
    Serial.println(F(" bytes are available."));
#endif
    if (requiredRam <= availableRam) {
      pixels[i] = new CRGB[numPixels[i]];
    }
    else {
#ifdef ENABLE_DEBUG_PRINT
      Serial.print(F("Pixel memory allocation failed for strip "));
      Serial.println(i);
#endif
      retval = false;
    }
  }

  // Add the strips to FastLED so that it will send data to them when FastLED.show() is called.
#if (NUM_STRIPS >= 1)
  if (pixels[0] != nullptr) {
    FastLED.addLeds<STRIP_0_CHIPSET, STRIP_0_PIN, STRIP_0_COLOR_ORDER>(pixels[0], numPixels[0]);
  }
#endif 
#if (NUM_STRIPS >= 2)
  if (pixels[1] != nullptr) {
    FastLED.addLeds<STRIP_1_CHIPSET, STRIP_1_PIN, STRIP_1_COLOR_ORDER>(pixels[1], numPixels[1]);
  }
#endif 
#if (NUM_STRIPS >= 3)
  if (pixels[2] != nullptr) {
    FastLED.addLeds<STRIP_2_CHIPSET, STRIP_2_PIN, STRIP_2_COLOR_ORDER>(pixels[2], numPixels[2]);
  }
#endif 
#if (NUM_STRIPS >= 4)
  #error Too many strips configured.
#endif
#if (!defined(NUM_STRIPS) || NUM_STRIPS <= 0)
  #error Invalid number of strips configured.
#endif

  // Although not enforced above, we'll assume that all the strips are of the
  // same type and should have the same color correction and maximum brightness.
  FastLED.setCorrection(colorCorrection);
  FastLED.setBrightness(overallBrightness);

  return retval;
}


void initPatterns()
{
  for (uint8_t iPattern = 0; iPattern < numPatternIds; ++iPattern) {

    for (uint8_t iStrip = 0; iStrip < NUM_STRIPS; ++iStrip) {
      if (pixels[iStrip] == nullptr) {
        continue;
      }

      uint8_t sectionOffset = 0;
      for (uint8_t iSection = 0; iSection < MAX_SECTIONS_PER_STRIP; ++iSection) {
        if (numSectionPixels[iStrip][iSection] == 0) {
          continue;
        }
   
        CRGB* pixelSection = pixels[iStrip] + sectionOffset;
        uint8_t numPixelsInSection = numSectionPixels[iStrip][iSection];

        patternObjects[iPattern][iStrip][iSection] = pixelPatternFactory(patternIds[iPattern]);
        if (patternObjects[iPattern][iStrip][iSection] != nullptr) {
          // Give the pattern object pointers to everything it needs to generate an interactive pattern.
          patternObjects[iPattern][iStrip][iSection]->init(
            pixelSection,
            numPixelsInSection,
            iStrip,
            iSection,
            numDistanceMeasmts,
            minDistance,
            maxDistance,
            currentDistance,
            waveMeasmt);
#ifdef ENABLE_DEBUG_PRINT
          Serial.print(freeRam());
          Serial.print(F(" bytes available after instantiating pattern id "));
          Serial.print(patternIds[iPattern]);
          Serial.print(F(" for strip "));
          Serial.print(iStrip);
          Serial.print(F(" section "));
          Serial.println(iSection);
#endif
        }
        else {
#ifdef ENABLE_DEBUG_PRINT
          Serial.print(F("*** Instantiation of pattern id "));
          Serial.print(patternIds[iPattern]);
          Serial.print(F(" for strip "));
          Serial.print(iStrip);
          Serial.print(F(" section "));
          Serial.print(iSection);
          Serial.println(F(" failed."));
#endif
        }
        sectionOffset += numPixelsInSection;
      }
    }
  }

  activePatternId = defaultPatternId;
  startPattern();
}


void setup()
{
#ifdef ENABLE_DEBUG_PRINT
  Serial.begin(115200);
  printf_begin();
  Serial.println(F("Debug print enabled."));    
#endif

  initGpios();
  initRadio();
  initPixels();
  initPatterns();

#ifdef ENABLE_WATCHDOG
  wdt_enable(WDTO_1S);     // enable the watchdog
#endif
}



/************
 * Run Loop *
 ************/

void loop()
{
#ifdef ENABLE_RADIO
  if (digitalRead(SIMULATION_PIN) == SIMULATION_ACTIVE) {
    // If we are just starting to use simulated measurements, usingSimulatedMeasmts
    // will be false at this point, so passing !usingSimulatedMeasmts to
    // updateSimulatedMeasmts tells it to do initialization.
    updateSimulatedMeasmts(!usingSimulatedMeasmts);
    usingSimulatedMeasmts = true;
  }
  else {
    usingSimulatedMeasmts = false;
    pollRadio();
  }
#else
  updateSimulatedMeasmts(!usingSimulatedMeasmts);
  usingSimulatedMeasmts = true;
#endif

  // Periodically update the pattern.
  EVERY_N_MILLISECONDS(PATTERN_UPDATE_INTERVAL_MS) {
    shiftWave();
    updatePattern();
  }

  // Periodically write to the LEDs.
  EVERY_N_MILLISECONDS(1000 / LED_FRAMES_PER_SECOND) {
    FastLED.show();
  }

#ifdef ENABLE_WATCHDOG
  // Kick the dog (gently, of course) to let him know we're still alive.
  wdt_reset();
#endif
}
