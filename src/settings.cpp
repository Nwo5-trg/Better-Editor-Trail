#include "settings.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
    SettingsManager::get()->load();
}