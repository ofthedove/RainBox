#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     noise1;         //xy=403,240
AudioPlaySdWav           playSdWav1;     //xy=538,321
AudioSynthNoisePink      pink1;          //xy=550,190
AudioFilterStateVariable filter1;        //xy=552,247
AudioMixer4              mixer1;         //xy=782,279
AudioOutputI2S           i2s1;           //xy=981,279
AudioConnection          patchCord1(noise1, 0, filter1, 0);
AudioConnection          patchCord2(playSdWav1, 0, mixer1, 2);
AudioConnection          patchCord3(pink1, 0, mixer1, 0);
AudioConnection          patchCord4(filter1, 1, mixer1, 1);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=922,349
// GUItool: end automatically generated code

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

enum
{
  Channel_Pink = 0,
  Channel_FilteredWhite = 1,
  Channel_Rain = 2,
  Channel_Max,
};
typedef uint8_t Channel_t;

static const float ChannelOff = 0.0;
static const float ChannelOn = 1.0;
static const float AdcMax = 1023.0;
static const float SwitchThreshold = 0.1;

static Channel_t currentChannel = 0;
static bool alreadySwitched = false;

void UpdateVolume(void)
{
  float vol = analogRead(15);
  vol = vol / AdcMax;
  sgtl5000_1.volume(vol);
}

void UpdateSwitch(void)
{
  for(Channel_t channel = 0; channel < Channel_Max; channel++)
  {
    if(channel == currentChannel)
    {
      mixer1.gain(channel, ChannelOn);
    }
    else
    {
      mixer1.gain(channel, ChannelOff);
    }
  }
}

void UpdateChannelSelection(void)
{
  float vol = analogRead(15);
  vol /= AdcMax;
  if(vol < SwitchThreshold)
  {
    if(!alreadySwitched)
    {
      currentChannel = (currentChannel + 1) % Channel_Max;
      alreadySwitched = true;

      switch(currentChannel)
      {
        case Channel_Pink:
          Serial.println("Switched to Pink Channel");
          break;
          
        case Channel_FilteredWhite:
          Serial.println("Switched to Filtered White Channel");
          break;
          
        case Channel_Rain:
          Serial.println("Switched to Rain Channel");
          break;
      }
      UpdateSwitch();
    }
  }
  else
  {
    alreadySwitched = false;
  }
}

void PlayFile(void)
{
  if(!playSdWav1.isPlaying())
  {
    playSdWav1.play("RAINLP1.WAV");
    Serial.println("Play Rain Loop 1");
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  sgtl5000_1.enable();
  UpdateVolume();

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
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

  PlayFile();
  noise1.amplitude(0.5);
  pink1.amplitude(0.5);
  filter1.frequency(200);
  filter1.resonance(1.0);
  UpdateSwitch();
}

void loop() {
  UpdateVolume();
  UpdateChannelSelection();
  PlayFile();

  delay(50);
}
