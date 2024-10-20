################################################################################

set(PLUGIN_NAME              ChromaPitch)
set(PLUGIN_VERSION           0.1.2)
set(PLUGIN_MANUFACTURER_CODE Chrm)
set(PLUGIN_CODE              Ptch)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")

################################################################################

cmake_minimum_required(VERSION 3.22)

set(FORMATS "VST3;AU;Standalone" CACHE STRING "Plugin formats for JUCE to build. Valid formats: VST AU AUv3 Standalone")
message("-- Building formats: ${FORMATS}")

project(${PLUGIN_NAME} VERSION ${PLUGIN_VERSION} LANGUAGES C CXX)

add_subdirectory(extern/JUCE)
include_directories(extern/infra/include)
include_directories(extern/q/q_lib/include)

juce_add_plugin(${PLUGIN_NAME}
  COMPANY_NAME "Chroma Audio"
  BUNDLE_ID com.chromaaudio.pitch.
  PLUGIN_MANUFACTURER_CODE ${PLUGIN_MANUFACTURER_CODE}
  PLUGIN_CODE ${PLUGIN_CODE}
  FORMATS ${FORMATS}
  PRODUCT_NAME ${PLUGIN_NAME}
  EDITOR_WANTS_KEYBOARD_FOCUS FALSE
  COPY_PLUGIN_AFTER_BUILD TRUE 
  VST3_CATEGORIES Fx
  AU_MAIN_TYPE kAudioUnitType_Effect
  MICROPHONE_PERMISSION_ENABLED TRUE
  NEEDS_MIDI_INPUT FALSE 
  NEEDS_MIDI_OUTPUT TRUE 
  IS_SYNTH FALSE
  IS_MIDI_EFFECT FALSE
)

juce_generate_juce_header(${PLUGIN_NAME})

juce_add_binary_data(Assets SOURCES
  assets/logo.png
)

target_sources(${PLUGIN_NAME} PRIVATE src/juce_build.cpp)

target_compile_definitions(${PLUGIN_NAME} PUBLIC
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0
  JUCE_VST3_CAN_REPLACE_VST2=0
  JUCE_PLUGINHOST_VST3=1
  JUCE_PLUGINHOST_AU=1)

target_link_libraries(${PLUGIN_NAME} PRIVATE
  Assets
  juce::juce_audio_utils
  juce::juce_audio_devices
  juce::juce_recommended_config_flags # Sets stuff like optimisation level
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags)
