#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>

class LICColorPopup :
    public geode::Popup<cocos2d::CCSprite*, cocos2d::ccColor3B const&, cocos2d::ccColor3B const&, bool, bool, bool, bool>,
    public cocos2d::extension::ColorPickerDelegate
{
protected:
    cocos2d::ccColor3B m_color;
    cocos2d::ccColor3B m_originalColor;
    cocos2d::ccColor3B m_defaultColor;
    cocos2d::extension::CCControlColourPicker* m_picker;
    geode::TextInput* m_rInput;
    geode::TextInput* m_gInput;
    geode::TextInput* m_bInput;
    geode::TextInput* m_hexInput;
    cocos2d::CCSprite* m_newColorSpr;
    CCMenuItemSpriteExtra* m_resetBtn;
    CCMenuItemSpriteExtra* m_hardResetBtn;

    bool setup(cocos2d::CCSprite*, cocos2d::ccColor3B const&, cocos2d::ccColor3B const&, bool, bool, bool, bool) override;
    void updateState(CCNode* except = nullptr);
    void colorValueChanged(cocos2d::ccColor3B) override;
    void onClose(CCObject*) override;
public:
    static LICColorPopup* create(cocos2d::CCSprite*, cocos2d::ccColor3B const&, cocos2d::ccColor3B const&, bool, bool, bool, bool);
};
