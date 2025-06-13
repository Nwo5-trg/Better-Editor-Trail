#include "Indicators.hpp"
#include "Variables.hpp"

using namespace geode::prelude;

void createClick(PlayerObject* player, PlayerButton button) {
    if (!BetterTrailVars::showClicks || !BetterTrailVars::trailRendering) return;
    auto col = player->m_isSecondPlayer ? BetterTrailVars::p2ClickColor : BetterTrailVars::p1ClickColor;
    auto pos = player->getPosition();
    if (BetterTrailVars::showClickDirection && player->m_isPlatformer) drawArrow(pos, BetterTrailVars::clickSize, button, col);
    else drawIndicator(pos, BetterTrailVars::clickSize, BetterTrailVars::clickShape, col);
}

void createRelease(PlayerObject* player, PlayerButton button) {
    if (!BetterTrailVars::showReleases || !BetterTrailVars::trailRendering) return;
    auto col = player->m_isSecondPlayer ? BetterTrailVars::p2ReleaseColor : BetterTrailVars::p1ReleaseColor;
    auto pos = player->getPosition();
    if (BetterTrailVars::showReleaseDirection && player->m_isPlatformer) drawArrow(pos, BetterTrailVars::releaseSize, button, col);
    else drawIndicator(pos, BetterTrailVars::releaseSize, BetterTrailVars::releaseShape, col);
}

void drawIndicator(CCPoint pos, float size, IndicatorShape shape, ccColor4F col) {
    switch (shape) {
        case IndicatorShape::Square: {
            BetterTrailVars::indicatorDraw->drawDot(pos, size, col);
            break;
        }
        case IndicatorShape::Circle: {
            BetterTrailVars::indicatorDraw->drawCircle(pos, size, col, 0, col, 30);
            break;
        } 
         case IndicatorShape::Triangle: {
            drawTriangle(pos, size, col);
            break;
        } 
         case IndicatorShape::Prism: {
            drawPrism(pos, size, col);
            break;
        } 
    }
}

void drawArrow(CCPoint pos, float size, PlayerButton button, ccColor4F col) {
    auto half = size / 2;
    auto offset = size * 1.5f;
    auto tip = offset * 2;

    switch (button) {
        case PlayerButton::Jump: {
            BetterTrailVars::indicatorDraw->drawSegment(ccp(pos.x, pos.y - offset), ccp(pos.x, pos.y + offset), half, col);
            BetterTrailVars::indicatorDraw->drawSegment(ccp(pos.x, pos.y + offset), ccp(pos.x + offset, pos.y), half, col);
            BetterTrailVars::indicatorDraw->drawSegment(ccp(pos.x, pos.y + offset), ccp(pos.x - offset, pos.y), half, col);
            break;
        }
        case PlayerButton::Right: {
            BetterTrailVars::indicatorDraw->drawSegment(pos, ccp(pos.x + tip, pos.y), half, col);
            BetterTrailVars::indicatorDraw->drawSegment(ccp(pos.x + tip, pos.y), ccp(pos.x + offset, pos.y + offset), half, col);
            BetterTrailVars::indicatorDraw->drawSegment(ccp(pos.x + tip, pos.y), ccp(pos.x + offset, pos.y - offset), half, col);
            break;
        }
        case PlayerButton::Left: {
            BetterTrailVars::indicatorDraw->drawSegment(pos, ccp(pos.x - tip, pos.y), half, col);
            BetterTrailVars::indicatorDraw->drawSegment(ccp(pos.x - tip, pos.y), ccp(pos.x - offset, pos.y + offset), half, col);
            BetterTrailVars::indicatorDraw->drawSegment(ccp(pos.x - tip, pos.y), ccp(pos.x - offset, pos.y - offset), half, col);
            break;
        }
    }
}

void drawTriangle(CCPoint pos, float size, ccColor4F col) {
    CCPoint polygon[3] = {
        ccp(pos.x - size, pos.y - size),
        ccp(pos.x + size, pos.y - size),
        ccp(pos.x, pos.y + size)
    };

    BetterTrailVars::indicatorDraw->drawPolygon(polygon, 3, col, 0.0f, col);
}

void drawPrism(CCPoint pos, float size, ccColor4F col) {
    auto halfSize = size / 2;

    CCPoint polygon[4] = {
        ccp(pos.x, pos.y + size),
        ccp(pos.x + halfSize, pos.y),
        ccp(pos.x, pos.y - size),
        ccp(pos.x - halfSize, pos.y)
    };

    BetterTrailVars::indicatorDraw->drawPolygon(polygon, 4, col, 0.0f, col);
}
