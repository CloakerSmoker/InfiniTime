#pragma once
#include <cstdint>
#include <bitset>
#include "components/brightness/BrightnessController.h"
#include "components/fs/FS.h"

namespace Pinetime {
  namespace Controllers {
    class Settings {
    public:
      enum class ClockType : uint8_t { H24, H12 };
      enum class Notification : uint8_t { On, Off, Sleep };
      enum class ChimesOption : uint8_t { None, Hours, HalfHours };
      enum class RefreshStyle : uint8_t { None, Slide, MixSlide };
      enum class FullRefreshDirections { None, Up, Down, Left, Right, LeftAnim, RightAnim };
      enum class WakeUpMode : uint8_t {
        SingleTap = 0,
        DoubleTap = 1,
        RaiseWrist = 2,
        Shake = 3,
      };
      enum class Colors : uint8_t {
        White,
        Silver,
        Gray,
        Black,
        Red,
        Maroon,
        Yellow,
        Olive,
        Lime,
        Green,
        Cyan,
        Teal,
        Blue,
        Navy,
        Magenta,
        Purple,
        Orange,
        Pink
      };
      enum class PTSGaugeStyle : uint8_t { Full, Half, Numeric };

      struct PineTimeStyle {
        Colors ColorTime = Colors::Teal;
        Colors ColorBar = Colors::Teal;
        Colors ColorBG = Colors::Black;
        PTSGaugeStyle gaugeStyle = PTSGaugeStyle::Full;
      };
      struct WatchFaceInfineat {
        bool showSideCover = true;
        int colorIndex = 0;
      };

      Settings(Pinetime::Controllers::FS& fs);

      Settings(const Settings&) = delete;
      Settings& operator=(const Settings&) = delete;
      Settings(Settings&&) = delete;
      Settings& operator=(Settings&&) = delete;

      void Init();
      void SaveSettings();

      void SetClockFace(uint8_t face) {
        if (face != settings.clockFace) {
          settingsChanged = true;
        }
        settings.clockFace = face;
      };
      uint8_t GetClockFace() const {
        return settings.clockFace;
      };

      void SetChimeOption(ChimesOption chimeOption) {
        if (chimeOption != settings.chimesOption) {
          settingsChanged = true;
        }
        settings.chimesOption = chimeOption;
      };
      ChimesOption GetChimeOption() const {
        return settings.chimesOption;
      };

      void SetPTSColorTime(Colors colorTime) {
        if (colorTime != settings.PTS.ColorTime)
          settingsChanged = true;
        settings.PTS.ColorTime = colorTime;
      };
      Colors GetPTSColorTime() const {
        return settings.PTS.ColorTime;
      };

      void SetPTSColorBar(Colors colorBar) {
        if (colorBar != settings.PTS.ColorBar)
          settingsChanged = true;
        settings.PTS.ColorBar = colorBar;
      };
      Colors GetPTSColorBar() const {
        return settings.PTS.ColorBar;
      };

      void SetPTSColorBG(Colors colorBG) {
        if (colorBG != settings.PTS.ColorBG)
          settingsChanged = true;
        settings.PTS.ColorBG = colorBG;
      };
      Colors GetPTSColorBG() const {
        return settings.PTS.ColorBG;
      };

      void SetInfineatShowSideCover(bool show) {
        if (show != settings.watchFaceInfineat.showSideCover) {
          settings.watchFaceInfineat.showSideCover = show;
          settingsChanged = true;
        }
      };
      bool GetInfineatShowSideCover() const {
        return settings.watchFaceInfineat.showSideCover;
      };

      void SetInfineatColorIndex(int index) {
        if (index != settings.watchFaceInfineat.colorIndex) {
          settings.watchFaceInfineat.colorIndex = index;
          settingsChanged = true;
        }
      };
      int GetInfineatColorIndex() const {
        return settings.watchFaceInfineat.colorIndex;
      };

      void SetPTSGaugeStyle(PTSGaugeStyle gaugeStyle) {
        if (gaugeStyle != settings.PTS.gaugeStyle)
          settingsChanged = true;
        settings.PTS.gaugeStyle = gaugeStyle;
      };
      PTSGaugeStyle GetPTSGaugeStyle() const {
        return settings.PTS.gaugeStyle;
      };

      void SetAppMenu(uint8_t menu) {
        appMenu = menu;
      };

      uint8_t GetAppMenu() const {
        return appMenu;
      };

      void SetSettingsMenu(uint8_t menu) {
        settingsMenu = menu;
      };
      uint8_t GetSettingsMenu() const {
        return settingsMenu;
      };

      void SetClockType(ClockType clocktype) {
        if (clocktype != settings.clockType) {
          settingsChanged = true;
        }
        settings.clockType = clocktype;
      };
      ClockType GetClockType() const {
        return settings.clockType;
      };

      void SetNotificationStatus(Notification status) {
        if (status != settings.notificationStatus) {
          settingsChanged = true;
        }
        settings.notificationStatus = status;
      };
      Notification GetNotificationStatus() const {
        return settings.notificationStatus;
      };

      void SetScreenTimeOut(uint32_t timeout) {
        if (timeout != settings.screenTimeOut) {
          settingsChanged = true;
        }
        settings.screenTimeOut = timeout;
      };

      uint32_t GetScreenTimeOut() const {
        return settings.screenTimeOut;
      };

      void SetShakeThreshold(uint16_t thresh) {
        if (settings.shakeWakeThreshold != thresh) {
          settings.shakeWakeThreshold = thresh;
          settingsChanged = true;
        }
      }

      int16_t GetShakeThreshold() const {
        return settings.shakeWakeThreshold;
      }

      void setWakeUpMode(WakeUpMode wakeUp, bool enabled) {
        if (enabled != isWakeUpModeOn(wakeUp)) {
          settingsChanged = true;
        }
        settings.wakeUpMode.set(static_cast<size_t>(wakeUp), enabled);
        // Handle special behavior
        if (enabled) {
          switch (wakeUp) {
            case WakeUpMode::SingleTap:
              settings.wakeUpMode.set(static_cast<size_t>(WakeUpMode::DoubleTap), false);
              break;
            case WakeUpMode::DoubleTap:
              settings.wakeUpMode.set(static_cast<size_t>(WakeUpMode::SingleTap), false);
              break;
            default:
              break;
          }
        }
      };

      std::bitset<4> getWakeUpModes() const {
        return settings.wakeUpMode;
      }

      bool isWakeUpModeOn(const WakeUpMode mode) const {
        return getWakeUpModes()[static_cast<size_t>(mode)];
      }

      void SetBrightness(Controllers::BrightnessController::Levels level) {
        if (level != settings.brightLevel) {
          settingsChanged = true;
        }
        settings.brightLevel = level;
      };

      Controllers::BrightnessController::Levels GetBrightness() const {
        return settings.brightLevel;
      };

      void SetStepsGoal(uint32_t goal) {
        if (goal != settings.stepsGoal) {
          settingsChanged = true;
        }
        settings.stepsGoal = goal;
      };

      uint32_t GetStepsGoal() const {
        return settings.stepsGoal;
      };

      void SetBleRadioEnabled(bool enabled) {
        bleRadioEnabled = enabled;
      };

      bool GetBleRadioEnabled() const {
        return bleRadioEnabled;
      };

      void SetHorizontalRefresh(RefreshStyle style) {
        if (settings.horizontalRefresh != style) {
          settings.horizontalRefresh = style;
          settingsChanged = true;
        }
      }

      RefreshStyle GetHorizontalRefresh() const {
        return settings.horizontalRefresh;
      }

      void SetVerticalRefresh(RefreshStyle style) {
        if (settings.verticalRefresh != style) {
          settings.verticalRefresh = style;
          settingsChanged = true;
        }
      }

      RefreshStyle GetVerticalRefresh() const {
        return settings.verticalRefresh;
      }

      FullRefreshDirections PickRefreshDirection(RefreshStyle style, FullRefreshDirections slide, FullRefreshDirections mixSlide) const {
        switch (style) {
          case RefreshStyle::None: return FullRefreshDirections::None;
          case RefreshStyle::Slide: return slide;
          case RefreshStyle::MixSlide: return mixSlide;
          default: return slide;
        }
      }

      FullRefreshDirections RemapRefreshDirection(FullRefreshDirections original) const {
        // LeftAnim/RightAnim actually refresh from the opposite direction so we handle RightAnim as a request for
        // a "left to right" refresh and emit it if we want to use RightAnim as the horizontal "left to right" refresh

        switch (original) {
          case FullRefreshDirections::Left:
          case FullRefreshDirections::RightAnim:
            return PickRefreshDirection(settings.horizontalRefresh, FullRefreshDirections::Left, FullRefreshDirections::RightAnim);
          case FullRefreshDirections::Right:
          case FullRefreshDirections::LeftAnim:
            return PickRefreshDirection(settings.horizontalRefresh, FullRefreshDirections::Right, FullRefreshDirections::LeftAnim);
          case FullRefreshDirections::Up:
            return PickRefreshDirection(settings.verticalRefresh, FullRefreshDirections::Up, FullRefreshDirections::Up);
          case FullRefreshDirections::Down:
            return PickRefreshDirection(settings.verticalRefresh, FullRefreshDirections::Down, FullRefreshDirections::Down);
          default:
            return original;
        }
      }


    private:
      Pinetime::Controllers::FS& fs;

      static constexpr uint32_t settingsVersion = 0x0004;
      struct SettingsData {
        uint32_t version = settingsVersion;
        uint32_t stepsGoal = 10000;
        uint32_t screenTimeOut = 15000;

        ClockType clockType = ClockType::H24;
        Notification notificationStatus = Notification::On;

        uint8_t clockFace = 0;
        ChimesOption chimesOption = ChimesOption::None;

        PineTimeStyle PTS;

        WatchFaceInfineat watchFaceInfineat;

        std::bitset<4> wakeUpMode {0};
        uint16_t shakeWakeThreshold = 150;
        Controllers::BrightnessController::Levels brightLevel = Controllers::BrightnessController::Levels::Medium;

        RefreshStyle horizontalRefresh = RefreshStyle::MixSlide;
        RefreshStyle verticalRefresh = RefreshStyle::Slide;
      };

      SettingsData settings;
      bool settingsChanged = false;

      uint8_t appMenu = 0;
      uint8_t settingsMenu = 0;
      uint8_t watchFacesMenu = 0;
      /* ble state is intentionally not saved with the other watch settings and initialized
       * to off (false) on every boot because we always want ble to be enabled on startup
       */
      bool bleRadioEnabled = true;

      void LoadSettingsFromFile();
      void SaveSettingsToFile();
    };
  }
}
