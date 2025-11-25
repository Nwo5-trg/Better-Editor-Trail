#pragma once

#include "Enums.hpp"

namespace Utils {
    void drawLine(cocos2d::CCDrawNode* drawNode, const cocos2d::CCPoint& p1, const cocos2d::CCPoint& p2, float thickness, const cocos2d::ccColor4F& col);
    void drawAngle(cocos2d::CCDrawNode* drawNode, const cocos2d::CCPoint& p0, const cocos2d::CCPoint& p1, const cocos2d::CCPoint& p2, float thickness, const cocos2d::ccColor4F& col);
    void getTrailLayer(LevelEditorLayer* editor);
}
