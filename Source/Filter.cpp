/*
  ==============================================================================

    Filter.cpp
    Created: 23 Apr 2020 11:19:21am
    Author:  Jerry Bennett

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(VocalChainAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    filterMenu.addItem("Lowpass", 1);
    filterMenu.addItem("Highpass", 2);
    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);
    filterMenu.addListener(this);
    
    filterSelection = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.state, "filtertype", filterMenu);
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    
}

void Filter::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    
    filterMenu.setBounds(area.removeFromTop(20));

}

void Filter::comboBoxChanged(ComboBox * box){
    
}
