#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <settings.hpp>
#include <utils.hpp>

using namespace geode::prelude;

class $modify(HookedEditorPauseLayer, EditorPauseLayer) {
    bool init(LevelEditorLayer* layer) {
        if (!EditorPauseLayer::init(layer)) {
            return false;
        }

        if (!settings::settingsButtonEnabled) {
            return true;
        }

        auto menu = getChildByID("guidelines-menu");

        if (!menu) {
            return true;
        }

        ui::buttonSprite(
            "settings-button.png"_spr, this, 
            menu_selector(HookedEditorPauseLayer::onBETSettings), 0.85f
        )
            .id("settings-button"_spr)
            .parent(menu);

        return true;
    }

    void onBETSettings(CCObject* sender) {
        openSettingsPopup(Mod::get(), true);
    }
};