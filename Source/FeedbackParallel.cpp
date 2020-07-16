//
//  FeedbackParallel.cpp
//  VocalChain
//
//  Created by Jerry Bennett on 4/18/20.
//

#include "FeedbackParallel.hpp"

FeedbackParallel::FeedbackParallel(){
}

FeedbackParallel::FeedbackParallel(float dry,float delayLengthMS){
    this->dry = dry;
    this->delayLengthMS = delayLengthMS;
}

// Destructor
FeedbackParallel::~FeedbackParallel(){
}

void FeedbackParallel::processSignal(float * samples, const int numSamples, const int channel){
    // Where we do our effect
    // Perform the processing
    for (int n = 0; n < numSamples ; n++){
            float x = samples[n];

            samples[n] = processSample(x,channel);
        }
    }


float FeedbackParallel::processSample(float x, int channel){
    delayLengthSamples = floor(Fs*delayLengthMS/1000.f);
    
    
    // Feed-back Parallel
    // Step 1: read from buffer to get output
    float y = x + linearGain * delayBuffer[ index[channel] ][channel];//???
    
    // Step 2: write into buffer our input
    delayBuffer[index[channel]][channel] = y;
    
        
    // Step 3: move index
    if (index[channel] < delayLengthSamples -1){
        index[channel]++;
    }
    else{
        index[channel] = 0;
    }
        
    return y;//???
}

void FeedbackParallel::setFs(float Fs){
    this->Fs = Fs;
}

void FeedbackParallel::setDry(float dry){
    if(dry >= 0.f){
        this->dry = dry;
    }
}

void FeedbackParallel::setLength(float delayLengthMS){
    if(delayLengthMS >= 200){
        this->delayLengthMS = delayLengthMS;
    }
}


