#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>
#include <hiimjasmine00.optional_settings/include/OptionalColor3BSetting.hpp>

class LICColorPopup : public geode::Popup<cocos2d::CCSprite*, GJGameLevel*>, public cocos2d::extension::ColorPickerDelegate {
protected:
    cocos2d::ccColor3B m_color;
    cocos2d::ccColor3B m_originalColor;
    cocos2d::ccColor3B m_defaultColor;
    cocos2d::extension::CCControlColourPicker* m_picker;
    cocos2d::CCSprite* m_target;
    geode::TextInput* m_rInput;
    geode::TextInput* m_gInput;
    geode::TextInput* m_bInput;
    geode::TextInput* m_hexInput;
    cocos2d::CCSprite* m_newColorSpr;
    CCMenuItemSpriteExtra* m_resetBtn;
    CCMenuItemSpriteExtra* m_hardResetBtn;
    optional_settings::OptionalColor3BSetting* m_setting;
    bool m_enabled;

    bool setup(cocos2d::CCSprite*, GJGameLevel*) override;
    void updateState(CCNode* = nullptr);
    void colorValueChanged(cocos2d::ccColor3B) override;
    void onClose(CCObject*) override;
public:
    static LICColorPopup* create(cocos2d::CCSprite*, GJGameLevel*);
};
