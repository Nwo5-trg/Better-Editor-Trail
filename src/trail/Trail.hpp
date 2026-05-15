#pragma once

#include "utils.hpp"

namespace BetterEditorTrail {
    enum class InputType {
        Normal = 0,

        Up = 1,
        Left = 2,
        Right = 3
    };

    struct TrailPoint {
        cocos2d::CCPoint pos;
        bool start;
        bool holding;
    };

    struct TrailInput {
        cocos2d::CCPoint pos;
        InputType type;
        bool release;
    };

    struct TrailHitbox {
        cocos2d::CCRect hitbox;
        cocos2d::CCRect innerHitbox;
    };

    struct PlayerState {
        std::vector<TrailPoint> points;
        
        std::vector<TrailInput> inputs;
        int activeInputs = 0;

        std::vector<TrailHitbox> hitbox;

        void reset() {
            points.clear();
            
            inputs.clear();
            activeInputs = 0;

            hitbox.clear();
        }
    };

    class EditorTrail final : public cocos2d::CCNode {
    protected:
        PlayerState m_player1State;
        PlayerState m_player2State;

        SillyDrawNode* m_draw = nullptr;

        bool init();

        void drawHitboxes(const cocos2d::CCRect& pView);
        void drawTrail(const cocos2d::CCRect& pView);
        void drawIndicators(const cocos2d::CCRect& pView);

        void drawArrow(const cocos2d::CCPoint& pPos, float pSize, InputType pType, const cocos2d::ccColor4F& pCol);
        void drawTriangle(const cocos2d::CCPoint& pPos, float pSize, const cocos2d::ccColor4F& pCol);
        void drawPrism(const cocos2d::CCPoint& pPos, float pSize, const cocos2d::ccColor4F& pCol);

    public:
        void addPlayerPoint(bool pPlayer2, cocos2d::CCPoint pPos, bool pStart);
        void addPlayerInput(bool pPlayer2, InputType pType, cocos2d::CCPoint pPos, bool pRelease);
        void addPlayerHitbox(PlayerObject* pPlayer);

        void reset();

        void updateTrail(bool pShouldDraw);

        static EditorTrail* create();
    };

    // impl in hooks/leveleditorlayer.cpp
    EditorTrail* getTrail();
}