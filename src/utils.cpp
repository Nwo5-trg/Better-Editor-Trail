#include "utils.hpp"

using namespace geode::prelude;

namespace Utils {
    // this is a *horrendous atrocity* for many a reason... but its fun ! let me have some joy and whimsy
    IndicatorShape indicatorShapeFromString(std::string_view pStr) {
        switch (pStr.front()) {
            case 'C': return IndicatorShape::Circle;
            case 'T': return IndicatorShape::Triangle;
            case 'P': return IndicatorShape::Prism;
            default: return IndicatorShape::Square;
        };
    }
}