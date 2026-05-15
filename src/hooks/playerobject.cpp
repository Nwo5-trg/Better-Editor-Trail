#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <trail/trail.hpp>
#include <settings.hpp>

using namespace geode::prelude;

using BetterEditorTrail::InputType;

class $modify(PlayerObject) {
    bool pushButton(PlayerButton button) {
        bool ret;

        if (!Settings::spiderFix) {
            ret = PlayerObject::pushButton(button);
        }

        if (m_editorEnabled && isVisible() && editor::isPlaytesting()) {
            const auto input = m_isPlatformer ? static_cast<InputType>(button) : InputType::Normal;
            BetterEditorTrail::getTrail()->addPlayerInput(m_isSecondPlayer, input, getRealPosition(), false);
        }

        if (Settings::spiderFix) {
            ret = PlayerObject::pushButton(button);
        }
        
        return ret;
    }

    bool releaseButton(PlayerButton button) {
        bool ret;

        if (!Settings::spiderFix) {
            ret = PlayerObject::releaseButton(button);
        }

        if (m_editorEnabled && isVisible() && editor::isPlaytesting()) {
            const auto input = m_isPlatformer ? static_cast<InputType>(button) : InputType::Normal;
            BetterEditorTrail::getTrail()->addPlayerInput(m_isSecondPlayer, input, getRealPosition(), true);
        }

        if (Settings::spiderFix) {
            ret = PlayerObject::releaseButton(button);
        }
        
        return ret;
    }
};