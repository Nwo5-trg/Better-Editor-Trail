#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include "../Trail.hpp"
#include "../Variables.hpp"

using namespace geode::prelude;

class $modify(Editor, LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {
        if (!LevelEditorLayer::init(p0, p1)) return false;
                
        // BetterTrailVars::batchLayer = nullptr;
        BetterTrailVars::trailLayer = nullptr;
        BetterTrailVars::trailDraw = nullptr;
        BetterTrailVars::indicatorDraw = nullptr;

        BetterTrailVars::updateSettings();

        // if (auto shaderLayer = this->getChildByType<ShaderLayer>(0)) BetterTrailVars::batchLayer = shaderLayer->getChildByType<CCNode>(1)->getChildByType<CCLayer>(0);
        // else BetterTrailVars::batchLayer = this->getChildByType<CCNode>(1)->getChildByType<CCLayer>(0);

        for (auto node : CCArrayExt<CCNode*>(this->getChildren())) { // find the vanilla trail layer safely or smth
            if (auto layer = typeinfo_cast<CCLayer*>(node->getChildByType<CCNode>(0))) {
                if (layer->getChildByType<CCDrawNode>(0)) {
                    BetterTrailVars::trailLayer = layer;
                    layer->getChildByTag(-9999)->setScale(0); // oh yeah and hide vanilla trail (setvisible constantly gets set and opacity doesnt work)
                }
            }
        }

        BetterTrailVars::hideTrail = GameManager::sharedState()->getGameVariable("0152");
        GameManager::sharedState()->setGameVariable("0149", false); // hide click indicators


        for (int i = 0; i < 2; i++) {
            auto draw = CCDrawNode::create();
            draw->setPosition(0.0f, 0.0f);
            draw->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
            draw->setID(i == 0 ? "better-trail-trail" : "better-trail-indicators");
            BetterTrailVars::trailLayer->addChild(draw);
            if (i == 0) BetterTrailVars::trailDraw = draw;
            else BetterTrailVars::indicatorDraw = draw;
        }

        return true;
    }

    void postUpdate(float p0) {
        // idk what method robtop uses to update his playerpoints but 
        // it fixes all the lag issues to my knowledge with my method so im just gonna use his points
        // it does update really slow normally tho so were just gonna speed that up
        LevelEditorLayer::postUpdate(p0);
        m_trailTimer = 240;
    }

    void updateDebugDraw() {
        LevelEditorLayer::updateDebugDraw();
        if (!BetterTrailVars::hideTrail) updateTrail(this);
    }

    void onPlaytest() {
        LevelEditorLayer::onPlaytest();
        BetterTrailVars::hideTrail = GameManager::sharedState()->getGameVariable("0152");
        startTrail();
    }

    void onStopPlaytest() {
        stopTrail();
        LevelEditorLayer::onStopPlaytest();
    }
};