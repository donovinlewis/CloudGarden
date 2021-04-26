/*
   RadioLib RF69 Transmit Example

   This example transmits packets using RF69 FSK radio module.
   Each packet contains up to 64 bytes of data, in the form of:
    - Arduino String
    - null-terminated char array (C-string)
    - arbitrary binary data (byte array)

   For default module settings, see the wiki page
   https://github.com/jgromes/RadioLib/wiki/Default-configuration#rf69sx1231

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/
*/

// include the library
#include <RadioLib.h>

#define portMAX_DELAY UINT32_MAX

// RF69 has the following connections:
// CS pin:    11
// DIO0 pin:  3
// RESET pin: 10
#if defined (__AVR_ATmega328P__)
  RF69 radio = new Module(SS, 3, 10);
#else 
  RF69 radio = new Module(10, 2, 3);
#endif

// or using RadioShield
// https://github.com/jgromes/RadioShield
//RF69 radio = RadioShield.ModuleA;

void printFailure(int code) {
  if (code != ERR_NONE) {
    Serial.print(F("failed, code "));
    Serial.println(code);
  }
}


void setup() {
  Serial.begin(115200);

  radio.reset();
  delay(10);

  // initialize RF69 with default settings
  Serial.print(F("[RF69] Initializing ... "));
  int state = radio.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // NOTE: some RF69 modules use high power output,
  //       those are usually marked RF69H(C/CW).
  //       To configure RadioLib for these modules,
  //       you must call setOutputPower() with
  //       second argument set to true.
  Serial.print(F("[RF69] Setting high power module ... "));
  state = radio.setOutputPower(13, false);
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
  printFailure(radio.setFrequency(900.0));
  printFailure(radio.setBitRate(100.0));
  printFailure(radio.disableAddressFiltering());
  uint8_t syncWord[4] = {0x01, 0x23, 0x45, 0x67};
  printFailure(radio.setSyncWord(syncWord, 4));
  printFailure(radio.enableSyncWordFiltering());
  printFailure(radio.setPromiscuousMode(false));
  printFailure(radio.disableAES());
  printFailure(radio.setCrcFiltering(false));
  printFailure(radio.setDataShaping(RADIOLIB_SHAPING_0_5));
  printFailure(radio.setEncoding(RADIOLIB_ENCODING_MANCHESTER));
  printFailure(radio.variablePacketLengthMode(RF69_MAX_PACKET_LENGTH));
}

void loop() {
  Serial.print(F("[RF69] Transmitting packet ... "));

  // you can transmit C-string or Arduino string up to 64 characters long
  int state = radio.transmit("Hello World!");

  // you can also transmit byte array up to 64 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    int state = radio.transmit(byteArr, 8);
  */

  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("success!"));

  } else if (state == ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 64 bytes
    Serial.println(F("too long!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }

  String str;
  state = ERR_RX_TIMEOUT;
  while (state != ERR_NONE)
  {
    state = radio.receive(str, 14, portMAX_DELAY);
    if (state == ERR_NONE)
    {
      Serial.println(F("Got something"));
      Serial.println(str);
    }
    else
    {
      Serial.println(F("Got nothing"));
    }
  }
  

  // wait for a second before transmitting again
  delay(1000);
}
