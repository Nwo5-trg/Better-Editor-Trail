#include <Geode/modify/LevelEditorLayer.hpp>
#include <trail/trail.hpp>
#include <settings.hpp>

using namespace geode::prelude;

using bettereditortrail::EditorTrail;

class $modify(HookedLevelEditorLayer, LevelEditorLayer) {
    struct Fields {
        EditorTrail* trail = nullptr;
        
        bool wasDual = false;
    };

    bool init(GJGameLevel* level, bool noUI) {
        if (!LevelEditorLayer::init(level, noUI)) {
            return false;
        }

        m_fields->trail = Setup(EditorTrail::create())
            .id("better-editor-trail"_spr)
            .pos(CCPointZero)
            .order(1403)
            .parent(m_debugDrawNode->getParent());

        misc::setupKeybind(this, "hitboxes-keybind", [this] (const auto&, bool pDown, auto, auto) {
            if (pDown) {
                settings::hitboxesEnabled = !settings::hitboxesEnabled;
            }
        });
        
        return true;
    }
    
    void onPlaytest() {    
        LevelEditorLayer::onPlaytest();

        m_fields->trail->reset();
    }

    void updateDebugDraw() {
        if (!settings::enabled) {
            LevelEditorLayer::updateDebugDraw();

            return m_fields->trail->updateTrail(false);
        }

        const auto hideTrail = GameManager::get()->getGameVariable(GameVar::HidePlayerPath);
        
        GameManager::get()->setGameVariable(GameVar::HidePlayerPath, true);

        LevelEditorLayer::updateDebugDraw();

        if (settings::hideInPlaytest && editor::isPlaytesting()) {
            m_fields->trail->updateTrail(false);
        }
        else {
            m_fields->trail->updateTrail(true);
        }

        GameManager::get()->setGameVariable(GameVar::HidePlayerPath, hideTrail);
    }

    void postUpdate(float dt) {
        if (settings::updateMethod == "Post Update") {
            auto fields = m_fields.self();

            const bool isStart = fields->wasDual != m_gameState.m_isDualMode;
            fields->wasDual = m_gameState.m_isDualMode;

            auto trail = fields->trail;

            trail->addPlayerPoint(false, m_player1->getRealPosition(), isStart);
            trail->addPlayerPoint(true, m_player2->getRealPosition(), isStart);
        }

        LevelEditorLayer::postUpdate(dt);
    }

    void onStopPlaytest() {
        // if it gets set normally indicator appears when playtest stopped
        m_playbackMode = PlaybackMode::Not;
        
        LevelEditorLayer::onStopPlaytest();
    }
};

namespace bettereditortrail {
    EditorTrail* getTrail() {
        auto layer = editor::layer<HookedLevelEditorLayer>();
        
        if (!layer) {
            return nullptr;
        }

        return layer->m_fields->trail;
    }
}