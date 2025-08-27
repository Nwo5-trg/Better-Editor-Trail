#include "Utils.hpp"
#include "../shared/Cache.hpp"

using namespace geode::prelude;

namespace Utils {
    void drawLine(CCDrawNode* drawNode, CCPoint p1, CCPoint p2, float thickness, ccColor4F col) {
        // see taking like 3 weeks learning opengl payed off for smth 
        auto dir = ccpNormalize(p2 - p1);
        auto perp = ccp(-dir.y, dir.x) * (thickness / 2);
        CCPoint v[] {
            (p1 + perp), (p2 + perp), (p2 - perp), (p1 - perp)
        };
        drawNode->drawPolygon(v, 4, col, 0.0f, col);
    }

    void getTrailLayer(LevelEditorLayer* editor) {
        for (auto node : CCArrayExt<CCNode*>(editor->getChildren())) { // find the vanilla trail layer safely maybe or smth

            auto layer = typeinfo_cast<CCLayer*>(node->getChildByType<CCNode>(0));
            if (!layer) continue;

            if (layer->getChildByType<CCDrawNode>(0)) Cache::trailLayer = layer;
            // oh yeah and NOT hide vanilla trail 
            // (cuz the grand fuckass robtop draws hitboxes in the same drawnode as the trail 
            // (and i think redraws every frame wtf));
            /// fucks this girl talking about :sob:
        }
    }
}