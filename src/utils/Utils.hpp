#pragma once

#include "Enums.hpp"

namespace Utils {
    void drawLine(cocos2d::CCDrawNode* drawNode, cocos2d::CCPoint p1, cocos2d::CCPoint p2, float thickness, cocos2d::ccColor4F col);
    void getTrailLayer(LevelEditorLayer* editor);
}