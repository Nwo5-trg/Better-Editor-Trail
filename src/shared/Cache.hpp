#pragma once

namespace Cache {
    inline cocos2d::CCLayer* trailLayer = nullptr;

    inline cocos2d::CCDrawNode* trailDraw = nullptr;
    inline cocos2d::CCDrawNode* indicatorDraw = nullptr;

    /// lowkey why do i have this, wtv idrc
    inline int trailSteps = 0;
    inline bool trailRendering = false;

    inline bool p1Holding = false;
    inline bool p2Holding = false;

    inline cocos2d::ccColor4F p1TrailCol;
    inline cocos2d::ccColor4F p2TrailCol;
}