#include <Geode/binding/FLAlertLayerProtocol.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>
#include <hiimjasmine00.optional_settings/include/OptionalColor3BSetting.hpp>

class LICColorPopup : public geode::Popup, public TextInputDelegate, public FLAlertLayerProtocol, public cocos2d::extension::ColorPickerDelegate {
protected:
    cocos2d::ccColor3B m_color;
    cocos2d::ccColor3B m_originalColor;
    cocos2d::ccColor3B m_defaultColor;
    cocos2d::ccColor3B m_queuedColor;
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

    bool init(cocos2d::CCSprite*, GJGameLevel*);
    void onEnable(cocos2d::CCObject*);
    void onReset(cocos2d::CCObject*);
    void onHardReset(cocos2d::CCObject*);
    void FLAlert_Clicked(FLAlertLayer*, bool) override;
    void onConfirm(cocos2d::CCObject*);
    void textChanged(CCTextInputNode*) override;
    void updateState(cocos2d::CCNode* = nullptr);
    void colorValueChanged(cocos2d::ccColor3B) override;
    void onClose(cocos2d::CCObject*) override;
public:
    static LICColorPopup* create(cocos2d::CCSprite*, GJGameLevel*);
};
