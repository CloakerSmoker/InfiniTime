#pragma once

#include <array>
#include <cstdint>
#include <lvgl/lvgl.h>

#include "displayapp/screens/ScreenList.h"
#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/Symbols.h"

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class SettingRefreshStyles : public Screen {
      public:
        SettingRefreshStyles(DisplayApp* app, Pinetime::Controllers::Settings& settingsController);
        ~SettingRefreshStyles() override;

        bool OnTouchEvent(TouchEvents event) override;

      private:
        Controllers::Settings& settingsController;

        ScreenList<2> screens;

        static constexpr const char* symbol = Symbols::sun;

        std::unique_ptr<Screen> CreateScreenHorizontal();
        std::unique_ptr<Screen> CreateScreenVertical();
      };
    }
  }
}
