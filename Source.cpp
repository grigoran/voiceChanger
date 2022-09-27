
#include "Sound.h"
#include "gui.h"
#include <iostream>
#include <portaudio.h>

#define ROSOLUTION_X 800
#define RESOLUTION_Y 600

struct selectedDevices {
  int input = 0;
  int output = 0;
} seldevices;

void changeInputDevice(void *data, int dev) {
  Sound *sound = (Sound *)data;
  seldevices.input = dev;
  sound->restart(dev, seldevices.output);
}
void changeOutputDevice(void *data, int dev) {
  Sound *sound = (Sound *)data;
  seldevices.output = dev;
  sound->restart(seldevices.input, dev);
}

int main() {
  Sound sound;
  sound.start();
  int deviceCount = Pa_GetDeviceCount();
  const char **devices = new const char *[deviceCount];
  for (int i = 0; i < deviceCount; i++) {
    devices[i] = Pa_GetDeviceInfo(i)->name;
  }

  Gui gui(800, 600, "voiceChanger");
  list inputDeviceList;
  list outputDeviceList;
  inputDeviceList.setChangeCallback(changeInputDevice);
  inputDeviceList.setUserCallbackData(&sound);
  outputDeviceList.setChangeCallback(changeOutputDevice);
  outputDeviceList.setUserCallbackData(&sound);
  gui.pushElement(&inputDeviceList);
  gui.pushElement(&outputDeviceList);

  inputDeviceList.setContent(devices, deviceCount);
  inputDeviceList.setPosition(10, 10);
  outputDeviceList.setContent(devices, deviceCount);
  outputDeviceList.setPosition(300, 10);

  inputDeviceList.setSelectedItem(Pa_GetDefaultInputDevice());
  outputDeviceList.setSelectedItem(Pa_GetDefaultInputDevice());

  while (gui.isOpen()) {
    gui.update();
  }
  sound.stop();

  return 0;
}
