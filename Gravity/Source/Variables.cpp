#include "Headers.h"


// File path variables.
#ifdef _WIN64
    const std::string Variables::ROOT_PATH = "C:/Program Files/Gravity/";
#else
    const std::string Variables::ROOT_PATH = "/Users/lucaayscough/Library/Application Support/Gravity/";
#endif

const std::string Variables::GENERATOR_MODULE_PATH = "Generators/generator_module.pt";
const std::string Variables::MAPPER_MODULE_PATH = "Generators/mapper_module.pt";
const std::string Variables::LOGO_PATH = "Assets/logo_white.png";

// FIle path methods.
std::string Variables::getGeneratorModulePath(){return Variables::ROOT_PATH + Variables::GENERATOR_MODULE_PATH;}
std::string Variables::getMapperModulePath(){return Variables::ROOT_PATH + Variables::MAPPER_MODULE_PATH;}
std::string Variables::getLogoPath(){return Variables::ROOT_PATH + Variables::LOGO_PATH;}

// Window variables.
const int Variables::WINDOW_WIDTH = 1080;
const int Variables::WINDOW_HEIGHT = 610;
const bool Variables::IS_WIDTH_RESIZABLE = false;
const bool Variables::IS_HEIGHT_RESIZABLE = false;

// Editor variables.
const juce::Colour Variables::EDITOR_BG_COLOUR = juce::Colour(46, 48, 53);
const int Variables::LEFT_BAR = 140;
const int Variables::TOP_BAR = 35;
const int Variables::MAP_TRIM = 8;

// Top bar variables.
const juce::Colour Variables::TOP_BAR_SHADOW_COLOUR = juce::Colour(16, 16, 16);

// Left bar variables.
const int Variables::LEFT_BAR_TOP_BOUNDARY = 20;
const int Variables::LEFT_BAR_BOTTOM_BOUNDARY = 20;
const int Variables::LEFT_BAR_MAP_BOUNDARY = 10;

// MapButton variables.
const juce::Colour Variables::MAP_BUTTON_BG_COLOUR_1 = juce::Colour(39, 40, 46);
const juce::Colour Variables::MAP_BUTTON_BG_COLOUR_2 = juce::Colour(0, 0, 0);

// Map variables.
const int Variables::NUM_MAPS = 8;
const int Variables::MAX_NUM_PLANETS = 20;
const juce::Colour Variables::MAP_BG_COLOUR = juce::Colour(37, 38, 43);
const juce::Colour Variables::MAP_CIRCLE_COLOUR = juce::Colour(86, 87, 90);
const float Variables::FORCE_VECTOR_SIZE = 1.0f;

// Astro animator variables.
const int Variables::ANIMATION_INTERVAL = 30;
const float Variables::CREATION_AREA_SHIFT = 100.0f;
const float Variables::AREA_SHIFT_LIMIT = 150.0f;
const float Variables::AREA_SHIFT = 10.0f;
const float Variables::DISTANCE_BOUNDARY = 20.0f;

// Planet variables.
const float Variables::DEFAULT_PLANET_AREA = 1200.0f;
const float Variables::MAX_PLANET_AREA = 3000.0f;
const float Variables::MIN_PLANET_AREA = 500.0f;
const float Variables::AREA_MODIFIER = 100.0f;
const int Variables::CLIP_BOUNDARY = 100;

// Planet methods.
int Variables::getDefaultPlanetDiameter(){return (int)(round((sqrt(DEFAULT_PLANET_AREA / 3.1415f) * 2.0f) / 2.0f) * 2.0f);}
int Variables::getDefaultPlanetDiameterWithClipBoundary(){return getDefaultPlanetDiameter() + CLIP_BOUNDARY;}
int Variables::getDefaultPlanetRadius(){return getDefaultPlanetDiameter() / 2;}
int Variables::getDefaultPlanetRadiusWithClipBoundary(){return getDefaultPlanetDiameter() / 2 + CLIP_BOUNDARY / 2;}

// Sun variables.
const float Variables::SUN_AREA = 2000.0f;

// Other.
const float Variables::PI = 3.1415f;
