#pragma once

enum class IndicatorShape;

void createClick(PlayerObject* player, PlayerButton button);
void createRelease(PlayerObject* player, PlayerButton button);
void drawIndicator(cocos2d::CCPoint pos, float size, IndicatorShape shape, cocos2d::ccColor4F col);
void drawArrow(cocos2d::CCPoint pos, float size, PlayerButton button, cocos2d::ccColor4F col);
void drawTriangle(cocos2d::CCPoint pos, float size, cocos2d::ccColor4F col);
void drawPrism(cocos2d::CCPoint pos, float size, cocos2d::ccColor4F col);