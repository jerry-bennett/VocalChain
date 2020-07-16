//
//  FeedbackParallel.cpp
//  VocalChain
//
//  Created by Jerry Bennett on 4/18/20.
//

#include "FeedbackParallel.hpp"

FeedbackParallel::FeedbackParallel(){
}

FeedbackParallel::FeedbackParallel(float dry,float length){
    this->dry = dry;
    this->length = length;
}

// Destructor
FeedbackParallel::~FeedbackParallel(){
}

void FeedbackParallel::processSignal(vector<float> & signal, int numSamples){
    // Where we do our effect
    for (int channel = 0; channel < 2; channel++){
    for (int n = 0; n < numSamples ; n++){
        
        int x = signal[n];
        // Feed-back Parallel
        // Step 1: read from buffer to get output
        int y = x + linearGain * delayBuffer[ index[channel] ][channel];
        
        // Step 2: write into buffer our input
        delayBuffer[index[channel]][channel] = y;
        
        // Step 3: move index
        if (index[channel] < delayLengthSamples){
            index[channel]++;
        }else{
            index[channel] = 0;
        }
    }
}
}

void FeedbackParallel::setFs(float Fs){
    this->Fs = Fs;
}

void FeedbackParallel::setDry(float dry){
    if(dry >= 0.f){
        this->dry = dry;
    }
}

void FeedbackParallel::setLength(float length){
    if(length >= 50){
        this->length = length;
    }
}


