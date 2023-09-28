#pragma once


class StateManager
{
public:
    StateManager();
    ~StateManager();

    void initState (juce::ValueTree state, juce::UndoManager* undoManager);

    juce::ValueTree getRootEffectNode();
    void addEffectNode (juce::Point<int> position);

private:
    juce::ValueTree m_state;
    juce::UndoManager* m_undoManager = nullptr;

public:
    // Type identifiers.
    const juce::Identifier rootEffectNodeType = "root_effect_node_type";
    const juce::Identifier effectNodeType = "effect_node_type";

    // Property identifiers.
    const juce::Identifier posXProp = "pos_x_prop";
    const juce::Identifier posYProp = "pos_y_prop";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StateManager)
};
