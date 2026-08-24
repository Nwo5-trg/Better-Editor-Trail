#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <trail/trail.hpp>
#include <settings.hpp>

using namespace geode::prelude;

using BetterEditorTrail::InputType;

class $modify(PlayerObject) {
    bool pushButton(PlayerButton button) {
        if (Settings::spiderFix) {
            const auto ret = PlayerObject::pushButton(button);

            if (m_editorEnabled && isVisible() && editor::isPlaytesting()) {
                const auto input = m_isPlatformer ? static_cast<InputType>(button) : InputType::Normal;
                BetterEditorTrail::getTrail()->addPlayerInput(m_isSecondPlayer, input, this->getRealPosition(), false);
            }

            return ret;
        }
        else {
            if (m_editorEnabled && isVisible() && editor::isPlaytesting()) {
                const auto input = m_isPlatformer ? static_cast<InputType>(button) : InputType::Normal;
                BetterEditorTrail::getTrail()->addPlayerInput(m_isSecondPlayer, input, this->getRealPosition(), false);
            }

            return PlayerObject::pushButton(button);
        }
    }

    bool releaseButton(PlayerButton button) {
        if (Settings::spiderFix) {
            const auto ret = PlayerObject::releaseButton(button);

            if (m_editorEnabled && isVisible() && editor::isPlaytesting()) {
                const auto input = m_isPlatformer ? static_cast<InputType>(button) : InputType::Normal;
                BetterEditorTrail::getTrail()->addPlayerInput(m_isSecondPlayer, input, this->getRealPosition(), true);
            }

            return ret;
        }
        else {
            if (m_editorEnabled && isVisible() && editor::isPlaytesting()) {
                const auto input = m_isPlatformer ? static_cast<InputType>(button) : InputType::Normal;
                BetterEditorTrail::getTrail()->addPlayerInput(m_isSecondPlayer, input, this->getRealPosition(), true);
            }

            return PlayerObject::releaseButton(button);
        }
    }
};