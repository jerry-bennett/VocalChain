//
//  FeedbackParallel.hpp
//  VocalChain
//
//  Created by Jerry Bennett on 4/18/20.
//

#ifndef FeedbackParallel_hpp
#define FeedbackParallel_hpp

#include <stdio.h>



#include <cmath>
#include <vector>
using namespace std;

class FeedbackParallel {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    FeedbackParallel();
    
    FeedbackParallel(float dry, float length);
    
    // Destructor
    ~FeedbackParallel();
    
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

#endif /* FeedbackParallel_hpp */
