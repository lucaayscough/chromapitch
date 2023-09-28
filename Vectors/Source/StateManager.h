#pragma once


class StateManager
{
public:
    StateManager();
    ~StateManager();

    void initState (juce::ValueTree state, juce::UndoManager* undoManager);

    void addEffectNode (juce::Point<int> position);

private:
    juce::ValueTree m_state;
    juce::UndoManager* m_undoManager = nullptr;

    // Type identifiers.
    juce::Identifier rootEffectNodeType = "Root_Effect_Node_Type";
    juce::Identifier effectNodeType = "Effect_Node_Type";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StateManager)
};
