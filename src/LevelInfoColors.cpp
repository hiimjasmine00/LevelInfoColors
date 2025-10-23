#include "LevelInfoColors.hpp"
#include <Geode/binding/GJGameLevel.hpp>
#include <Geode/loader/Mod.hpp>

using namespace geode::prelude;
using namespace optional_settings;

$on_mod(Loaded) {
    auto mod = Mod::get();
    if (mod->setSavedValue("migrated-colors", true)) return;

    constexpr std::array settings = {
        "normal-color",
        "daily-color",
        "weekly-color",
        "event-color",
        "gauntlet-color"
    };

    auto& data = mod->getSavedSettingsData();
    for (auto key : settings) {
        if (auto setting = std::static_pointer_cast<OptionalColor3BSetting>(mod->getSetting(key))) {
            if (auto color = data.get<ccColor3B>(key)) {
                setting->setStoredValue(color.unwrap());
                setting->setEnabled(true);
            }
        }
    }
}

OptionalColor3BSetting* LevelInfoColors::settingForLevel(GJGameLevel* level) {
    auto dailyID = level->m_dailyID.value();
    const char* key = nullptr;
    if (dailyID > 0 && dailyID <= 100000) key = "daily-color";
    else if (dailyID > 100000 && dailyID <= 200000) key = "weekly-color";
    else if (dailyID > 200000) key = "event-color";
    else if (level->m_gauntletLevel) key = "gauntlet-color";
    else key = "normal-color";
    return std::static_pointer_cast<OptionalColor3BSetting>(Mod::get()->getSetting(key)).get();
}
