#pragma once
#include "vec.h"
#include <portaudio.h>

#define SAMPLE_RATE (48000)
#define SAMPLE_PERBUFFER (2048)
#define BUFFER_SIZE SAMPLE_RATE
#define TABLE_SIZE SAMPLE_RATE * 2

struct paCallbacktData {
  float *buffer = new float[BUFFER_SIZE];
  float *insert = buffer;
  float *get = ++buffer;
  vec2 *dftData = new vec2[SAMPLE_PERBUFFER];
  int speed = 100;
  int phase = 0;
};

class Sound {
public:
  Sound();
  bool start();
  bool stop();
  bool restart(int inputDevice, int outputDevice);

private:
  paCallbacktData data;
  const char **names;
  PaStream *stream;
  PaStreamParameters outputParameters;
  PaStreamParameters inputParameters;
};