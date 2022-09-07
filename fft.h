#define _USE_MATH_DEFINES
#include <math.h>
#include "vec.h"


void IFFT(vec2* source, float* result, int size);

void FFT(float* source, vec2* result, int size);

int getFreqIndex(int frequency, int framesPerBuffer, int sampleRate);