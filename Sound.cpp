#include "Sound.h"


Sound::Sound() {
	Pa_Initialize();
	int deviceCount = Pa_GetDeviceCount();
	names = new const char* [deviceCount];
	for (int i = 0; i < deviceCount; i++) {
		names[i] = Pa_GetDeviceInfo(i)->name;
	}
}


bool Sound::start() {
	outputParameters.channelCount = 1;
	outputParameters.device = 3;
	outputParameters.hostApiSpecificStreamInfo = 0;
	outputParameters.sampleFormat = paFloat32;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(3)->defaultLowInputLatency;

	inputParameters.channelCount = 1;
	inputParameters.device = 5;
	inputParameters.hostApiSpecificStreamInfo = 0;
	inputParameters.sampleFormat = paFloat32;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(5)->defaultLowInputLatency;

	Pa_OpenStream(
		&stream,
		&inputParameters,
		&outputParameters,
		SAMPLE_RATE,
		SAMPLE_PERBUFFER,
		paNoFlag, //flags that can be used to define dither, clip settings and more
		paCallback, //your callback function
		&data);
	Pa_StartStream(stream);
	return 0;
}

bool Sound::stop() {
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
	return 0;
}