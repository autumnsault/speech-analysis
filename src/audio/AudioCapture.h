//
// Created by clo on 12/09/2019.
//

#ifndef SPEECH_ANALYSIS_AUDIOCAPTURE_H
#define SPEECH_ANALYSIS_AUDIOCAPTURE_H

#include <portaudio.h>
#include <Eigen/Core>
#include "RingBuffer.h"

#define CAPTURE_DURATION 35.0
#define CAPTURE_SAMPLE_COUNT(sampleRate) ((CAPTURE_DURATION * sampleRate) / 1000)

#define BUFFER_SAMPLE_COUNT(sampleRate) (CAPTURE_SAMPLE_COUNT(sampleRate))

struct RecordContext {
    RingBuffer buffer;
    PaSampleFormat format;
};

class AudioCapture {
public:
    AudioCapture();
    ~AudioCapture();

    void openInputDevice(int id);
    void openOutputDevice(int id);
    void startStream();
    void closeStream();

    static int readCallback(const void * input, void * output,
                     unsigned long frameCount,
                     const PaStreamCallbackTimeInfo * timeInfo,
                     PaStreamCallbackFlags statusFlags,
                     void * userData);

    [[nodiscard]]
    int getSampleRate() const noexcept;

    void readBlock(Eigen::ArrayXd & capture) noexcept;

private:
    PaError err;
    PaStream * stream;

    PaStreamParameters parameters;
    double sampleRate;

    // Ring buffer
    struct RecordContext audioContext;

};

#endif //SPEECH_ANALYSIS_AUDIOCAPTURE_H
