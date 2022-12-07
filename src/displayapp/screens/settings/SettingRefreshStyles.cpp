#include "displayapp/screens/settings/SettingRefreshStyles.h"
#include <lvgl/lvgl.h>

#include "displayapp/screens/CheckboxList.h"

using namespace Pinetime::Applications::Screens;

SettingRefreshStyles::SettingRefreshStyles(Pinetime::Applications::DisplayApp* app,
                               Pinetime::Controllers::Settings& settingsController)
  : Screen(app),
    settingsController {settingsController},
    screens {app,
             0,
             {[this]() -> std::unique_ptr<Screen> {
                return CreateScreenHorizontal();
             },
             [this]() -> std::unique_ptr<Screen> {
                return CreateScreenVertical();
             }},
             Screens::ScreenListModes::UpDown} {
}

SettingRefreshStyles::~SettingRefreshStyles() {
  lv_obj_clean(lv_scr_act());
}

bool SettingRefreshStyles::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  return screens.OnTouchEvent(event);
}

std::unique_ptr<Screen> SettingRefreshStyles::CreateScreenHorizontal() {
  std::array<Screens::CheckboxList::Item, 4> styles {
    {{"None", true}, {"Slide", true}, {"Mix and slide", true}, {"", false}}};
  return std::make_unique<Screens::CheckboxList>(
    0,
    1,
    app,
    "Horizontal",
    symbol,
    (uint32_t)settingsController.GetHorizontalRefresh(),
    [&settings = settingsController](uint32_t style) {
      settings.SetHorizontalRefresh((Controllers::Settings::RefreshStyle)style);
      settings.SaveSettings();
    },
    styles);
}

std::unique_ptr<Screen> SettingRefreshStyles::CreateScreenVertical() {
  std::array<Screens::CheckboxList::Item, 4> styles {
    {{"None", true}, {"Slide", true}, {"", false}, {"", false}}};
  return std::make_unique<Screens::CheckboxList>(
    0,
    1,
    app,
    "Vertical",
    symbol,
    (uint32_t)settingsController.GetVerticalRefresh(),
    [&settings = settingsController](uint32_t style) {
      settings.SetVerticalRefresh((Controllers::Settings::RefreshStyle)style);
      settings.SaveSettings();
    },
    styles);
}