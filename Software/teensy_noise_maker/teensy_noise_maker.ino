#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav           playWav1;
AudioOutputI2S           i2s;
AudioConnection          patchCord1(playWav1, 0, i2s, 0);
AudioConnection          patchCord2(playWav1, 1, i2s, 1);
AudioControlSGTL5000     sgtl5000_1;

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

#define VOLUME_PIN 15

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");

  AudioMemory(20);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
}

void loop() {
  playWav1.play("RAINLP1.WAV");
  // A brief delay for the library read WAV info
  delay(5);
  while (playWav1.isPlaying())
  {
    float vol = analogRead(VOLUME_PIN);
    vol = vol / 1023.0;
    sgtl5000_1.volume(vol);
    delay(10);
  }
}
