#pragma once

enum class IndicatorShape {
    Square = 0,
    Circle = 1,
    Triangle = 2,
    Prism = 3
};

namespace BetterTrailVars {
    // inline cocos2d::CCLayer* batchLayer = nullptr;
    inline cocos2d::CCLayer* trailLayer = nullptr;
    inline LevelEditorLayer* editor = nullptr;

    inline cocos2d::CCDrawNode* trailDraw = nullptr;
    inline cocos2d::CCDrawNode* indicatorDraw = nullptr;

    inline int trailSteps = 1;
    inline bool trailRendering = false;

    inline bool p1Holding = false;
    inline bool p2Holding = false;

    // why are there so many settings uajesgfhnuisd
    inline float trailTimer;
    inline float p1TrailSize;
    inline float p2TrailSize;
    inline float clickSize;
    inline float releaseSize;
    inline IndicatorShape clickShape = IndicatorShape::Square;  // fuck enums im too cool for that
    inline IndicatorShape releaseShape = IndicatorShape::Square;
    inline bool hideWhenPlaytesting;
    inline bool showClicks;
    inline bool showReleases;
    inline bool p1IndicateHolding;
    inline bool p2IndicateHolding;
    inline bool showClickDirection;
    inline bool showReleaseDirection;
    inline bool p1UseColor;
    inline bool p2UseColor;
    inline cocos2d::ccColor4F p1TrailCol;
    inline cocos2d::ccColor4F p2TrailCol;
    inline cocos2d::ccColor4F p1HoldTrailCol;
    inline cocos2d::ccColor4F p2HoldTrailCol;
    inline cocos2d::ccColor4F p1ClickColor;
    inline cocos2d::ccColor4F p2ClickColor;
    inline cocos2d::ccColor4F p1ReleaseColor;
    inline cocos2d::ccColor4F p2ReleaseColor;

    void updateSettings();
};