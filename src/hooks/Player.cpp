#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "../Indicators.hpp"
#include "../Variables.hpp"

using namespace geode::prelude;

class $modify(Player, PlayerObject) {
    bool pushButton(PlayerButton p0) {
        auto holdingLeft = m_holdingLeft; // scuffed but it works
        auto holdingRight = m_holdingRight;
        auto ret = !PlayerObject::pushButton(p0);
        if (!m_editorEnabled) return ret;   
        if (p0 == PlayerButton::Jump || ((p0 == PlayerButton::Right && !holdingRight) 
        || (p0 == PlayerButton::Left && !holdingLeft)))createClick(this, p0);
        if (m_isSecondPlayer) BetterTrailVars::p2Holding = true;
        else BetterTrailVars::p1Holding = true;
        return ret;
    }
    
    bool releaseButton(PlayerButton p0) {
        auto ret = !PlayerObject::releaseButton(p0);
        if (!m_editorEnabled) return ret;
        createRelease(this, p0);
        if (m_isSecondPlayer) BetterTrailVars::p2Holding = isButtonHeld();
        else BetterTrailVars::p1Holding = isButtonHeld();
        return ret;
    }

    bool isButtonHeld() { // why cant there just be a bool 3:
        // also there are edge cases that this doesnt work in but i cant be fucked to fix it
        for (const auto& pair : m_holdingButtons) if (pair.second) return true;
        return false;
    }
};