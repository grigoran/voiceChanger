#pragma once
#include <portaudio.h>
#include "PaCallback.h"
#include "vec.h"

#define SAMPLE_RATE (48000)
#define SAMPLE_PERBUFFER (4096)
#define BUFFER_SIZE SAMPLE_RATE
#define TABLE_SIZE SAMPLE_RATE*2

typedef struct
{
	float* buffer = new float[BUFFER_SIZE];
	float* insert = buffer;
	float* get = ++buffer;
	vec2* dftData = new vec2[SAMPLE_PERBUFFER];
	int speed = 100;
	int phase = 0;
}
paCallbacktData;

class Sound {
public:
	Sound();
	bool start();
	bool stop();
private:
	paCallbacktData data;
	const char** names;
	PaStream* stream;
	PaStreamParameters outputParameters;
	PaStreamParameters inputParameters;
};