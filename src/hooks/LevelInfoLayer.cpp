#include "../LevelInfoColors.hpp"
#include "../classes/LICColorPopup.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

class $modify(LICLevelInfoLayer, LevelInfoLayer) {
    struct Fields {
        CCSprite* m_background = nullptr;
    };

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        if (auto background = static_cast<CCSprite*>(getChildByID("background"))) {
            if (auto setting = LevelInfoColors::settingForLevel(m_level)) {
                if (setting->isEnabled()) background->setColor(setting->getStoredValue());
            }

            if (auto leftSideMenu = getChildByID("left-side-menu")) {
                auto colorButton = CCMenuItemSpriteExtra::create(
                    CircleButtonSprite::createWithSpriteFrameName("GJ_paintBtn_001.png", 1.0f),
                    this, menu_selector(LICLevelInfoLayer::onPickColor)
                );
                colorButton->setID("color-button"_spr);
                leftSideMenu->addChild(colorButton);
                leftSideMenu->updateLayout();
            }

            m_fields->m_background = background;
        }

        return true;
    }

    void onPickColor(CCObject*) {
        LICColorPopup::create(m_fields->m_background, m_level)->show();
    }
};
