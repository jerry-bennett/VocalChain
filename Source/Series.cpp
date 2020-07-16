/*
  ==============================================================================

    Series.cpp
    Created: 23 Apr 2020 12:47:30pm
    Author:  Jerry Bennett

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Series.h"

//==============================================================================
Series::Series(){
}

Series::Series(float dry,float delayLengthMS){
    this->dry = dry;
    this->delayLengthMS = delayLengthMS;
}

// Destructor
Series::~Series(){
}

void Series::processSignal(float * samples, const int numSamples, const int channel){
    // Where we do our effect
    // Perform the processing
    for (int n = 0; n < numSamples ; n++){
            float x = samples[n];

            samples[n] = processSample(x,channel);
        }
    }


float Series::processSample(float x, int channel){
    delayLengthSamples = floor(Fs*delayLengthMS/1000.f);
    
    float y = delayBuffer[ index[channel] ][channel];;
    
    delayBuffer[ index[channel] ][channel] = x;
    
    if (index[channel] < 11999){
        index[channel]++;
    }else{
        index[channel] = 0;
    }
        
    return y;//???
}

void Series::setFs(float Fs){
    this->Fs = Fs;
}

void Series::setDry(float dry){
    if(dry >= 0.f){
        this->dry = dry;
    }
}

void Series::setLength(float delayLengthMS){
    if(delayLengthMS >= 200){
        this->delayLengthMS = delayLengthMS;
    }
}
