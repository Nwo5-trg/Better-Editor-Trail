#include "settings.hpp"

$on_mod(Loaded) {
    SettingsManager::get()->load();
}