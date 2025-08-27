#include "Settings.hpp"

using namespace geode::prelude;

namespace Settings {
    void updateSettings() {
        auto mod = Mod::get();

        trailTimer = mod->getSettingValue<double>("trail-timer");
        p1TrailSize = mod->getSettingValue<double>("trail-size-one");
        p2TrailSize = mod->getSettingValue<double>("trail-size-two");
        clickSize = mod->getSettingValue<double>("click-size");
        releaseSize = mod->getSettingValue<double>("release-size");

        for (int i = 0; i < 2; i++) {
            const auto& shape = mod->getSettingValue<std::string>(i == 1 ? "release-shape" : "click-shape");
            IndicatorShape shapeEnum;

            if (shape == "Square") shapeEnum = IndicatorShape::Square;
            else if (shape == "Circle") shapeEnum = IndicatorShape::Circle;
            else if (shape == "Triangle") shapeEnum = IndicatorShape::Triangle;
            else  shapeEnum = IndicatorShape::Prism;

            if (i == 1) releaseShape = shapeEnum;
            else clickShape = shapeEnum;
        }

        hideWhenPlaytesting = mod->getSettingValue<bool>("hide-when-playtesting");
        showClicks = mod->getSettingValue<bool>("show-clicks");
        showReleases = mod->getSettingValue<bool>("show-releases");
        p1IndicateHolding = mod->getSettingValue<bool>("use-hold-one");
        p2IndicateHolding = mod->getSettingValue<bool>("use-hold-two");
        showClickDirection = mod->getSettingValue<bool>("click-direction");
        showReleaseDirection = mod->getSettingValue<bool>("release-direction");
        p1UseColor = mod->getSettingValue<bool>("player-one-for-trail");
        p2UseColor = mod->getSettingValue<bool>("player-two-for-trail");

        p1TrailCol = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("trail-color-one"));
        p2TrailCol = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("trail-color-two"));
        p1HoldTrailCol = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("trail-hold-color-one"));
        p2HoldTrailCol = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("trail-hold-color-two"));
        p1ClickColor = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("click-color-one"));
        p2ClickColor = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("click-color-two"));
        p1ReleaseColor = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("release-color-one"));
        p2ReleaseColor = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("release-color-two"));
    }
}