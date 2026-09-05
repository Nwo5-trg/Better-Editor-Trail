#include "trail.hpp"
#include <settings.hpp>

using namespace geode::prelude;

namespace bettereditortrail {
    bool EditorTrail::init() {
        if (!CCNode::init()) {
            return false;
        }

        m_draw = Setup(SillyDrawNode::create())
            .id("draw-node"_spr)
            .pos(CCPointZero)
            .parent(this);

        reset();

        return true;
    }

    void EditorTrail::drawHitboxes(const cocos2d::CCRect& pView) {
        const auto zoomMult = settings::scaleWithZoom && !settings::dontScaleHitboxesWithZoom ? editor::zoom() : 1.0f;

        for (auto player2 : {!settings::focusPlayer2.get(), settings::focusPlayer2.get()}) {
            const auto& state = player2 ? m_player2State : m_player1State;

            const auto thickness = (player2 ? settings::p2HitboxesThickness.get() : settings::p1HitboxesThickness.get()) / zoomMult;
            const auto col = color_cast<ccColor4F>(player2 ? settings::p2HitboxesColor.get() : settings::p1HitboxesColor.get());
            const ccColor4F fill{col.r, col.g, col.b, player2 ? settings::p2HitboxesFillOpacity.get() : settings::p1HitboxesFillOpacity.get()};
            const auto innerThickness = (player2 ? settings::p2HitboxesInnerThickness.get() : settings::p1HitboxesInnerThickness.get()) / zoomMult;
            const auto innerCol = color_cast<ccColor4F>(player2 ? settings::p2HitboxesInnerColor.get() : settings::p1HitboxesInnerColor.get());
            const ccColor4F innerFill{innerCol.r, innerCol.g, innerCol.b, player2 ? settings::p2HitboxesInnerFillOpacity.get() : settings::p1HitboxesInnerFillOpacity.get()};

            for (const auto& point : state.hitbox) {
                if (!pView.containsPoint(point.hitbox.origin)) {
                    continue;
                }

                m_draw->drawRect(
                    point.hitbox, fill, thickness, col
                );
            }

            if (settings::showInnerHitbox) {
                for (const auto& point : state.hitbox) {
                    if (pView.containsPoint(point.hitbox.origin)) {
                        m_draw->drawRect(
                            point.innerHitbox, innerFill, innerThickness, innerCol
                        );
                    }
                }
            }
        }
    }
    void EditorTrail::drawTrail(const cocos2d::CCRect& pView) {
        const auto zoomMult = settings::scaleWithZoom ? editor::zoom() : 1.0f;

        for (auto player2 : {!settings::focusPlayer2.get(), settings::focusPlayer2.get()}) {
            const auto& state = player2 ? m_player2State : m_player1State;

            const auto col = color_cast<ccColor4F>(player2 ? settings::p2TrailColor.get() : settings::p1TrailColor);
            const auto holdCol = settings::showHolding ? color_cast<ccColor4F>(player2 ? settings::p2TrailHoldColor.get() : settings::p1TrailHoldColor) : col;
            const auto size = (player2 ? settings::p2TrailSize.get() : settings::p1TrailSize.get()) / zoomMult;

            std::optional<CCPoint> segmentStart = std::nullopt;

            for (const auto& point : state.points) {
                if (!segmentStart.has_value() || point.start) {
                    segmentStart = point.pos;

                    continue;
                }

                if (pView.containsPoint(point.pos) || pView.containsPoint(segmentStart.value())) {
                    m_draw->drawSegment(
                        segmentStart.value(), point.pos,
                        size, point.holding ? holdCol : col
                    );
                }

                segmentStart = point.pos;
            }
        }
    }
    void EditorTrail::drawIndicators(const cocos2d::CCRect& pView) {
        const auto zoomMult = settings::scaleWithZoom ? editor::zoom() : 1.0f;

        for (auto player2 : {!settings::focusPlayer2.get(), settings::focusPlayer2.get()}) {
            const auto& state = player2 ? m_player2State : m_player1State;

            const auto clickSize = (player2 ? settings::p2ClickSize.get() : settings::p1ClickSize.get()) / zoomMult;
            const auto clickCol = color_cast<ccColor4F>(player2 ? settings::p2ClickColor.get() : settings::p1ClickColor);
            const auto clickShape = bettereditortrail::indicatorShapeFromString(player2 ? settings::p2ClickShape.get() : settings::p1ClickShape.get());
            const auto releaseSize = (player2 ? settings::p2ReleaseSize.get() : settings::p1ReleaseSize.get()) / zoomMult;
            const auto releaseCol = color_cast<ccColor4F>(player2 ? settings::p2ReleaseColor.get() : settings::p1ReleaseColor);
            const auto releaseShape = bettereditortrail::indicatorShapeFromString(player2 ? settings::p2ReleaseShape.get() : settings::p1ReleaseShape.get());

            for (const auto& point : state.inputs) {
                if (!pView.containsPoint(point.pos)) {
                    continue;
                }

                const auto& col = point.release ? releaseCol : clickCol;
                const auto size = point.release ? releaseSize : clickSize;

                if (point.type == InputType::Normal || !settings::directionalIndicators) {
                    switch (point.release ? releaseShape : clickShape) {
                        case IndicatorShape::Square: {
                            m_draw->drawDot(point.pos, size, col);
                        break; }
                        case IndicatorShape::Circle: {
                            m_draw->drawCircle(point.pos, size, col, 25);
                        break; }
                        case IndicatorShape::Triangle: {
                            drawTriangle(point.pos, size, col);
                        break; }
                        case IndicatorShape::Prism: {
                            drawPrism(point.pos, size, col);
                        break; }
                    }
                }
                else {
                    drawArrow(point.pos, size, point.type, col);
                }
            }
        }
    }

    void EditorTrail::drawArrow(const cocos2d::CCPoint& pPos, float pSize, InputType pType, const cocos2d::ccColor4F& pCol) {
        const auto half = pSize * 0.5f * std::sqrt(2.0f) * 0.5f;
        const auto offset = pSize * 1.5f;
        const auto tip = offset * 2;

        switch (pType) {
            case InputType::Up: {
                m_draw->drawSegment({pPos.x, pPos.y - offset}, {pPos.x, pPos.y + offset}, pSize, pCol);
                m_draw->drawSegment({pPos.x - half, pPos.y + offset + half}, {pPos.x + offset, pPos.y}, pSize, pCol);
                m_draw->drawSegment({pPos.x + half, pPos.y + offset + half}, {pPos.x - offset, pPos.y}, pSize, pCol);
            break; }
            case InputType::Right: {
                m_draw->drawSegment(pPos, {pPos.x + tip, pPos.y}, pSize, pCol);
                m_draw->drawSegment({pPos.x + tip + half, pPos.y - half}, {pPos.x + offset, pPos.y + offset}, pSize, pCol);
                m_draw->drawSegment({pPos.x + tip + half, pPos.y + half}, {pPos.x + offset, pPos.y - offset}, pSize, pCol);
            break; }
            case InputType::Left: {
                m_draw->drawSegment(pPos, {pPos.x - tip, pPos.y}, pSize, pCol);
                m_draw->drawSegment({pPos.x - tip - half, pPos.y - half}, {pPos.x - offset, pPos.y + offset}, pSize, pCol);
                m_draw->drawSegment({pPos.x - tip - half, pPos.y + half}, {pPos.x - offset, pPos.y - offset}, pSize, pCol);
            break; }
            default: break;
        }
    }
    void EditorTrail::drawTriangle(const cocos2d::CCPoint& pPos, float pSize, const cocos2d::ccColor4F& pCol) {
        const std::array<CCPoint, 3> points = {
            ccp(pPos.x - pSize, pPos.y - pSize),
            ccp(pPos.x + pSize, pPos.y - pSize),
            ccp(pPos.x, pPos.y + pSize)
        };
        
        m_draw->drawPolygon(points, pCol);
    }
    void EditorTrail::drawPrism(const cocos2d::CCPoint& pPos, float pSize, const cocos2d::ccColor4F& pCol) {
        const auto halfSize = pSize / 2;

        const std::array<CCPoint, 4> points = {
            ccp(pPos.x, pPos.y + pSize),
            ccp(pPos.x + halfSize, pPos.y),
            ccp(pPos.x, pPos.y - pSize),
            ccp(pPos.x - halfSize, pPos.y)
        };

        m_draw->drawPolygon(points, pCol);
    }

    void EditorTrail::addPlayerPoint(bool pPlayer2, cocos2d::CCPoint pPos, bool pStart) {
        auto& state = pPlayer2 ? m_player2State : m_player1State;
        
        pStart |= state.points.empty();

        state.points.emplace_back(pPos, pStart, static_cast<bool>(state.activeInputs));
    }
    void EditorTrail::addPlayerInput(bool pPlayer2, InputType pType, cocos2d::CCPoint pPos, bool pRelease) {
        auto& state = pPlayer2 ? m_player2State : m_player1State;

        if (state.inputs.empty() && pRelease) {
            return;
        }

        if (pRelease) {
            state.activeInputs--;
        }
        else {
            state.activeInputs++;
        }

        state.inputs.emplace_back(pPos, pType, pRelease);
    }
    void EditorTrail::addPlayerHitbox(PlayerObject* pPlayer) {
        if (!pPlayer) {
            return;
        }

        auto& state = pPlayer->m_isSecondPlayer ? m_player2State : m_player1State;

        state.hitbox.emplace_back(pPlayer->getObjectRect(), pPlayer->getObjectRect(0.3f, 0.3f));
    }

    void EditorTrail::reset() {
        m_player1State.reset();
        m_player2State.reset();
    }

    void EditorTrail::updateTrail(bool pShouldDraw) {
        if (!m_draw) {
            return;
        }

        m_draw->clear();

        if (!pShouldDraw) {
            return;
        }
        
        m_draw->setUseTint(settings::chroma);
        m_draw->setTint(misc::getChroma<ccColor4F>(settings::chromaSpeed, 0.0f, settings::chromaSaturation, 1.0f));

        const auto viewSize = editor::size(false) * 1.25f; // i dont feel like doing more complicated checks for perfect culling
        const CCRect view{editor::center(false) - viewSize / 2, viewSize};

        if (settings::hitboxesEnabled) {
            drawHitboxes(view);
        }

        drawTrail(view);

        if (settings::indicatorsEnabled) {
            drawIndicators(view);
        }
    }

    EditorTrail* EditorTrail::create() {
        auto ret = new EditorTrail;

        if (!ret->init()) {
            delete ret;

            return nullptr;
        }

        ret->autorelease();

        return ret;
    }
}