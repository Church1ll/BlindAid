#pragma once

#define HORZ_REGIONS 3
#define VERT_REGIONS 5

// Interface for detection module parameters.
class IParameters
{
public:
  // TODO: check that data is valid when received by a module.
  // virtual bool Valid() = 0;

  enum Toggle
  {
    Disabled,
    Enabled
  };

  enum Mode
  {
    Realtime,
    Simulate
  };

  Toggle GetToggle() { return _toggle; }
  void SetToggle(Toggle toggle) { _toggle = toggle; }

  Mode GetMode() { return _mode; }
  void SetMode(Mode mode) { _mode = mode; }

private:
  // allows toggling a module between enabled and disabled.
  Toggle _toggle = Toggle::Enabled;

  // allows switching a module from realtime to simulation modes.
  Mode _mode = Mode::Realtime;
};