/*
  ==============================================================================

    Series.h
    Created: 23 Apr 2020 12:47:30pm
    Author:  Jerry Bennett

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Series {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    Series();
    
    Series(float dry, float length);
    
    // Destructor
    ~Series();
    
    void processSignal(float * samples, const int numSamples, const int channel);
    
    float processSample(float x, int channel);

    void setFs(float Fs);
    
    void setDry(float dry);
    
    void setLength(float length);

private:
        
    // Array for delay buffer
    
    static const int MAX_BUFFER_SIZE = 96000;
    
    float delayBuffer[MAX_BUFFER_SIZE][2] = {0.0f};
    
    int index[2] = {0};
    
    float dry = 0.f;
    
    //float length = 50.f;
    
    float delayLengthMS = 200.f;
    
    float linearGain = 0.5;
    
    float Fs = 480000;
    
    int delayLengthSamples = floor(Fs*delayLengthMS/1000.f);
};
