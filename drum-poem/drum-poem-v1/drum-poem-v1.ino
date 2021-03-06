#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioPlaySdWav           sd;     //xy=262,388
AudioAmplifier           ampLeft;           //xy=703,356
AudioAmplifier           ampRight;           //xy=726,404
AudioOutputI2S           i2s1;           //xy=1059,387
AudioConnection          patchCord1(sd, 0, ampLeft, 0);
AudioConnection          patchCord2(sd, 1, ampRight, 0);
AudioConnection          patchCord3(ampLeft, 0, i2s1, 0);
AudioConnection          patchCord4(ampRight, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=99,88
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

void setup() {
  // put your setup code here, to run once:
  AudioMemory(8);
  
  ampLeft.gain(1.0);
  ampRight.gain(1.0);

  Serial.begin(9600);


  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.1);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  
}

void block()
{
  while(sd.isPlaying() != 0);
  return;
}

void play1(){
  while(sd.isPlaying() == 0)
  {
    sd.play("00000001.WAV");
  }
  return;
}

void play2(){
  while(sd.isPlaying() == 0)
  {
    sd.play("00000002.WAV");
  }
  return;
}

void play3(){
  while(sd.isPlaying() == 0)
  {
    sd.play("00000003.WAV");
  }
  return;
}

void play4(){
  while(sd.isPlaying() == 0)
  {
    sd.play("00000004.WAV");
  }
  return;
}

void play5(){
  while(sd.isPlaying() == 0)
  {
    sd.play("00000005.WAV");
  }
  return;
}

void play6(){
  while(sd.isPlaying() == 0)
  {
    sd.play("00000006.WAV");
  }
  return;
}

void play7(){
  while(sd.isPlaying() == 0)
  {
    sd.play("00000007.WAV");
  }
  return;
}


void loop() {
  // put your main code here, to run repeatedly:
  play1();
  block();
  play2();
  block();
  play3();
  block();
  play4();
  block();
  play5();
  block();
  play6();
  block();
  play7();
  block();

}
