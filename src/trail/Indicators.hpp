#pragma once
#include "../utils/Enums.hpp"

namespace Trail {
    void createClick(PlayerObject* player, PlayerButton button);
    void createRelease(PlayerObject* player, PlayerButton button);
    void drawIndicator(cocos2d::CCPoint pos, float size, IndicatorShape shape, const cocos2d::ccColor4F& col);
    void drawArrow(cocos2d::CCPoint pos, float size, PlayerButton button, const cocos2d::ccColor4F& col);
    void drawTriangle(cocos2d::CCPoint pos, float size, const cocos2d::ccColor4F& col);
    void drawPrism(cocos2d::CCPoint pos, float size, const cocos2d::ccColor4F& col);
}