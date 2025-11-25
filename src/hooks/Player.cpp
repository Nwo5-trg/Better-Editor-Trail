#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "../trail/Trail.hpp"
#include "../shared/Cache.hpp"

using namespace geode::prelude;

class $modify(Player, PlayerObject) {
    bool pushButton(PlayerButton p0) {
        if (!m_editorEnabled) return PlayerObject::pushButton(p0);
        Trail::startMove(this, p0);
        bool ret = PlayerObject::pushButton(p0);
        Trail::endMove(this, static_cast<PlayerButton>(0));
        return ret;
    }

    bool releaseButton(PlayerButton p0) {
        if (!m_editorEnabled) return PlayerObject::releaseButton(p0);
        Trail::startMove(this, static_cast<PlayerButton>(0));
        bool ret = PlayerObject::releaseButton(p0);
        Trail::endMove(this, p0);
        return ret;
    }

    void update(float dt) {
        if (!m_editorEnabled) return PlayerObject::update(dt);
        Trail::startMove(this, static_cast<PlayerButton>(0));
        PlayerObject::update(dt);
    }

    void copyAttributes(PlayerObject* from) {
        PlayerObject::copyAttributes(from);
        if (!m_editorEnabled) return;
        Cache::playerStates[m_isSecondPlayer] = Cache::playerStates[!m_isSecondPlayer];
        Cache::playerStates[m_isSecondPlayer].pos = this->getPosition();
        Cache::playerStates[m_isSecondPlayer].prevPos = this->getPosition();
        //Cache::playerStates[m_isSecondPlayer].prevPos = Cache::playerStates[m_isSecondPlayer].pos;
    }
};
