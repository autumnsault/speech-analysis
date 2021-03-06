//
// Created by clo on 9/12/2019.
//

#include <iostream>
#include "AudioDevices.h"

AudioDevices::AudioDevices()
{
    refreshList();
}

bool AudioDevices::refreshList()
{
    inputs.clear();
    outputs.clear();

    int numDevices = Pa_GetDeviceCount();
    if (numDevices < 0) {
        std::cerr << "ERROR: Pa_CountDevices returned 0x" << std::hex << numDevices << std::dec << std::endl;
        return false;
    }
    else if (numDevices == 0) {
        std::cerr << "ERROR: Pa_CountDevices returned 0 (zero)." << std::endl;
        return false;
    }

    const PaDeviceInfo * info;

    for (int id = 0; id < numDevices; ++id) {
        info = Pa_GetDeviceInfo(id);

        if (info->maxInputChannels > 0) {
            inputs.push_back({
                .id = id,
                .name = info->name,
            });
        }

        if (info->maxOutputChannels > 0) {
            outputs.push_back({
                .id = id,
                .name = info->name
            });
        }
    }
    
    if (inputs.empty()) {
        std::cout << "No input devices found." << std::endl;
    }

    if (outputs.empty()) {
        std::cout << "No output devices found." << std::endl;
    }

    return true;
}

const std::vector<AudioDevice> & AudioDevices::getInputs() const {
    return inputs;
}

const std::vector<AudioDevice> & AudioDevices::getOutputs() const {
    return outputs;
}

PaDeviceIndex AudioDevices::getDefaultInputDevice() const {
    PaDeviceIndex ind = Pa_GetDefaultInputDevice();
    if (ind == paNoDevice) {
        std::cout << "No default input device found." << std::endl;
        return inputs.front().id;
    }
    return ind;
}
