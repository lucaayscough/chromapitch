#include "Headers.h"


StateManager::StateManager()
{ 
}

StateManager::~StateManager() {}

void StateManager::initState (juce::ValueTree state, juce::UndoManager* undoManager)
{
    m_state = state; 
    m_undoManager = undoManager;

    if (!m_state.getChildWithName(rootEffectNodeType).isValid())
    {
        juce::ValueTree rootEffectNode (rootEffectNodeType);
        m_state.addChild (rootEffectNode, -1, m_undoManager);
    }
}

void StateManager::addEffectNode (juce::Point<int> position)
{
    DBG ("Adding effect node.");
    //m_state.addChild ();

    juce::ValueTree newEffectNode (effectNodeType);
}
