#include <Geode/modify/GJBaseGameLayer.hpp>
#include "../trail/trail.hpp"
#include "../settings.hpp"

using namespace geode::prelude;

class $modify(HookedGJBaseGameLayer, GJBaseGameLayer) {
    struct Fields {
        bool wasDual = false;
    };

    void updateTrailGameTick() {
        auto trail = BetterEditorTrail::getTrail();

        if (!trail) {
            return;
        }

        if (Settings::updateMethod == "Game Tick") {
            auto fields = m_fields.self();

            const bool isStart = fields->wasDual != m_gameState.m_isDualMode;
            fields->wasDual = m_gameState.m_isDualMode;

            trail->addPlayerPoint(false, m_player1->getRealPosition(), isStart);
            if (m_player2) {
                trail->addPlayerPoint(true, m_player2->getRealPosition(), isStart);
            }
        }

        trail->addPlayerHitbox(m_player1);
        trail->addPlayerHitbox(m_player2);
    }

    #ifdef GEODE_IS_MACOS
        void processQueuedButtons(float dt, bool clearInputQueue) {
            GJBaseGameLayer::processQueuedButtons(dt, clearInputQueue);
            updateTrailGameTick();
        }
    #else
        void processCommands(float dt, bool isHalfTick, bool isLastTick) {
            GJBaseGameLayer::processCommands(dt, isHalfTick, isLastTick);
            updateTrailGameTick();
        }
    #endif
};