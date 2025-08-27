#include "Trail.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

namespace Trail {
    void updateTrail(LevelEditorLayer* editor) {
        if (!Cache::trailRendering) return;

        Cache::trailSteps++;

        /// could make shit const but like idc it looks ugly with my theme (yes thats my only reason)
        auto& p1Points = editor->m_playerPoints;
        auto size = p1Points.size();
        if (editor->m_player1 && size > 1) {
            Utils::drawLine(
                Cache::trailDraw,
                p1Points[size - 2], p1Points[size - 1], Settings::p1TrailSize, 
                Cache::p1Holding ? Settings::p1HoldTrailCol : Cache::p1TrailCol
            );
        }

        auto& p2PointsVector = editor->m_player2Points;

        if (p2PointsVector.empty()) return; // robtop saves p2 points as a vector of vectors

        auto& p2Points = p2PointsVector[p2PointsVector.size() - 1];
        if (editor->m_player2 && p2Points.size() > 1) {
            Utils::drawLine(
                Cache::trailDraw,
                p2Points[size - 2], p2Points[size - 1], Settings::p2TrailSize, 
                Cache::p2Holding ? Settings::p2HoldTrailCol : Cache::p2TrailCol
            );
        }
    }

    void startTrail() {
        Cache::trailDraw->clear();
        Cache::indicatorDraw->clear();
        Cache::trailSteps = 0;
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