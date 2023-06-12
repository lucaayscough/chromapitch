juce_add_plugin(ChromaPitch
    VERSION 0.1.1
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "Chroma Audio"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT TRUE
    IS_MIDI_EFFECT FALSE
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Juce               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Dem0                            # A unique four-character plugin id with exactly one upper-case character
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "Chroma Pitch"
    MICROPHONE_PERMISSION_ENABLED TRUE
)                


juce_generate_juce_header(ChromaPitch)

target_sources(ChromaPitch
    PRIVATE
        FrequencyEstimator.cpp
        Header.cpp
        MPE.cpp
        NoteBox.cpp
        PitchLine.cpp
        PluginEditor.cpp
        PluginProcessor.cpp
        Variables.cpp
        View.cpp
        YIN.cpp
    )

target_compile_definitions(ChromaPitch
    PUBLIC
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)


juce_add_binary_data(logo_png SOURCES ../Assets/logo.png)


target_link_libraries(ChromaPitch
    PRIVATE
        logo_png
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
