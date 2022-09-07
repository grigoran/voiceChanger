#include "PaCallback.h"
#include "fft.h"
#include "Sound.h"


int paCallback(const void* inputBuffer, void* outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void* userData)
{
	/* Cast data passed through stream to our structure. */
	paCallbacktData* data = (paCallbacktData*)userData;
	float* out = (float*)outputBuffer;
	float* input = (float*)inputBuffer;

	data->phase += data->speed;

	FFT(input, data->dftData, framesPerBuffer);


	int beginFreq = getFreqIndex(50, framesPerBuffer, SAMPLE_RATE);
	int endFreq = getFreqIndex(10000, framesPerBuffer, SAMPLE_RATE);
	int pithScale = endFreq - beginFreq;
	for (int i = 0; i < pithScale / 2; i++) {
		data->dftData[i + beginFreq] = data->dftData[2 * i + beginFreq];
	}
	for (int i = pithScale / 2; i < pithScale; i++) {
		data->dftData[i + beginFreq].x = 0;
		data->dftData[i + beginFreq].y = 0;
	}
	pithScale = pithScale / 2;
	for (int i = 0; i < pithScale / 2; i++) {
		data->dftData[i + beginFreq] = data->dftData[2 * i + beginFreq];
	}
	for (int i = pithScale / 2; i < pithScale; i++) {
		data->dftData[i + beginFreq].x = 0;
		data->dftData[i + beginFreq].y = 0;
	}

	IFFT(data->dftData, out, framesPerBuffer);
	return 0;
}