/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
using namespace std;

//==============================================================================
VocalChainAudioProcessor::VocalChainAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),state(*this,nullptr,Identifier("ChainParameters"),createParameterLayout()),
                        treeState(*this, nullptr, ProjectInfo::projectName, createParameterLayout())
#endif
{
    NormalisableRange<float> filterTypeParam(0,2);
    state.createAndAddParameter("filtertype", "FilterType", "filterType", filterTypeParam, 0, nullptr, nullptr);
}

VocalChainAudioProcessor::~VocalChainAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout VocalChainAudioProcessor::createParameterLayout(){
    
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<AudioParameterInt>("FREQ","Freq",500,3000,10));
    params.push_back(std::make_unique<AudioParameterFloat>("GAIN","Gain",0.f,2.f,1.f));
    params.push_back(std::make_unique<AudioParameterInt>("DELAY","Delay",200,1000,10));
    
    return {params.begin() , params.end()};
}

//==============================================================================
const String VocalChainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VocalChainAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VocalChainAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VocalChainAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VocalChainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VocalChainAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VocalChainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VocalChainAudioProcessor::setCurrentProgram (int index)
{
}

const String VocalChainAudioProcessor::getProgramName (int index)
{
    return {};
}

void VocalChainAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VocalChainAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    float Fs;
    Fs = 48000.0f;
    vuAnalysis.setSampleRate(Fs);
}

void VocalChainAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VocalChainAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VocalChainAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumInputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
//    biquad.setFreq(freqValue);
    
    //delay values
//    fractionalDelay.setDelaySamples(depthVal);
//    fractionalDelay.setSpeed(rateVal);
//    fractionalDelay.setDepth(wetVal);
    
    //feedback delay values
    //feedbackParallel.setDry(dryVal);
    feedbackParallel.setFs(FsVal);
    
    //series delay values
    
    float gainValue = *state.getRawParameterValue("GAIN");
    float freqValue = *state.getRawParameterValue("FREQ");
    float delayValue = *state.getRawParameterValue("DELAY");
    //float dryValue = *state.getRawParameterValue("DRY");
    feedbackParallel.setDry(dryVal);
    biquad.setFreq(freqValue);
    biquad.setQ(qVal);
    biquad.setAmpdB(ampVal);
    //biquad.setFilterType(filterType);
    biquad.getFilterType(state.getRawParameterValue("filtertype"));
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        for (int n = 0; n < buffer.getNumSamples(); n++){
            // Read one sample at a time
            inputSample = buffer.getReadPointer(channel)[n];
            
            //filter values
            float x = buffer.getWritePointer(channel)[n];
            float y = biquad.processSample(x, channel);
            
            //fractional delay values
            fractionalDelay.setDepth(depthVal);
            fractionalDelay.setSpeed(rateVal);
            
            //feedback delay values
            feedbackParallel.setLength(delayValue);
            
            //series.setDry(dryValue);
            //series.setLength(delayValue);
            //float delaySample = fractionalDelay.processSample(y, channel);
            
            //float out2 = series.processSample(x, channel);
            
            float out = feedbackParallel.processSample(y, channel);
            float z = (1.f - dryVal) * y + dryVal * (out);
            
            // Write one sample to the output
            gainSmooth = (1.f-alpha) * gainValue + alpha*gainSmooth;
            float in = x * gainSmoothIn;
            float out2 = z * gainSmooth;
            
            outValue[channel] = vuAnalysis.processSample(out2, channel);
            inValue[channel] = vuAnalysis.processSample(in, channel);
            
            buffer.getWritePointer(channel)[n] = out2;
            
            //inValue[channel] = vuAnalysis.processSample(x, channel);
            
            
        }
    }
    meterValue = jmax(outValue[0], outValue[1]);
    meterValueIn = jmax(inValue[0], inValue[1]);
}


//==============================================================================
bool VocalChainAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VocalChainAudioProcessor::createEditor()
{
    return new foleys::MagicPluginEditor (magicState);
}

//==============================================================================
void VocalChainAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto currentState = state.copyState();
    std::unique_ptr<XmlElement> xml(currentState.createXml());
    copyXmlToBinary(*xml, destData);
}

void VocalChainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if(xmlState &&xmlState->hasTagName(state.state.getType())){
        state.replaceState(ValueTree::fromXml(*xmlState));
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VocalChainAudioProcessor();
}
