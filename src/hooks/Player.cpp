#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "../trail/Indicators.hpp"
#include "../shared/Cache.hpp"

using namespace geode::prelude;

class $modify(Player, PlayerObject) {
    bool pushButton(PlayerButton p0) {
        /// ok i dont remember doing this
        /// but please tell me this is some sort of ret
        /// please for my own sanity tell me this is necessary
        bool holdingLeft = m_holdingLeft;
        bool holdingRight = m_holdingRight;

        bool ret = PlayerObject::pushButton(p0);
        if (!m_editorEnabled) return ret;   

        if (
            p0 == PlayerButton::Jump || ((p0 == PlayerButton::Right && !holdingRight) 
            || (p0 == PlayerButton::Left && !holdingLeft))
        ) Trail::createClick(this, p0);

        if (m_isSecondPlayer) Cache::p2Holding = true;
        else Cache::p1Holding = true;

        return ret;
    }
    
    bool releaseButton(PlayerButton p0) {
        bool ret = PlayerObject::releaseButton(p0);
        if (!m_editorEnabled) return ret;

        Trail::createRelease(this, p0);

        if (m_isSecondPlayer) Cache::p2Holding = isButtonHeld();
        else Cache::p1Holding = isButtonHeld();

        return ret;
    }

    bool isButtonHeld() { // why cant there just be a bool 3:
        // also there are edge cases that this doesnt work in but i cant be fucked to fix it
        /// what are you talking about past me or mnaybe current me is stupid and gay (well yeah but still)
        for (const auto& pair : m_holdingButtons) if (pair.second) return true;
        return false;
    }
};