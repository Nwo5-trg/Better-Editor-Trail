#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include "../trail/Trail.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(Editor, LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {
        if (!LevelEditorLayer::init(p0, p1)) return false;
                
        /// i dont think this is needed but go on
        Cache::trailLayer = nullptr;
        Cache::trailDraw = nullptr;
        Cache::indicatorDraw = nullptr;

        Settings::updateSettings();

        Utils::getTrailLayer(this);

        GameManager::sharedState()->setGameVariable("0152", true); // hide default trail
        GameManager::sharedState()->setGameVariable("0149", false); // hide click indicators


        for (int i = 0; i < 2; i++) {
            auto draw = CCDrawNode::create();
            draw->setPosition(0.0f, 0.0f);
            draw->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
            draw->setID(i == 0 ? "better-trail-trail"_spr : "better-trail-indicators"_spr);
            Cache::trailLayer->addChild(draw);
            if (i == 0) Cache::trailDraw = draw;
            else Cache::indicatorDraw = draw;
        }

        Cache::p1TrailCol = Settings::p1UseColor 
        ? ccc4FFromccc3B(m_player1->m_playerColor1)
        : Settings::p1TrailCol;

        Cache::p2TrailCol = Settings::p2UseColor 
        ? ccc4FFromccc3B(m_player2->m_playerColor2)
        : Settings::p2TrailCol;

        return true;
    }

    void postUpdate(float p0) {
        // idk what method robtop uses to update his playerpoints but 
        // it fixes all the lag issues to my knowledge with my method so im just gonna use his points
        // it does update really slow normally tho so were just gonna speed that up
        /// just say you copied ts from qol mod imo
        LevelEditorLayer::postUpdate(p0);
        m_trailTimer = Settings::trailTimer;
    }

    void updateDebugDraw() {
        LevelEditorLayer::updateDebugDraw();
        Trail::updateTrail(this);
    }

    void onPlaytest() {
        LevelEditorLayer::onPlaytest();
        Trail::startTrail();
        Trail::toggleTrail(!Settings::hideWhenPlaytesting);
    }

    void onStopPlaytest() {
        Trail::stopTrail();
        LevelEditorLayer::onStopPlaytest();
        Trail::toggleTrail(true);
    }
};