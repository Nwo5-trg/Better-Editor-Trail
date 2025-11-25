#include "Trail.hpp"
#include "Indicators.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

namespace Trail {
    void startMove(PlayerObject* player, PlayerButton click) {
        if (!Cache::trailRendering) return;

        bool p2 = player->m_isSecondPlayer;
        auto& state = Cache::playerStates[p2];

        if (state.moving) return;
        state.moving = true;

        const CCPoint& pos = player->getPosition();

        if (static_cast<int>(click) > 0)
            Trail::createClick(player, click);

        state.jump = state.jump || click == PlayerButton::Jump;
        state.left = state.left || click == PlayerButton::Left;
        state.right = state.right || click == PlayerButton::Right;
        if (state.pos != pos)
            state.prevPos = state.pos;
        state.pos = pos;
    }

    void endMove(PlayerObject* player, PlayerButton release) {
        if (!Cache::trailRendering) return;

        bool p2 = player->m_isSecondPlayer;
        auto& state = Cache::playerStates[p2];

        if (!state.moving) return;
        state.moving = false;

        const CCPoint& pos = player->getPosition();

        if (pos.x - state.pos.x != 0.0f || pos.y - state.pos.y != 0.0f) {
            const float& trailSize = p2 ? Settings::p2TrailSize : Settings::p1TrailSize;

            const ccColor4F& releaseTrailCol = p2 ? Settings::p2TrailCol : Settings::p1TrailCol;
            const ccColor4F& holdTrailCol = p2 ? Settings::p2HoldTrailCol : Settings::p1HoldTrailCol;

            bool input = state.jump || state.left || state.right;
            bool indicateHolding = p2 ? Settings::p2IndicateHolding : Settings::p1IndicateHolding;
            const ccColor4F& trailCol = input && indicateHolding ? holdTrailCol : releaseTrailCol;

            if (state.prevPos == state.pos) {
                Cache::trailDraw->drawCircle(
                    state.pos, trailSize * 0.5f, trailCol,
                    std::numeric_limits<float>::epsilon(), trailCol, 16
                );
            }
            Utils::drawAngle(Cache::trailDraw, state.prevPos, state.pos, pos, trailSize, trailCol);
        }

        if (static_cast<int>(release) > 0)
            Trail::createRelease(player, release);

        state.jump = state.jump && release != PlayerButton::Jump;
        state.left = state.left && release != PlayerButton::Left;
        state.right = state.right && release != PlayerButton::Right;
        if (state.pos != pos)
            state.prevPos = state.pos;
        state.pos = pos;
    }

    void startTrail() {
        Cache::trailDraw->clear();
        Cache::indicatorDraw->clear();
        Cache::trailRendering = true;
    }

    void stopTrail() {
        Cache::trailRendering = false;
    }

    void toggleTrail(bool on) {
        Cache::trailDraw->setVisible(on);
        Cache::indicatorDraw->setVisible(on);
    }
}
