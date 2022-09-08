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
		std::cout << i << ": " << Pa_GetDeviceInfo(i)->name << std::endl;
	}

	while (true)
	{
		//if (GetKeyState(VK_ESCAPE) & 0x8000) break;
	}

	sound.stop();

	return 0;
}
