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
    inline bool hideTrail = false;

    inline bool p1Holding = false;
    inline bool p2Holding = false;

    // why are there so many settings uajesgfhnuisd
    inline float p1TrailSize = 1.0f;
    inline float p2TrailSize = 1.0f;
    inline float clickSize;
    inline float releaseSize;
    inline IndicatorShape clickShape = IndicatorShape::Square;  // fuck enums im too cool for that
    inline IndicatorShape releaseShape = IndicatorShape::Square;
    inline bool showClicks = false;
    inline bool showReleases = false;
    inline bool p1IndicateHolding = false;
    inline bool p2IndicateHolding = false;
    inline bool showClickDirection = false;
    inline bool showReleaseDirection = false;
    inline cocos2d::ccColor4F p1TrailCol = cocos2d::ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
    inline cocos2d::ccColor4F p2TrailCol = cocos2d::ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
    inline cocos2d::ccColor4F p1HoldTrailCol = cocos2d::ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
    inline cocos2d::ccColor4F p2HoldTrailCol = cocos2d::ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
    inline cocos2d::ccColor4F p1ClickColor = cocos2d::ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
    inline cocos2d::ccColor4F p2ClickColor = cocos2d::ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
    inline cocos2d::ccColor4F p1ReleaseColor = cocos2d::ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
    inline cocos2d::ccColor4F p2ReleaseColor = cocos2d::ccc4f(1.0f, 1.0f, 1.0f, 1.0f);

    void updateSettings();
};