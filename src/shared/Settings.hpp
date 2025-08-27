#pragma once

#include "../utils/Enums.hpp"

namespace Settings {
    // why are there so many settings uajesgfhnuisd
    // cuz you made the mod dipshit
    inline bool hideWhenPlaytesting;
    inline bool showClicks;
    inline bool showReleases;
    inline bool p1IndicateHolding;
    inline bool p2IndicateHolding;
    inline bool showClickDirection;
    inline bool showReleaseDirection;
    inline bool p1UseColor;
    inline bool p2UseColor;
    inline IndicatorShape clickShape = IndicatorShape::Square;  // fuck enums im too cool for that
    inline IndicatorShape releaseShape = IndicatorShape::Square; // proceeds to use enums-
    inline float trailTimer;
    inline float p1TrailSize;
    inline float p2TrailSize;
    inline float clickSize;
    inline float releaseSize;
    inline cocos2d::ccColor4F p1TrailCol;
    inline cocos2d::ccColor4F p2TrailCol;
    inline cocos2d::ccColor4F p1HoldTrailCol;
    inline cocos2d::ccColor4F p2HoldTrailCol;
    inline cocos2d::ccColor4F p1ClickColor;
    inline cocos2d::ccColor4F p2ClickColor;
    inline cocos2d::ccColor4F p1ReleaseColor;
    inline cocos2d::ccColor4F p2ReleaseColor;

    void updateSettings();
}