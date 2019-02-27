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

#define NUM_TO_PLAY 8
int toplay[NUM_TO_PLAY] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  AudioMemory(8);
  
  ampLeft.gain(1.0);
  ampRight.gain(1.0);

  Serial.begin(9600);


  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  /*set pizo pins*/
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(8), play1i, RISING );
  attachInterrupt(digitalPinToInterrupt(5), play2i, RISING );
  
}


void block()
{
  digitalWrite(13, HIGH);
  while(sd.isPlaying() != 0);
  for(int i = 0; i < NUM_TO_PLAY; i++) toplay[i] = 0;
  digitalWrite(13, LOW);
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

void play1i() {
  toplay[1] = 1;
  return;
}

void play2i() {
  toplay[2] = 1;
  return;
}



void loop() {
  // put your main code here, to run repeatedly:


  if(1 == toplay[1])      {play1(); block();}
  else if(1 == toplay[2]) {play2(); block();}
  else if(1 == toplay[3]) {play3(); block();}
  else if(1 == toplay[4]) {play4(); block();}
  else if(1 == toplay[5]) {play5(); block();}
  else if(1 == toplay[6]) {play6(); block();}
  else if(1 == toplay[7]) {play7(); block();}
  delay(1);

}
