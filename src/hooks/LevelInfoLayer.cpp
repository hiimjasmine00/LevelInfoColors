#include "../classes/LICColorPopup.hpp"
#include <Geode/binding/GJGameLevel.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(LICLevelInfoLayer, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        if (auto background = static_cast<CCSprite*>(getChildByID("background"))) {
            auto mod = Mod::get();
            auto dailyID = level->m_dailyID.value();
            if (dailyID > 0 && dailyID < 100000) background->setColor(mod->getSettingValue<ccColor3B>("daily-color"));
            else if (dailyID >= 100000 && dailyID < 200000) background->setColor(mod->getSettingValue<ccColor3B>("weekly-color"));
            else if (dailyID >= 200000) background->setColor(mod->getSettingValue<ccColor3B>("event-color"));
            else if (level->m_gauntletLevel) background->setColor(mod->getSettingValue<ccColor3B>("gauntlet-color"));
            else background->setColor(mod->getSettingValue<ccColor3B>("normal-color"));
        }

        auto colorButton = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSpriteFrameName("GJ_paintBtn_001.png", 1.0f), this, menu_selector(LICLevelInfoLayer::onPickColor));
        colorButton->setID("color-button"_spr);
        auto leftSideMenu = getChildByID("left-side-menu");
        leftSideMenu->addChild(colorButton);
        leftSideMenu->updateLayout();

        return true;
    }

    void onPickColor(CCObject*) {
        auto dailyID = m_level->m_dailyID.value();
        auto isWeekly = dailyID >= 100000 && dailyID < 200000;
        auto isEvent = dailyID >= 200000;
        auto isGauntlet = m_level->m_gauntletLevel;
        auto background = static_cast<CCSprite*>(getChildByID("background"));

        auto defaultColor = isEvent ? ccColor3B { 99, 24, 126 } : isWeekly || isGauntlet ? ccColor3B { 51, 51, 51 } : ccColor3B { 0, 102, 255 };
        LICColorPopup::create(background, background ? background->getColor() : defaultColor,
            defaultColor, dailyID > 0 && dailyID < 100000, isWeekly, isEvent, isGauntlet)->show();
    }
};
