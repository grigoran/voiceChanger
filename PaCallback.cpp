#include "PaCallback.h"
#include "Sound.h"
#include "fft.h"

int paCallback(const void *inputBuffer, void *outputBuffer,
               unsigned long framesPerBuffer,
               const PaStreamCallbackTimeInfo *timeInfo,
               PaStreamCallbackFlags statusFlags, void *userData) {
  /* Cast data passed through stream to our structure. */
  paCallbacktData *data = (paCallbacktData *)userData;
  float *out = (float *)outputBuffer;
  float *input = (float *)inputBuffer;
  for (int i = 0; i < framesPerBuffer; i++) {
    out[i] = input[i];
  }
  // FFT(input, data->dftData, framesPerBuffer);
  // IFFT(data->dftData, out, framesPerBuffer);
  return 0;
}