#include "Utils.hpp"
#include "../shared/Cache.hpp"

using namespace geode::prelude;

namespace Utils {
    void drawLine(CCDrawNode* drawNode, const CCPoint& p1, const CCPoint& p2, float thickness, const ccColor4F& col) {
        thickness *= 0.5f;

        auto dir = ccpNormalize(p2 - p1);
        auto perp = ccp(-dir.y * thickness, dir.x * thickness);

        CCPoint v[] {
            p1 + perp, p2 + perp, p2 - perp, p1 - perp
        };
        drawNode->drawPolygon(v, 4, col, std::numeric_limits<float>::epsilon(), col);
    }

    void drawAngle(CCDrawNode* drawNode, const CCPoint& p0, const CCPoint& p1, const CCPoint& p2, float thickness, const ccColor4F& col) {
        thickness *= 0.5f;

        auto dir0 = ccpNormalize(p1 - p0);
        auto dir1 = ccpNormalize(p2 - p1);
        auto perp1 = ccp(-dir1.y * thickness, dir1.x * thickness);

        if (p0 == p1 || dir0 == dir1) {
            CCPoint v[] {
                p1 + perp1, p2 + perp1, p2 - perp1, p1 - perp1,
            };
            drawNode->drawPolygon(v, 4, col, std::numeric_limits<float>::epsilon(), col);
            return;
        }

        auto perp0 = ccp(-dir0.y * thickness, dir0.x * thickness);

        if (std::atan2f(dir0.cross(dir1), dir0.dot(dir1)) > 0.0f) {
            CCPoint v[] {
                p1 + perp1, p2 + perp1, p2 - perp1, p1 - perp1,
                p1 - perp0
            };
            drawNode->drawPolygon(v, 5, col, std::numeric_limits<float>::epsilon(), col);
        }
        else {
            CCPoint v[] {
                p1 + perp0,
                p1 + perp1, p2 + perp1, p2 - perp1, p1 - perp1
            };
            drawNode->drawPolygon(v, 5, col, std::numeric_limits<float>::epsilon(), col);
        }
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
