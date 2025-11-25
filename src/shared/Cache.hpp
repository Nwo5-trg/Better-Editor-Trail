#pragma once

namespace Cache {
    struct PlayerState {
        bool moving = false;
        bool jump = false;
        bool left = false;
        bool right = false;
        cocos2d::CCPoint pos = ccp(0.0f, 0.0f);
        cocos2d::CCPoint prevPos = ccp(0.0f, 0.0f);
    };

    inline cocos2d::CCLayer* trailLayer = nullptr;

    inline cocos2d::CCDrawNode* trailDraw = nullptr;
    inline cocos2d::CCDrawNode* indicatorDraw = nullptr;

    inline PlayerState playerStates[2];
    inline bool trailRendering = false;

    inline cocos2d::ccColor4F p1TrailCol;
    inline cocos2d::ccColor4F p2TrailCol;
}
