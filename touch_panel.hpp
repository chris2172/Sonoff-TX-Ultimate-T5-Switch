#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

#include <vector>

namespace esphome
{
  namespace touch_panel
  {

    enum TouchEvent
    {
      Released = 1,
      Pressed = 2,
      Dragged = 3
    };

    enum TouchPosition
    {
      Left = 1,
      Middle = 4,
      Right = 7,
      TwoFinger = 11,
      DraggedLTR = 12,
      DraggedRTL = 13
    };

    class TouchPanel : public Component, public uart::UARTDevice
    {
    public:
      TouchPanel(uart::UARTComponent *parent);
      void setup() override;
      void loop() override;
      float get_setup_priority() const override { return esphome::setup_priority::BUS; }

      binary_sensor::BinarySensor *left = new binary_sensor::BinarySensor();
      binary_sensor::BinarySensor *middle = new binary_sensor::BinarySensor();
      binary_sensor::BinarySensor *right = new binary_sensor::BinarySensor();
      binary_sensor::BinarySensor *two_finger = new binary_sensor::BinarySensor();
      binary_sensor::BinarySensor *dragged_ltr = new binary_sensor::BinarySensor();
      binary_sensor::BinarySensor *dragged_rtl = new binary_sensor::BinarySensor();

    protected:
      // For positional tracking
      std::vector<binary_sensor::BinarySensor *> button_map = {
          left, // 0 never occurs but is here for completeness
          left, // 1-3 is left
          left,
          left,
          middle, // 4-6 is middle
          middle,
          middle,
          right, // 7-10 is right
          right,
          right,
          right,
          two_finger,  // 11 is two fingers (released only)
          dragged_ltr, // 12 is drag left to right
          dragged_rtl, // 13 is drag right to left
      };
    };

  } // namespace adalight
} // namespace esphome
