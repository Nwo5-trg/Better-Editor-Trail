#pragma once

#include <nwo5.silly-api/utils/include.hpp>
#include <nwo5.silly-api/editor/include.hpp>
#include <nwo5.silly-api/ui/include.hpp>
#include <nwo5.silly-api/nodes/include.hpp>

using namespace nwo5::utils::prelude;
using namespace nwo5::editor::prelude;
using namespace nwo5::ui::prelude;
using namespace nwo5::nodes::prelude;

namespace bettereditortrail {
    enum class IndicatorShape {
        Square,
        Circle,
        Triangle,
        Prism
    };

    IndicatorShape indicatorShapeFromString(std::string_view pStr);

    inline auto& processInputs() {
        static bool val = false;
        return val;
    }
}