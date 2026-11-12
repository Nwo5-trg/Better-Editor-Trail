#pragma once

#include <nwo5.silly-api/cache/include.hpp>

using namespace nwo5::cache::prelude;

namespace settings {
    inline SettingCache<bool> enabled{"general-enabled"};
    inline SettingCache<bool> settingsButtonEnabled{"general-settings-button"};
    inline SettingCache<bool> scaleWithZoom{"general-scale-with-zoom"};
    inline SettingCache<bool> focusPlayer2{"general-focus-player-2"};

    inline SettingCache<bool> showHolding{"trail-show-holding"};
    inline SettingCache<bool> hideInPlaytest{"trail-hide-in-playtest"};
    inline SettingCache<std::string> updateMethod{"trail-update-method"};

    inline SettingCache<float> p1TrailSize{"p1-trail-size"};
    inline SettingCache<cocos2d::ccColor4B> p1TrailColor{"p1-trail-color"};
    inline SettingCache<cocos2d::ccColor4B> p1TrailHoldColor{"p1-trail-hold-color"};

    inline SettingCache<float> p2TrailSize{"p2-trail-size"};
    inline SettingCache<cocos2d::ccColor4B> p2TrailColor{"p2-trail-color"};
    inline SettingCache<cocos2d::ccColor4B> p2TrailHoldColor{"p2-trail-hold-color"};

    inline SettingCache<bool> indicatorsEnabled{"indicators-enabled"};
    inline SettingCache<bool> showReleases{"indicators-show-releases"};
    inline SettingCache<bool> spiderFix{"indicators-spider-fix"};
    inline SettingCache<bool> botFix{"indicators-bot-fix"};
    inline SettingCache<bool> directionalIndicators{"indicators-directional-indicators"};
    inline SettingCache<float> directionalIndicatorScale{"indicators-directional-indicator-scale"};

    inline SettingCache<float> p1ClickSize{"p1-indicators-click-size"};
    inline SettingCache<cocos2d::ccColor4B> p1ClickColor{"p1-indicators-click-color"};
    inline SettingCache<std::string> p1ClickShape{"p1-indicators-click-shape"};
    inline SettingCache<float> p1ReleaseSize{"p1-indicators-release-size"};
    inline SettingCache<cocos2d::ccColor4B> p1ReleaseColor{"p1-indicators-release-color"};
    inline SettingCache<std::string> p1ReleaseShape{"p1-indicators-release-shape"};

    inline SettingCache<float> p2ClickSize{"p2-indicators-click-size"};
    inline SettingCache<cocos2d::ccColor4B> p2ClickColor{"p2-indicators-click-color"};
    inline SettingCache<std::string> p2ClickShape{"p2-indicators-click-shape"};
    inline SettingCache<float> p2ReleaseSize{"p2-indicators-release-size"};
    inline SettingCache<cocos2d::ccColor4B> p2ReleaseColor{"p2-indicators-release-color"};
    inline SettingCache<std::string> p2ReleaseShape{"p2-indicators-release-shape"};

    inline SettingCache<bool> hitboxesEnabled{"hitboxes-enabled"};
    inline SettingCache<bool> showInnerHitbox{"hitboxes-inner-hitbox"};
    inline SettingCache<bool> dontScaleHitboxesWithZoom{"hitboxes-dont-scale-with-zoom"};
    inline SettingCache<bool> syncShowHitboxes{"hitboxes-sync-show-hitboxes"};

    inline SettingCache<float> p1HitboxesThickness{"p1-hitboxes-thickness"};
    inline SettingCache<cocos2d::ccColor4B> p1HitboxesColor{"p1-hitboxes-color"};
    inline SettingCache<float> p1HitboxesFillOpacity{"p1-hitboxes-fill-opacity"};
    inline SettingCache<float> p1HitboxesInnerThickness{"p1-hitboxes-inner-thickness"};
    inline SettingCache<cocos2d::ccColor4B> p1HitboxesInnerColor{"p1-hitboxes-inner-color"};
    inline SettingCache<float> p1HitboxesInnerFillOpacity{"p1-hitboxes-inner-fill-opacity"};

    inline SettingCache<float> p2HitboxesThickness{"p2-hitboxes-thickness"};
    inline SettingCache<cocos2d::ccColor4B> p2HitboxesColor{"p2-hitboxes-color"};
    inline SettingCache<float> p2HitboxesFillOpacity{"p2-hitboxes-fill-opacity"};
    inline SettingCache<float> p2HitboxesInnerThickness{"p1-hitboxes-inner-thickness"};
    inline SettingCache<cocos2d::ccColor4B> p2HitboxesInnerColor{"p2-hitboxes-inner-color"};
    inline SettingCache<float> p2HitboxesInnerFillOpacity{"p2-hitboxes-inner-fill-opacity"};

    inline SettingCache<bool> chroma{"extra-chroma"};
    inline SettingCache<float> chromaSpeed{"extra-chroma-speed"};
    inline SettingCache<float> chromaSaturation{"extra-chroma-saturation"};
}