#include <Geode/modify/EditorUI.hpp>
#include <settings.hpp>

using namespace geode::prelude;

class $modify(EditorUI) {
    void keyDown(enumKeyCodes key, double timestamp) {
        EditorUI::keyDown(key, timestamp);

        if (key == cocos2d::KEY_F5 && settings::syncShowHitboxes) {
            settings::hitboxesEnabled = GameManager::get()->getGameVariable(GameVar::DebugDrawEditor);
        }
    }
};