#include "Headers.h"


PluginWindow::PluginWindow (const juce::String& name, juce::AudioProcessor& processor) : 
    juce::DocumentWindow (name, juce::Colours::black, 7),
    m_processor (processor)
{
    setSize (400, 400);

    if (auto* ui = createProcessorEditor())
    {
        setContentOwned (ui, true);
        setResizable (ui->isResizable(), false);
    }

    setConstrainer (nullptr);

    setVisible (true);
}

PluginWindow::~PluginWindow()
{
    clearContentComponent();
}

juce::AudioProcessorEditor* PluginWindow::createProcessorEditor()
{
    if (m_processor.hasEditor())
    {
        if (auto* ui = m_processor.createEditorIfNeeded())
        {
            return ui;
        }
    }

    // If plugin has no editor return nullptr.
    return nullptr;
}

void PluginWindow::closeButtonPressed()
{
   
}


