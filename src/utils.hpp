#pragma once

#include <nwo5.silly-api/include/utils/include.hpp>
#include <nwo5.silly-api/include/editor/include.hpp>
#include <nwo5.silly-api/include/ui/include.hpp>

using namespace nwo5::utils::prelude;
using namespace nwo5::editor::prelude;
using namespace nwo5::ui::prelude;

enum class IndicatorShape {
    Square,
    Circle,
    Triangle,
    Prism
};

namespace Utils {
    IndicatorShape indicatorShapeFromString(std::string_view pStr);
}