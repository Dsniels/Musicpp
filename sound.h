
#ifndef SOUND_H
#define SOUND_H
#define UPDATE_PERIOD_MS 50
#define  MIN_FREQ 100
#define MAX_FREQ 800

#include <ao/ao.h>
#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <thread>

class Sound {

 public:
  Sound(/* args */);
  void play(int x, int y, int winWidth, int winHeight);
  void pause();
  void destroy();

 private:
  ao_device *device;
  ao_sample_format format;
  char *buffer = NULL;
  int bufferSize = 0;
  bool soundActive = false;
  bool soundPlaying = false;
  std::thread soundThread;
  void playLoop();
};

#endif