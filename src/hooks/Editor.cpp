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

        CCDrawNode* draws[2];
        for (auto& draw : draws) {
            draw = CCDrawNode::create();
            draw->setPosition(0.0f, 0.0f);
            draw->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
            draw->m_bUseArea = false;
            Cache::trailLayer->addChild(draw);
        }
        Cache::trailDraw = draws[0];
        Cache::indicatorDraw = draws[1];

        Cache::trailDraw->setID("better-trail-trail"_spr);
        Cache::indicatorDraw->setID("better-trail-indicators"_spr);

        Cache::p1TrailCol = Settings::p1UseColor
            ? ccc4FFromccc3B(m_player1->m_playerColor1)
            : Settings::p1TrailCol;

        Cache::p2TrailCol = Settings::p2UseColor
            ? ccc4FFromccc3B(m_player2->m_playerColor2)
            : Settings::p2TrailCol;

        return true;
    }

    void postUpdate(float p0) {
        if (m_player1) {
            if (m_player1->m_wasTeleported) {
                Cache::playerStates[0].moving = false;
                Cache::playerStates[0].pos = m_player1->getPosition();
                Cache::playerStates[0].prevPos = Cache::playerStates[0].pos;
            }
            Trail::endMove(m_player1, static_cast<PlayerButton>(0));
        }
        if (m_player2) {
            if (m_player2->m_wasTeleported) {
                Cache::playerStates[1].moving = false;
                Cache::playerStates[1].pos = m_player2->getPosition();
                Cache::playerStates[1].prevPos = Cache::playerStates[1].pos;
            }
            Trail::endMove(m_player2, static_cast<PlayerButton>(0));
        }
        LevelEditorLayer::postUpdate(p0);
    }

    void onPlaytest() {
        LevelEditorLayer::onPlaytest();
        Trail::startTrail();
        Trail::toggleTrail(!Settings::hideWhenPlaytesting);

        Cache::playerStates[0].moving = false;
        Cache::playerStates[0].jump = false;
        Cache::playerStates[0].left = false;
        Cache::playerStates[0].right = false;
        Cache::playerStates[0].pos = m_player1 ? m_player1->getPosition() : ccp(0.0f, 0.0f);
        Cache::playerStates[0].prevPos = Cache::playerStates[0].pos;

        Cache::playerStates[1].moving = false;
        Cache::playerStates[1].jump = false;
        Cache::playerStates[1].left = false;
        Cache::playerStates[1].right = false;
        Cache::playerStates[1].pos = m_player2 ? m_player2->getPosition() : ccp(0.0f, 0.0f);
        Cache::playerStates[1].prevPos = Cache::playerStates[1].pos;
    }

    void onStopPlaytest() {
        Trail::stopTrail();
        LevelEditorLayer::onStopPlaytest();
        Trail::toggleTrail(true);
    }
};
