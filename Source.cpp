#include <iostream>
#include "Sound.h"


int errorHandler(PaError* err) {
	if (*err != paNoError) {
		printf("PortAudio error: %s\n", Pa_GetErrorText(*err));
		return 1;
	}
	return 0;
}

int main() {
	Sound sound;
	sound.start();

	for (int i = 0; i < Pa_GetDeviceCount(); i++) {
		std::cout << i << ": " << Pa_GetDeviceInfo(i)->name
		<<" in:"<<Pa_GetDeviceInfo(i)->maxInputChannels
		<<" out:"<<Pa_GetDeviceInfo(i)->maxOutputChannels
		<<" r:"<<Pa_GetDeviceInfo(i)->defaultSampleRate
		<<std::endl;
	}
	std::cout<<"type e to exit\n";

	while (true)
	{
		char a;
		std::cin>>a;
		if(a=='e') break;
	}

	sound.stop();

	return 0;
}
