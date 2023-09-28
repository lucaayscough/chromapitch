#include "Headers.h"


StateManager::StateManager() {}

StateManager::~StateManager() {}

void StateManager::initState (juce::ValueTree state, juce::UndoManager* undoManager)
{
    m_state = state; 
    m_undoManager = undoManager;

    if (!m_state.getChildWithName (rootEffectNodeType).isValid())
    {
        juce::ValueTree rootEffectNode (rootEffectNodeType);
        m_state.addChild (rootEffectNode, -1, m_undoManager);
    }
}

juce::ValueTree StateManager::getRootEffectNode()
{
    return m_state.getChildWithName (rootEffectNodeType); 
} 

void StateManager::addEffectNode (juce::Point<int> position)
{
    DBG ("Adding effect node.");

    juce::ValueTree newEffectNode (effectNodeType);
    newEffectNode.setProperty (posXProp, position.getX(), m_undoManager);
    newEffectNode.setProperty (posYProp, position.getY(), m_undoManager);

    m_state.getChildWithName(rootEffectNodeType).addChild (newEffectNode, -1, m_undoManager);
}
