/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Biquad.h"
#include "FractionalDelay.hpp"
#include "FeedbackParallel.hpp"
#include "Series.h"
#include "VUAnalysis.h"


//==============================================================================
/**
*/
class VocalChainAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    VocalChainAudioProcessor();
    ~VocalChainAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorValueTreeState state;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    //float gainMultiplier = 0.5f;
    float polarityMultiplier = 1.0f;
    
    //filter values
    //float freqVal = 500.f;
    //float freqValue;
    float qVal = 2.0f;
    float ampVal = 0.0f;
    
    //fractional delay values
    float depthVal = 5.0f;
    float rateVal = 1.0f;
    //float wetVal = 1.0f;
    
    //feedback delay values
    //float delayLengthMS = 200;
    //float lengthVal = 50.f;
    float dryVal = 0.f;
    float FsVal = 48000.f;
    
    float gainSmooth = 0.0f;
    float gainSmoothIn = 1.0f;
    float alpha = 0.995f;
    
    Biquad::FilterType filterType = Biquad::FilterType::HPF;
    
    std::atomic<float> meterValue;
    std::atomic<float> meterValueIn;
    

private:
    AudioProcessorValueTreeState treeState;
    //VocalChainAudioProcessor& processor;
    
    // Declare variable to use in PluginProcessor
    float inputSample;
    
    Biquad biquad;
    
    FractionalDelay fractionalDelay;
    
    FeedbackParallel feedbackParallel;
    
    Series series;
    
    VUAnalysis vuAnalysis;
    
    float outValue[2] = {0.0f};
    
    float inValue[2] = {0.0f};
    
    foleys::MagicProcessorState magicState { *this, treeState };
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocalChainAudioProcessor)
};
