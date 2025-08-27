#include "Indicators.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

namespace Trail {
    void createClick(PlayerObject* player, PlayerButton button) {
        if (!Settings::showClicks || !Cache::trailRendering) return;

        auto col = player->m_isSecondPlayer ? Settings::p2ClickColor : Settings::p1ClickColor;

        if (Settings::showClickDirection && player->m_isPlatformer) {
            drawArrow(player->getPosition(), Settings::clickSize, button, col);
        }
        else {
            drawIndicator(player->getPosition(), Settings::clickSize, Settings::clickShape, col);
        }
    }

    void createRelease(PlayerObject* player, PlayerButton button) {
        if (!Settings::showReleases || !Cache::trailRendering) return;

        auto col = player->m_isSecondPlayer ? Settings::p2ReleaseColor : Settings::p1ReleaseColor;

        if (Settings::showReleaseDirection && player->m_isPlatformer) {
            drawArrow(player->getPosition(), Settings::releaseSize, button, col);
        }
        else {
            drawIndicator(player->getPosition(), Settings::releaseSize, Settings::releaseShape, col);
        }
    }

    void drawIndicator(CCPoint pos, float size, IndicatorShape shape, const ccColor4F& col) {
        switch (shape) {
            case IndicatorShape::Square: {
                Cache::indicatorDraw->drawDot(pos, size, col);
                break;
            }
            case IndicatorShape::Circle: {
                Cache::indicatorDraw->drawCircle(pos, size, col, 0, col, 30);
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

    void drawArrow(CCPoint pos, float size, PlayerButton button, const ccColor4F& col) {
        float half = size / 2;
        float offset = size * 1.5f;
        float tip = offset * 2;

        switch (button) {
            case PlayerButton::Jump: {
                Utils::drawLine(Cache::indicatorDraw, {pos.x, pos.y - offset}, {pos.x, pos.y + offset}, half, col);
                Utils::drawLine(Cache::indicatorDraw, {pos.x, pos.y + offset}, {pos.x + offset, pos.y}, half, col);
                Utils::drawLine(Cache::indicatorDraw, {pos.x, pos.y + offset}, {pos.x - offset, pos.y}, half, col);
                break;
            }
            case PlayerButton::Right: {
                Utils::drawLine(Cache::indicatorDraw, pos, {pos.x + tip, pos.y}, half, col);
                Utils::drawLine(Cache::indicatorDraw, {pos.x + tip, pos.y}, {pos.x + offset, pos.y + offset}, half, col);
                Utils::drawLine(Cache::indicatorDraw, {pos.x + tip, pos.y}, {pos.x + offset, pos.y - offset}, half, col);
                break;
            }
            case PlayerButton::Left: {
                Utils::drawLine(Cache::indicatorDraw, pos, {pos.x - tip, pos.y}, half, col);
                Utils::drawLine(Cache::indicatorDraw, {pos.x - tip, pos.y}, {pos.x - offset, pos.y + offset}, half, col);
                Utils::drawLine(Cache::indicatorDraw, {pos.x - tip, pos.y}, {pos.x - offset, pos.y - offset}, half, col);
                break;
            }
        }
    }

    void drawTriangle(CCPoint pos, float size, const ccColor4F& col) {
        CCPoint polygon[] = {
            {pos.x - size, pos.y - size},
            {pos.x + size, pos.y - size},
            {pos.x, pos.y + size}
        };

        Cache::indicatorDraw->drawPolygon(polygon, 3, col, 0.0f, col);
    }

    void drawPrism(CCPoint pos, float size, const ccColor4F& col) {
        auto halfSize = size / 2;

        CCPoint polygon[] = {
            {pos.x, pos.y + size},
            {pos.x + halfSize, pos.y},
            {pos.x, pos.y - size},
            {pos.x - halfSize, pos.y}
        };

        Cache::indicatorDraw->drawPolygon(polygon, 4, col, 0.0f, col);
    }
}