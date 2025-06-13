#include "Trail.hpp"
#include "Variables.hpp"

using namespace geode::prelude;

void updateTrail(LevelEditorLayer* editor) {
    if (!BetterTrailVars::trailRendering) return;
    BetterTrailVars::trailSteps++;
    auto p1 = editor->m_player1;
    auto p2 = editor->m_player2;
    const auto& p1Points = editor->m_playerPoints;
    const auto& p2PointsVector = editor->m_player2Points;
    if (p1 && p1Points.size() > 1) {
        auto size = p1Points.size();
        auto col = BetterTrailVars::p1Holding ? BetterTrailVars::p1HoldTrailCol : BetterTrailVars::p1TrailCol;
        if (BetterTrailVars::p1UseColor) col = ccc4FFromccc3B(p1->m_playerColor1);
        BetterTrailVars::trailDraw->drawSegment(p1Points[size - 2], p1Points[size - 1], BetterTrailVars::p1TrailSize, col);
    }

    if (!p2PointsVector.empty()) { // robtop saves p2 points as a vector of vectors
        const auto& p2Points = p2PointsVector[p2PointsVector.size() - 1];
        if (p2 && p2Points.size() > 1) {
            auto size = p2Points.size();
            auto col = BetterTrailVars::p2Holding ? BetterTrailVars::p2HoldTrailCol : BetterTrailVars::p2TrailCol;
            if (BetterTrailVars::p2UseColor) col = ccc4FFromccc3B(p2->m_playerColor1);
            BetterTrailVars::trailDraw->drawSegment(p2Points[size - 2], p2Points[size - 1], BetterTrailVars::p2TrailSize, col);
        }
    }
}

void startTrail() {
    BetterTrailVars::trailDraw->clear();
    BetterTrailVars::indicatorDraw->clear();
    BetterTrailVars::trailSteps = 0;
    BetterTrailVars::trailRendering = true;
}

void stopTrail() {
    BetterTrailVars::trailRendering = false;
}

void toggleTrail(bool on) {
    BetterTrailVars::trailDraw->setVisible(on);
    BetterTrailVars::indicatorDraw->setVisible(on);
}