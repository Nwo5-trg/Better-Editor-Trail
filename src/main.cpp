#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

auto mod = Mod::get();
bool trailRendering = false;

class $modify (LevelEditor, LevelEditorLayer) {
    struct Fields {
        CCLayer* trailRenderLayer;
        CCLayer* batchLayer;
        CCDrawNode* trailRenderer;
        CCDrawNode* dotRenderer;
        CCPoint lastPlayerPos = ccp(-100, -100);
        CCPoint lastPlayerPos2 = ccp(-100, -100);
        float trailSize = mod->getSettingValue<double>("trail-size");
        float clickSize = mod->getSettingValue<double>("click-size");
        float releaseSize = mod->getSettingValue<double>("release-size");
        bool holding;
        bool useHold = mod->getSettingValue<bool>("use-hold-one");
        bool useHold2 = mod->getSettingValue<bool>("use-hold-two");
        bool clickDirection = mod->getSettingValue<bool>("click-direction");
        bool releaseDirection = mod->getSettingValue<bool>("release-direction");
        ccColor4F trailColor;
        ccColor4F trailColor2;
        ccColor4F trailHoldColor;
        ccColor4F trailHoldColor2;
        ccColor4F dotColor;
        ccColor4F dotColor2;
        ccColor4F dotReleaseColor;
        ccColor4F dotReleaseColor2;
    };

    virtual void postUpdate(float dt) { // disable default path
        m_trailTimer = 0;
        LevelEditorLayer::postUpdate(dt);
    }
    
    bool init (GJGameLevel* p0, bool p1) {
        if (!LevelEditorLayer::init(p0, p1)) return false;

        if (auto shaderLayer = this->getChildByType<ShaderLayer>(0)) m_fields->batchLayer = shaderLayer->getChildByType<CCNode>(1)->getChildByType<CCLayer>(0);
        else m_fields->batchLayer = this->getChildByType<CCNode>(1)->getChildByType<CCLayer>(0);
        
        auto nodes = this->getChildren(); // not crash with shaderlayer
        for (int i = 0; i < nodes->count(); i++) { 
            if (auto layer = typeinfo_cast<CCLayer*>(static_cast<CCNode*>(nodes->objectAtIndex(i))->getChildByType<CCNode>(0))) {
                if (layer->getChildByType<CCDrawNode>(0)) m_fields->trailRenderLayer = layer;
            }
        }

        auto trailRenderer = CCDrawNode::create();
        trailRenderer->setZOrder(1401);
        m_fields->trailRenderLayer->addChild(trailRenderer);
        m_fields->trailRenderer = trailRenderer;

        if (mod->getSettingValue<bool>("show-clicks") || mod->getSettingValue<bool>("show-releases")) {
            GameManager::sharedState()->setGameVariable("0149", false);
            auto dotRenderer = CCDrawNode::create(); // make a dot renderer seperately so dots render above the trail
            dotRenderer->setZOrder(1402);
            m_fields->trailRenderLayer->addChild(dotRenderer);
            m_fields->dotRenderer = dotRenderer;
        }
        
        // this part is so bad but idk how to optimise it
        auto col = mod->getSettingValue<ccColor4B>("trail-color-one");
        m_fields->trailColor = ccc4f(col.r / 255.f, col.g / 255.f, col.b / 255.f, col.a / 255.f);
        col = mod->getSettingValue<ccColor4B>("trail-color-two");
        m_fields->trailColor2 = ccc4f(col.r / 255.f, col.g / 255.f, col.b / 255.f, col.a / 255.f);
        col = mod->getSettingValue<ccColor4B>("trail-hold-color-one");
        m_fields->trailHoldColor = ccc4f(col.r / 255.f, col.g / 255.f, col.b / 255.f, col.a / 255.f);
        col = mod->getSettingValue<ccColor4B>("trail-hold-color-two");
        m_fields->trailHoldColor2 = ccc4f(col.r / 255.f, col.g / 255.f, col.b / 255.f, col.a / 255.f);
        col = mod->getSettingValue<ccColor4B>("click-color-one");
        m_fields->dotColor = ccc4f(col.r / 255.f, col.g / 255.f, col.b / 255.f, col.a / 255.f);
        col = mod->getSettingValue<ccColor4B>("click-color-two");
        m_fields->dotColor2 = ccc4f(col.r / 255.f, col.g / 255.f, col.b / 255.f, col.a / 255.f);
        col = mod->getSettingValue<ccColor4B>("release-color-one");
        m_fields->dotReleaseColor = ccc4f(col.r / 255.f, col.g / 255.f, col.b / 255.f, col.a / 255.f);
        col = mod->getSettingValue<ccColor4B>("release-color-two");
        m_fields->dotReleaseColor2 = ccc4f(col.r / 255.f, col.g / 255.f, col.b / 255.f, col.a / 255.f);
        return true;
    }

    void onPlaytest() {
        LevelEditorLayer::onPlaytest();
        startTrailUpdateLoop();
    }

    void onStopPlaytest() {
        LevelEditorLayer::onStopPlaytest();
        stopTrailUpdateLoop();
    }
    
    void startTrailUpdateLoop() {
        trailRendering = true;
        m_fields->lastPlayerPos = ccp(-100, -100);
        m_fields->lastPlayerPos2 = ccp(-100, -100);
        m_fields->trailRenderer->clear();
        m_fields->dotRenderer->clear();
        if (mod->getSettingValue<bool>("player-one-for-trail") && m_fields->batchLayer->getChildByType<PlayerObject>(0)) {
            auto pcolor = m_fields->batchLayer->getChildByType<PlayerObject>(0)->m_playerColor1;
            m_fields->trailColor = ccc4f(pcolor.r / 255.f, pcolor.g / 255.f, pcolor.b / 255.f, m_fields->trailColor.a);
        }
        if (mod->getSettingValue<bool>("player-two-for-trail") && m_fields->batchLayer->getChildByType<PlayerObject>(1)) {
            auto pcolor = m_fields->batchLayer->getChildByType<PlayerObject>(1)->m_playerColor1;
            m_fields->trailColor2 = ccc4f(pcolor.r / 255.f, pcolor.g / 255.f, pcolor.b / 255.f, m_fields->trailColor2.a);
        }
         // if someone lags from this or something ill add an optimised mode with scheduleupdatefortarget
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
        schedule_selector(LevelEditor::trailUpdate), this, static_cast<float>(mod->getSettingValue<double>("trail-interval")), false);
    }
    
    void stopTrailUpdateLoop() {
        trailRendering = false;
        CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(
        schedule_selector(LevelEditor::trailUpdate), this);
    }

    void trailUpdate(float dt) {
        if (trailRendering == false) return;
        CCPoint currentPlayerPos; // tried making this code cleaner but it wouldnt render duals so whatever
        auto fields = m_fields.self();

        if (auto player = fields->batchLayer->getChildByType<PlayerObject>(0)) {
            currentPlayerPos = player->getPosition();
            if (fields->lastPlayerPos != ccp(-100, -100)) {
                fields->trailRenderer->drawSegment(fields->lastPlayerPos, currentPlayerPos, fields->trailSize, (fields->holding && fields->useHold) ? fields->trailHoldColor : fields->trailColor);
            }
            fields->lastPlayerPos = currentPlayerPos;
        }
        
        if (auto player = fields->batchLayer->getChildByType<PlayerObject>(1)) {
            currentPlayerPos = player->getPosition();
            if (fields->lastPlayerPos2 != ccp(-100, -100)) {
                fields->trailRenderer->drawSegment(fields->lastPlayerPos2, currentPlayerPos, fields->trailSize, (fields->holding && fields->useHold2) ? fields->trailHoldColor2 : fields->trailColor2);
            }
            fields->lastPlayerPos2 = currentPlayerPos;
        }
    }

    void trailAddClick(bool player, bool isRelease, PlayerObject* playerObj, bool platformer, PlayerButton button) {
        auto color = isRelease ? (player ? m_fields->dotReleaseColor2 : m_fields->dotReleaseColor) : (player ? m_fields->dotColor2 : m_fields->dotColor);
        if (!platformer || !(isRelease ? m_fields->releaseDirection : m_fields->clickDirection)) {
            if (!(!platformer && !(button == PlayerButton::Jump))) {
                if (mod->getSettingValue<std::string>(isRelease ? "release-shape" : "click-shape") == "Square") m_fields->dotRenderer->drawDot(playerObj->getPosition(), isRelease ? m_fields->releaseSize : m_fields->clickSize, color);
                if (mod->getSettingValue<std::string>(isRelease ? "release-shape" : "click-shape") == "Circle") m_fields->dotRenderer->drawCircle(playerObj->getPosition(), isRelease ? m_fields->releaseSize : m_fields->clickSize, color, 0, color, 30);
            }
        }
        else drawArrow(playerObj->getPosition(), isRelease ? m_fields->releaseSize : m_fields->clickSize, color, button);

        if (isRelease) m_fields->holding = false;
        else m_fields->holding = true;
    }

    void drawArrow(CCPoint pos, float size, ccColor4F col, PlayerButton direction) {
        if (direction == PlayerButton::Jump) {
            m_fields->dotRenderer->drawSegment(ccp(pos.x, pos.y - (size * 1.5)), ccp(pos.x, pos.y + (size * 1.5)), size / 2, col);
            m_fields->dotRenderer->drawSegment(ccp(pos.x, pos.y + (size * 1.5)), ccp(pos.x + (size * 1.5), pos.y), size / 2, col);
            m_fields->dotRenderer->drawSegment(ccp(pos.x, pos.y + (size * 1.5)), ccp(pos.x - (size * 1.5), pos.y), size / 2, col);
        }
        else if (direction == PlayerButton::Right) {
            m_fields->dotRenderer->drawSegment(pos, ccp(pos.x + ((size * 1.5) * 2), pos.y), size / 2, col);
            m_fields->dotRenderer->drawSegment(ccp(pos.x + ((size * 1.5) * 2), pos.y), ccp(pos.x + (size * 1.5), pos.y + (size * 1.5)), size / 2, col);
            m_fields->dotRenderer->drawSegment(ccp(pos.x + ((size * 1.5) * 2), pos.y), ccp(pos.x + (size * 1.5), pos.y - (size * 1.5)), size / 2, col);
        }
        else if (direction == PlayerButton::Left) {
            m_fields->dotRenderer->drawSegment(pos, ccp(pos.x - ((size * 1.5) * 2), pos.y), size / 2, col);
            m_fields->dotRenderer->drawSegment(ccp(pos.x - ((size * 1.5) * 2), pos.y), ccp(pos.x - (size * 1.5), pos.y + (size * 1.5)), size / 2, col);
            m_fields->dotRenderer->drawSegment(ccp(pos.x - ((size * 1.5) * 2), pos.y), ccp(pos.x - (size * 1.5), pos.y - (size * 1.5)), size / 2, col);
        }
    }
};

class $modify (Player, PlayerObject) {
    struct Fields {
        bool buttonPushed;
        bool showClicks = mod->getSettingValue<bool>("show-clicks");
        bool showReleases = mod->getSettingValue<bool>("show-releases");
    };

    bool pushButton(PlayerButton p0) {
        auto ret = PlayerObject::pushButton(p0);
        if (m_fields->showClicks && !m_fields->buttonPushed && trailRendering) if (auto levelEditor = static_cast<LevelEditor*>(LevelEditorLayer::get())) {
            if (!m_isPlatformer) levelEditor->trailAddClick(m_isSecondPlayer, false, this, false, p0);
            else levelEditor->trailAddClick(m_isSecondPlayer, false, this, true, p0);
            m_fields->buttonPushed = true;
        }
        return ret;
    }

    bool releaseButton(PlayerButton p0) {
        auto ret = PlayerObject::releaseButton(p0);
        if (m_fields->showReleases && trailRendering) if (auto levelEditor = static_cast<LevelEditor*>(LevelEditorLayer::get())) {
            if (!m_isPlatformer) levelEditor->trailAddClick(m_isSecondPlayer, true, this, false, p0);
            else levelEditor->trailAddClick(m_isSecondPlayer, true, this, true, p0);
            m_fields->buttonPushed = false;
        }
        return ret;
    }
};