#include "LICColorPopup.hpp"
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/loader/Mod.hpp>

using namespace geode::prelude;

LICColorPopup* LICColorPopup::create(CCSprite* target, const ccColor3B& color, const ccColor3B& defaultColor, bool isDaily, bool isWeekly, bool isEvent, bool isGauntlet) {
    auto ret = new LICColorPopup();
    if (ret->initAnchored(400.0f, 240.0f, target, color, defaultColor, isDaily, isWeekly, isEvent, isGauntlet)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool LICColorPopup::setup(CCSprite* target, const ccColor3B& color, const ccColor3B& defaultColor, bool isDaily, bool isWeekly, bool isEvent, bool isGauntlet) {
    setID("LICColorPopup");
    setTitle("Select Color");
    m_title->setID("select-color-title");
    m_mainLayer->setID("main-layer");
    m_buttonMenu->setID("button-menu");
    m_bgSprite->setID("background");
    m_closeBtn->setID("close-button");
    m_noElasticity = true;

    m_color = color;
    m_originalColor = color;
    m_defaultColor = defaultColor;

    auto pickerRow = CCLayer::create();
    pickerRow->setLayout(RowLayout::create()->setGap(10.0f)->setAxisAlignment(AxisAlignment::Start)->setAutoGrowAxis(0));
    pickerRow->setPosition({ 200.0f, 120.0f });
    pickerRow->setID("picker-row");
    m_mainLayer->addChild(pickerRow);

    auto colorMenu = CCMenu::create();
    colorMenu->setLayout(ColumnLayout::create()->setGap(0.0f)->setAxisReverse(true)->setAutoScale(false)->setAxisAlignment(AxisAlignment::Start)->setAutoGrowAxis(0));
    colorMenu->setID("color-menu");
    pickerRow->addChild(colorMenu);

    m_picker = CCControlColourPicker::colourPicker();
    m_picker->setDelegate(this);
    m_picker->setColorTarget(target);
    m_picker->setPosition(m_picker->getContentSize() * 0.5f);
    m_picker->setID("color-picker");

    auto pickerWrapper = CCNode::create();
    pickerWrapper->setContentSize(m_picker->getContentSize());
    pickerWrapper->addChild(m_picker);
    pickerWrapper->setID("picker-wrapper");
    pickerRow->addChild(pickerWrapper);

    auto oldColorSpr = CCSprite::createWithSpriteFrameName("whiteSquare60_001.png");
    oldColorSpr->setColor(color);
    oldColorSpr->setID("old-color-sprite");
    colorMenu->addChild(oldColorSpr);

    m_newColorSpr = CCSprite::createWithSpriteFrameName("whiteSquare60_001.png");
    m_newColorSpr->setColor(color);
    m_newColorSpr->setID("new-color-sprite");
    colorMenu->addChild(m_newColorSpr);

    auto resetBtnSpr = ButtonSprite::create(CCSprite::createWithSpriteFrameName("geode.loader/reset-gold.png"), 32, true, 0.0f, "GJ_button_01.png", 1.25f);
    resetBtnSpr->setScale(0.6f);
    m_resetBtn = CCMenuItemExt::createSpriteExtra(resetBtnSpr, [this](auto) {
        m_color = m_originalColor;
        updateState();
    });
    m_resetBtn->setLayoutOptions(AxisLayoutOptions::create()->setPrevGap(10.0f)->setNextGap(10.0f));
    m_resetBtn->setID("reset-button");
    colorMenu->addChild(m_resetBtn);

    auto hardResetBtnSpr = ButtonSprite::create(CCSprite::createWithSpriteFrameName("geode.loader/reset-gold.png"), 32, true, 0.0f, "GJ_button_02.png", 1.25f);
    hardResetBtnSpr->setScale(0.6f);
    m_hardResetBtn = CCMenuItemExt::createSpriteExtra(hardResetBtnSpr, [this](auto) {
        m_color = m_defaultColor;
        updateState();
    });
    m_hardResetBtn->setLayoutOptions(AxisLayoutOptions::create()->setPrevGap(10.0f)->setNextGap(10.0f));
    m_hardResetBtn->setID("hard-reset-button");
    colorMenu->addChild(m_hardResetBtn);

    auto inputColumn = CCLayer::create();
    inputColumn->setLayout(ColumnLayout::create()->setGap(3.0f)->setAxisReverse(true)->setAxisAlignment(AxisAlignment::Start)->setAutoGrowAxis(0));
    inputColumn->setID("input-column");
    pickerRow->addChild(inputColumn);

    auto rgbRow = CCLayer::create();
    rgbRow->setLayout(RowLayout::create()->setGap(5.0f)->setAxisAlignment(AxisAlignment::Start)->setAutoGrowAxis(0));
    rgbRow->setID("rgb-row");
    inputColumn->addChild(rgbRow);

    auto rColumn = CCLayer::create();
    rColumn->setLayout(ColumnLayout::create()->setGap(3.0f)->setAxisReverse(true)->setAutoScale(false)->setAxisAlignment(AxisAlignment::Start)->setAutoGrowAxis(0));
    rColumn->setID("r-column");
    rgbRow->addChild(rColumn);

    auto rText = CCLabelBMFont::create("R", "goldFont.fnt");
    rText->setScale(0.55f);
    rText->setID("r-text");
    rColumn->addChild(rText);

    m_rInput = TextInput::create(50.0f, "R");
    m_rInput->setScale(0.7f);
    m_rInput->setCommonFilter(CommonFilter::Uint);
    m_rInput->setCallback([this](const std::string& text) {
        m_color.r = text.empty() ? m_color.r : numFromString<uint8_t>(text).unwrapOr(255);
        updateState(m_rInput);
    });
    m_rInput->setID("r-input");
    rColumn->addChild(m_rInput);

    rColumn->updateLayout();
    rColumn->setContentSize(calculateChildCoverage(rColumn).size);

    auto gColumn = CCLayer::create();
    gColumn->setLayout(ColumnLayout::create()->setGap(3.0f)->setAxisReverse(true)->setAutoScale(false)->setAxisAlignment(AxisAlignment::Start)->setAutoGrowAxis(0));
    gColumn->setID("g-column");
    rgbRow->addChild(gColumn);

    auto gText = CCLabelBMFont::create("G", "goldFont.fnt");
    gText->setScale(0.55f);
    gText->setID("g-text");
    gColumn->addChild(gText);

    m_gInput = TextInput::create(50.0f, "G");
    m_gInput->setScale(0.7f);
    m_gInput->setCommonFilter(CommonFilter::Uint);
    m_gInput->setCallback([this](const std::string& text) {
        m_color.g = text.empty() ? m_color.g : numFromString<uint8_t>(text).unwrapOr(255);
        updateState(m_gInput);
    });
    m_gInput->setID("g-input");
    gColumn->addChild(m_gInput);

    gColumn->updateLayout();
    gColumn->setContentSize(calculateChildCoverage(gColumn).size);

    auto bColumn = CCLayer::create();
    bColumn->setLayout(ColumnLayout::create()->setGap(3.0f)->setAxisReverse(true)->setAutoScale(false)->setAxisAlignment(AxisAlignment::Start)->setAutoGrowAxis(0));
    bColumn->setID("b-column");
    rgbRow->addChild(bColumn);

    auto bText = CCLabelBMFont::create("B", "goldFont.fnt");
    bText->setScale(0.55f);
    bText->setID("b-text");
    bColumn->addChild(bText);

    m_bInput = TextInput::create(50.0f, "B");
    m_bInput->setScale(0.7f);
    m_bInput->setCommonFilter(CommonFilter::Uint);
    m_bInput->setCallback([this](const std::string& text) {
        m_color.b = text.empty() ? m_color.b : numFromString<uint8_t>(text).unwrapOr(255);
        updateState(m_bInput);
    });
    m_bInput->setID("b-input");
    bColumn->addChild(m_bInput);

    bColumn->updateLayout();
    bColumn->setContentSize(calculateChildCoverage(bColumn).size);

    auto hexColumn = CCLayer::create();
    hexColumn->setLayout(ColumnLayout::create()->setGap(3.0f)->setAxisReverse(true)->setAutoScale(false)->setAxisAlignment(AxisAlignment::Start)->setAutoGrowAxis(0));
    hexColumn->setID("hex-column");
    inputColumn->addChild(hexColumn);

    auto hexText = CCLabelBMFont::create("Hex", "goldFont.fnt");
    hexText->setScale(0.55f);
    hexText->setID("hex-text");
    hexColumn->addChild(hexText);

    m_hexInput = TextInput::create(165.0f, "Hex");
    m_hexInput->setScale(0.7f);
    m_hexInput->setCommonFilter(CommonFilter::Hex);
    m_hexInput->setCallback([this](const std::string& text) {
        if (auto colorRes = cc3bFromHexString(text, true)) m_color = colorRes.unwrap();
        updateState(m_hexInput);
    });
    m_hexInput->setID("hex-input");
    hexColumn->addChild(m_hexInput);

    hexColumn->updateLayout();
    rgbRow->updateLayout();
    inputColumn->updateLayout();
    colorMenu->updateLayout();
    pickerRow->updateLayout();

    updateState();

    auto okBtnSpr = ButtonSprite::create("OK");
    okBtnSpr->setScale(0.7f);
    auto okBtn = CCMenuItemExt::createSpriteExtra(okBtnSpr, [this, isDaily, isWeekly, isEvent, isGauntlet](auto) {
        auto mod = Mod::get();
        if (isDaily) mod->setSettingValue("daily-color", m_color);
        else if (isWeekly) mod->setSettingValue("weekly-color", m_color);
        else if (isEvent) mod->setSettingValue("event-color", m_color);
        else if (isGauntlet) mod->setSettingValue("gauntlet-color", m_color);
        else mod->setSettingValue("normal-color", m_color);
        Popup::onClose(nullptr);
    });
    okBtn->setPosition({ 200.0f, 20.0f });
    okBtn->setID("ok-button");
    m_buttonMenu->addChild(okBtn);

    return true;
}

void LICColorPopup::updateState(CCNode* except) {
    if (except != m_rInput) m_rInput->setString(std::to_string(m_color.r));
    if (except != m_gInput) m_gInput->setString(std::to_string(m_color.g));
    if (except != m_bInput) m_bInput->setString(std::to_string(m_color.b));
    if (except != m_hexInput) m_hexInput->setString(cc3bToHexString(m_color));
    if (except != m_picker) {
        m_picker->setDelegate(nullptr);
        m_picker->setColorValue(m_color);
        m_picker->setDelegate(this);
    }

    m_resetBtn->setVisible(m_color != m_originalColor);
    m_hardResetBtn->setVisible(m_color != m_defaultColor);
    m_newColorSpr->setColor(m_color);
}

void LICColorPopup::colorValueChanged(ccColor3B color) {
    m_color = color;
    updateState(m_picker);
}

void LICColorPopup::onClose(CCObject* sender) {
    m_picker->getColorTarget()->setColor(m_originalColor);
    Popup::onClose(sender);
}
