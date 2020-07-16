/*
  ==============================================================================

    Filter.h
    Created: 23 Apr 2020 11:19:21am
    Author:  Jerry Bennett

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component,
                  private ComboBox::Listener
{
public:
    Filter(VocalChainAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox*) override;

private:
    ComboBox filterMenu;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterSelection;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VocalChainAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
