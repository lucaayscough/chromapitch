juce_add_plugin(Vectors
    VERSION 0.1.0
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "Chroma Audio"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE 
    IS_MIDI_EFFECT FALSE
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Juce               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Dem0                            # A unique four-character plugin id with exactly one upper-case character
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "Vectors"
    BUNDLE_ID "com.ChromaAudio.Vectors"
)                


juce_generate_juce_header(Vectors)

target_sources(Vectors
    PRIVATE
        StateManager.cpp
        PluginScanner.cpp
        Globals.cpp
        PluginWindow.cpp
        NodeComponent.cpp
        PluginEditor.cpp
        PluginProcessor.cpp
    )

target_compile_definitions(Vectors
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0 
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_PLUGINHOST_AU=1
        JUCE_PLUGINHOST_VST=0
        JUCE_PLUGINHOST_VST3=1)

target_link_libraries(Vectors
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_audio_formats
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
