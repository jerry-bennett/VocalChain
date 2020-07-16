/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>

//==============================================================================
VocalChainAudioProcessorEditor::VocalChainAudioProcessorEditor (VocalChainAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), filterGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (650, 300);
    
    addAndMakeVisible(&filterGUI);
    
    //filter slider
    //filterSlider.addListener(this);
    filterSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filterSlider.setBounds(400, 150, 150, 150);
    filterSlider.setRange(500.f, 3000.f, 10);
    //filterSlider.setValue(processor.freqVal);
    filterSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    addAndMakeVisible(filterSlider);
    filterSlider.setLookAndFeel(&otherLookAndFeel);
    
   sliderAttachment.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(processor.state,"FREQ",filterSlider));
    
    //gain slider
    //gainSlider.addListener(this);
    gainSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setBounds(250,150,150,150);
    gainSlider.setRange(0.0f, 2.0f, 0.1f);
    //gainSlider.setValue(processor.gainMultiplier);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    addAndMakeVisible(gainSlider);
    //custom design values
    gainSlider.setLookAndFeel(&otherLookAndFeel);
    
    sliderAttachment.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(processor.state,"GAIN",gainSlider));
    
    //polarity button
//    polarityButton.addListener(this);
//    polarityButton.setBounds(100, 100, 40, 40);
//    addAndMakeVisible(polarityButton);
    
    //feedback delay slider
    //delaySlider.addListener(this);
    delaySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    delaySlider.setBounds(100, 150, 150, 150);
    delaySlider.setRange(200.0f, 1000.0f, 10);
    //delaySlider.setValue(processor.delayLengthMS);
    delaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    addAndMakeVisible(delaySlider);
    delaySlider.setLookAndFeel(&otherLookAndFeel);
    
    sliderAttachment.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(processor.state,"DELAY",delaySlider));
    
    //delay depth slider
//    depthSlider.addListener(this);
//    depthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
//    depthSlider.setBounds(100, 150, 150, 150);
//    depthSlider.setRange(1.0f, 10.0f);
//    depthSlider.setValue(processor.wetVal);
//    depthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
//    addAndMakeVisible(depthSlider);
    
    //delay speed slider
//    rateSlider.addListener(this);
//    rateSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
//    rateSlider.setBounds(0, 150, 150, 150);
//    rateSlider.setRange(0.1f, 10.0f);
//    rateSlider.setValue(processor.rateVal);
//    rateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
//    addAndMakeVisible(rateSlider);
//
    wetSlider.addListener(this);
    wetSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    wetSlider.setBounds(135, 50, 75, 75);
    wetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    wetSlider.setRange(0.f,1.f, 0.1);
    addAndMakeVisible(wetSlider);
    wetSlider.setLookAndFeel(&otherLookAndFeel);
    
    meter.setBounds(600, 175, 20, 100);
    addAndMakeVisible(meter);
    startTimer(60);
    
    meterIn.setBounds(50, 200, 20, 100);
    addAndMakeVisible(meterIn);
    startTimer(60);
    
    //sliderAttachment.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(processor.state,"DRY",wetSlider));
    
}

VocalChainAudioProcessorEditor::~VocalChainAudioProcessorEditor()
{
}

//==============================================================================
void VocalChainAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);

    g.setColour (Colours::yellow);
    g.setFont (25.0f);
    
    //g.drawFittedText ("My First Plug-in", getLocalBounds(), Justification::centred, 1);
    //g.drawFittedText("My First Plugin",20, 20, 400, 100, Justification::centred, 1);
    
//    g.setColour (Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText("Polarity", 110, 105, 60, 30, Justification::centred, 1);
    
    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Gain", 250, 35, 150, 200, Justification::centred, 1);
    
    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Filter Cutoff", 400, 35, 150, 200, Justification::centred, 1);
    
    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Filter Type", 400, -75, 150, 200, Justification::centred, 1);
    
    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Delay Dry/Wet", 100, -75, 150, 200, Justification::centred, 1);
    
    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Delay Lenngth MS", 100, 35, 150, 200, Justification::centred, 1);
    
    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Output", 535, 40, 150, 200, Justification::centred, 1);
}

void VocalChainAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;
    filterGUI.setBounds(area.removeFromRight(componentWidth).removeFromTop(componentHeight));
    //filterGUI.setBounds(375, 25, 200, 200);
    filterGUI.setSize(800, 400);
}

void VocalChainAudioProcessorEditor::sliderValueChanged(Slider *slider) {
    
//    if(slider == &gainSlider){
//        float dB = gainSlider.getValue();
//        //float scaler = pow(10.0f(20.0f/dB));
//
//        //processor.gainMultiplier = gainSlider.getValue();
//    }
//
//    if(slider == &filterSlider){
//        float freq = filterSlider.getValue();
//        processor.freqVal = freq;
//
//    }
//
//    if(slider == &delaySlider){
//        processor.delayLengthMS = delaySlider.getValue();
//    }
    //delay depth
//    if(slider == &depthSlider){
//        processor.depthVal = depthSlider.getValue();
//    }
    //delay rate
//    if(slider == &rateSlider){
//        processor.rateVal = rateSlider.getValue();
//    }
//
    if(slider == &wetSlider){
        processor.dryVal = wetSlider.getValue();
    }
}

void VocalChainAudioProcessorEditor::buttonClicked(Button *button){
    
    if(button == &polarityButton){
        
        processor.polarityMultiplier *= -1.0f;
    }
}

void VocalChainAudioProcessorEditor::timerCallback(){
    meter.update(processor.meterValue);
    meterIn.update(processor.meterValueIn);
}


