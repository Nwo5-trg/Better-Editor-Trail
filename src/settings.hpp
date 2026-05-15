#pragma once

#include <nwo5.silly-api/include/settings/include.hpp>

using namespace nwo5::settings::prelude;

namespace Settings {
    inline Setting<bool> enabled{"general-enabled"};
    inline Setting<bool> settingsButtonEnabled{"general-settings-button"};
    inline Setting<bool> scaleWithZoom{"general-scale-with-zoom"};
    inline Setting<bool> focusPlayer2{"general-focus-player-2"};

    inline Setting<bool> showHolding{"trail-show-holding"};
    inline Setting<bool> hideInPlaytest{"trail-hide-in-playtest"};
    inline Setting<std::string> updateMethod{"trail-update-method"};

    inline Setting<float> p1TrailSize{"p1-trail-size"};
    inline Setting<cocos2d::ccColor4B> p1TrailColor{"p1-trail-color"};
    inline Setting<cocos2d::ccColor4B> p1TrailHoldColor{"p1-trail-hold-color"};

    inline Setting<float> p2TrailSize{"p2-trail-size"};
    inline Setting<cocos2d::ccColor4B> p2TrailColor{"p2-trail-color"};
    inline Setting<cocos2d::ccColor4B> p2TrailHoldColor{"p2-trail-hold-color"};

    inline Setting<bool> indicatorsEnabled{"indicators-enabled"};
    inline Setting<bool> showReleases{"indicators-show-releases"};
    inline Setting<bool> spiderFix{"indicators-spider-fix"};

    inline Setting<float> p1ClickSize{"p1-indicators-click-size"};
    inline Setting<cocos2d::ccColor4B> p1ClickColor{"p1-indicators-click-color"};
    inline Setting<std::string> p1ClickShape{"p1-indicators-click-shape"};
    inline Setting<float> p1ReleaseSize{"p1-indicators-release-size"};
    inline Setting<cocos2d::ccColor4B> p1ReleaseColor{"p1-indicators-release-color"};
    inline Setting<std::string> p1ReleaseShape{"p1-indicators-release-shape"};

    inline Setting<float> p2ClickSize{"p2-indicators-click-size"};
    inline Setting<cocos2d::ccColor4B> p2ClickColor{"p2-indicators-click-color"};
    inline Setting<std::string> p2ClickShape{"p2-indicators-click-shape"};
    inline Setting<float> p2ReleaseSize{"p2-indicators-release-size"};
    inline Setting<cocos2d::ccColor4B> p2ReleaseColor{"p2-indicators-release-color"};
    inline Setting<std::string> p2ReleaseShape{"p2-indicators-release-shape"};

    inline Setting<bool> hitboxesEnabled{"hitboxes-enabled"};
    inline Setting<bool> showInnerHitbox{"hitboxes-inner-hitbox"};
    inline Setting<bool> dontScaleHitboxesWithZoom{"hitboxes-dont-scale-with-zoom"};
    inline Setting<bool> syncShowHitboxes{"hitboxes-sync-show-hitboxes"};

    inline Setting<float> p1HitboxesThickness{"p1-hitboxes-thickness"};
    inline Setting<cocos2d::ccColor4B> p1HitboxesColor{"p1-hitboxes-color"};
    inline Setting<float> p1HitboxesFillOpacity{"p1-hitboxes-fill-opacity"};
    inline Setting<float> p1HitboxesInnerThickness{"p1-hitboxes-inner-thickness"};
    inline Setting<cocos2d::ccColor4B> p1HitboxesInnerColor{"p1-hitboxes-inner-color"};
    inline Setting<float> p1HitboxesInnerFillOpacity{"p1-hitboxes-inner-fill-opacity"};

    inline Setting<float> p2HitboxesThickness{"p2-hitboxes-thickness"};
    inline Setting<cocos2d::ccColor4B> p2HitboxesColor{"p2-hitboxes-color"};
    inline Setting<float> p2HitboxesFillOpacity{"p2-hitboxes-fill-opacity"};
    inline Setting<float> p2HitboxesInnerThickness{"p1-hitboxes-inner-thickness"};
    inline Setting<cocos2d::ccColor4B> p2HitboxesInnerColor{"p2-hitboxes-inner-color"};
    inline Setting<float> p2HitboxesInnerFillOpacity{"p2-hitboxes-inner-fill-opacity"};

    inline Setting<bool> chroma{"extra-chroma"};
    inline Setting<float> chromaSpeed{"extra-chroma-speed"};
    inline Setting<float> chromaSaturation{"extra-chroma-saturation"};
}