#include "fft.h"

void FFT(float* source, vec2* result, int size) {
	if (size == 2) {
		result[0].x = source[0] + source[1];
		result[1].x = source[0] - source[1];
		result[0].y = 0;
		result[1].y = 0;
		return;
	}
	float* odd = new float[size / 2];
	float* even = new float[size / 2];
	vec2* oddResult = new vec2[size / 2];
	vec2* evenResult = new vec2[size / 2];
	for (int i = 0; i < size; i += 2) {
		odd[i / 2] = source[i];
		even[i / 2] = source[i + 1];
	}
	FFT(odd, oddResult, size / 2);
	FFT(even, evenResult, size / 2);
	float wc = 0;
	float ws = 0;
	for (int i = 0; i < size / 2; i++) {
		wc = cos(i * 2 * M_PI / size);
		ws = sin(i * 2 * M_PI / size);
		result[i].x = oddResult[i].x + evenResult[i].x * wc + evenResult[i].y * ws;
		result[i].y = oddResult[i].y - evenResult[i].x * ws + evenResult[i].y * wc;
		result[i + size / 2].x = oddResult[i].x - evenResult[i].x * wc - evenResult[i].y * ws;
		result[i + size / 2].y = oddResult[i].y + evenResult[i].x * ws - evenResult[i].y * wc;
	}
	delete[] odd;
	delete[] even;
	delete[] oddResult;
	delete[] evenResult;
}

int getFreqIndex(int frequency, int framesPerBuffer, int sampleRate)
{
	return (int)(framesPerBuffer * frequency / sampleRate);
	return 0;
}


void IFFTworker(vec2* source, vec2* result, int size) {
	if (size == 2) {
		result[0].x = source[0].x + source[1].x;
		result[0].y = source[0].y + source[1].y;
		result[1].x = source[0].x - source[1].x;
		result[1].y = source[0].y - source[1].y;
		return;
	}
	vec2* odd = new vec2[size / 2];
	vec2* even = new vec2[size / 2];
	vec2* oddResult = new vec2[size / 2];
	vec2* evenResult = new vec2[size / 2];
	for (int i = 0; i < size; i += 2) {
		odd[i / 2] = source[i];
		even[i / 2] = source[i + 1];
	}
	IFFTworker(odd, oddResult, size / 2);
	IFFTworker(even, evenResult, size / 2);
	float wc = 0;
	float ws = 0;
	for (int i = 0; i < size / 2; i++) {
		wc = cos((float)i * 2 * M_PI / size);
		ws = sin((float)i * 2 * M_PI / size);
		result[i].x = oddResult[i].x + evenResult[i].x * wc - evenResult[i].y * ws;
		result[i].y = oddResult[i].y + evenResult[i].x * ws + evenResult[i].y * wc;
		result[i + size / 2].x = oddResult[i].x - evenResult[i].x * wc + evenResult[i].y * ws;
		result[i + size / 2].y = oddResult[i].y - evenResult[i].x * ws - evenResult[i].y * wc;
	}
	delete[] odd;
	delete[] even;
	delete[] oddResult;
	delete[] evenResult;
}

void IFFT(vec2* source, float* result, int size) {
	vec2* middleRes = new vec2[size];
	IFFTworker(source, middleRes, size);
	for (int i = 0; i < size; i++) {
		result[i] = middleRes[i].x / size;
	}
	delete[] middleRes;
}