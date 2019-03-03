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

#define NUM_TO_PLAY 7
int current_to_play = 1;
int flag_play = 0;

/* set volume timer for intergration */
IntervalTimer volumeTimer;
IntervalTimer playTimer;

/* volume intergrater */
double volume_intergrater = 0.0;
double volume_intergrater_k_input = 0.01;
double volume_intergrater_k_reduce = 0.001;
#define volume_intergrater_max 1.0
#define volume_min 0.3

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

  //attachInterrupt(digitalPinToInterrupt(8), play1i, RISING );
  //attachInterrupt(digitalPinToInterrupt(5), play2i, RISING );
  attachInterrupt(digitalPinToInterrupt(8), play_next, RISING );
  //attachInterrupt(digitalPinToInterrupt(5), play_next, RISING );

  /* Start volume timer */
  volumeTimer.begin(doVolumeTimer, 10000);
  //playTimer.begin(doPlayTimer,10000);
}
int tmp = 0;
void play_next(){
  flag_play = 1;
  noInterrupts();
  double tmp_vol = volume_intergrater;
  tmp_vol = tmp_vol + volume_intergrater_k_input;
  if(tmp_vol > volume_intergrater_max) tmp_vol = volume_intergrater_max;
  volume_intergrater = tmp_vol;
  interrupts();
  tmp_vol = tmp_vol / volume_intergrater_max;
  if(tmp_vol < volume_min) tmp_vol = volume_min;
  sgtl5000_1.volume(tmp_vol);
  
  Serial.println(tmp_vol);
  return;
}


void block()
{
  digitalWrite(13, HIGH);
  //while(sd.isPlaying() != 0);
  while(sd.isPlaying() == 0);
  //for(int i = 0; i < NUM_TO_PLAY; i++) toplay[i] = 0;
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

/*
void play1i() {
  toplay[1] = 1;
  return;
}

void play2i() {
  toplay[2] = 1;
  return;
}
*/

void doVolumeTimer() {
  double tmp_vol = volume_intergrater;
  tmp_vol = tmp_vol - volume_intergrater_k_reduce;
  if(tmp_vol < volume_min) tmp_vol = volume_min;
  volume_intergrater = tmp_vol;
  tmp_vol = tmp_vol / volume_intergrater_max;
  if(tmp_vol < volume_min) tmp_vol = volume_min;
  sgtl5000_1.volume(tmp_vol);
  Serial.println(tmp_vol);
  //yield();
  return;
}
void doPlayTimer() {
  // put your main code here, to run repeatedly:
 if(1 == flag_play){
  flag_play = 0;
 
  if(1 == current_to_play)      {play1();}
  else if(2 == current_to_play) {play2();}
  else if(3 == current_to_play) {play3();}
  else if(4 == current_to_play) {play4();}
  else if(5 == current_to_play) {play5();}
  else if(6 == current_to_play) {play6();}
  else if(7 == current_to_play) {play7();}
  block();

  current_to_play++;
  if(current_to_play > NUM_TO_PLAY) current_to_play = 1;
  
 }
 //yield();
 return;
}

void loop() {
  //noInterrupts();
  //interrupts();
  doPlayTimer();
  delay(1);

}
