#pragma once

#include <mmdeviceapi.h>
#include <mmsystem.h>
#include <string>
#include <vector>
#include <iostream>
#include "Stringer.h"
#include <functiondiscoverykeys.h>
#include <Audioclient.h>
#include <initguid.h>

#define AUDIO_OUT_FORCE_RELEASE -1

typedef struct AudioOutDevice
{
	std::string name;
	std::string id;
	size_t index;
} AudioOutDevice;

class AudioOut
{
public:
	bool setOutputDevice(int index = 0);
	void fetchDevices();
	//AudioOutputDevice selectOutputDevice(const char * name);
	//const std::vector<AudioOutputDevice> listOutputDevices() const;

	bool isReady();
	const std::vector<AudioOutDevice> getDevices();
	void captureAudio();
	const std::vector<int16_t> popBuffer();
	const uint32_t getFrequency() const;

private:
	bool releaseDevices(HRESULT hr = AUDIO_OUT_FORCE_RELEASE);
	bool releaseDeviceCollection(HRESULT hr = AUDIO_OUT_FORCE_RELEASE);
	void swapBuffers();
	
	std::vector<AudioOutDevice> _devices;
	std::vector<int16_t> _outBuffers[2];
	int _activeBuffer = 0;
	int _isReady = false;

	size_t maxOutBufferSize = 0;

	const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
	const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
	const IID IID_IAudioClient = __uuidof(IAudioClient);
	const IID IID_IAudioCaptureClient = __uuidof(IAudioCaptureClient);
};
