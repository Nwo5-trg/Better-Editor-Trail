#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <trail/trail.hpp>
#include <settings.hpp>

using namespace geode::prelude;

using bettereditortrail::InputType;

class $modify(PlayerObject) {
    bool pushButton(PlayerButton button) {
        if (!settings::botFix && !bettereditortrail::processInputs() && !m_isPlatformer) {
            return PlayerObject::pushButton(button);
        }

        if (settings::spiderFix) {
            if (m_editorEnabled && isVisible() && editor::isPlaytesting()) {
                const auto input = m_isPlatformer ? static_cast<InputType>(button) : InputType::Normal;
                bettereditortrail::getTrail()->addPlayerInput(m_isSecondPlayer, input, this->getRealPosition(), false);
            }

            return PlayerObject::pushButton(button);
        }
        else {
            const auto ret = PlayerObject::pushButton(button);

            if (m_editorEnabled && isVisible() && editor::isPlaytesting()) {
                const auto input = m_isPlatformer ? static_cast<InputType>(button) : InputType::Normal;
                bettereditortrail::getTrail()->addPlayerInput(m_isSecondPlayer, input, this->getRealPosition(), false);
            }

            return ret;
        }
    }

    bool releaseButton(PlayerButton button) {
        if (!settings::botFix && !bettereditortrail::processInputs() && !m_isPlatformer) {
            return PlayerObject::releaseButton(button);
        }

        if (settings::spiderFix) {
            if (m_editorEnabled && isVisible() && editor::isPlaytesting()) {
                const auto input = m_isPlatformer ? static_cast<InputType>(button) : InputType::Normal;
                bettereditortrail::getTrail()->addPlayerInput(m_isSecondPlayer, input, this->getRealPosition(), true);
            }

            return PlayerObject::releaseButton(button);
        }
        else {
            const auto ret = PlayerObject::releaseButton(button);

            if (m_editorEnabled && isVisible() && editor::isPlaytesting()) {
                const auto input = m_isPlatformer ? static_cast<InputType>(button) : InputType::Normal;
                bettereditortrail::getTrail()->addPlayerInput(m_isSecondPlayer, input, this->getRealPosition(), true);
            }

            return ret;
        }
    }
};