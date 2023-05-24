#include "touch_panel.hpp"
#include <stdio.h>

namespace esphome
{
  namespace touch_panel
  {

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

    const uint8_t PREFIX[] = {0xAA, 0x55, 0x01, 0x02};
    const unsigned int PREFIX_LENGTH = sizeof(PREFIX) / sizeof(PREFIX[0]);
    // Messages consist of a prefix, a type of action and a position.
    // There's probably other stuff but that's not relevant for us
    const unsigned int MESSAGE_SIZE = PREFIX_LENGTH + 4;
    const unsigned int BUFFER_SIZE = 32;

    TouchPanel::TouchPanel(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

    void TouchPanel::setup()
    {
      for (int i = 0; i < button_map.size(); i++)
        button_map[i]->publish_state(i < TwoFinger);
    }

    void TouchPanel::loop()
    {
      static uint8_t buffer[BUFFER_SIZE];
      while (available() >= MESSAGE_SIZE)
      {
        read_array(buffer, MIN(available(), BUFFER_SIZE));
        bool match = true;

        if (memcmp(buffer, PREFIX, PREFIX_LENGTH) != 0)
        {
          continue;
        }

        if (match)
        {
          TouchEvent event = static_cast<TouchEvent>(buffer[4]);
          uint8_t released_position = buffer[5];
          uint8_t pressed_position = buffer[6];

          if (event == Pressed)
          {
            // ESP_LOGD("custom", "Pressed: %d", pressed_position);
            button_map[pressed_position]->publish_state(true);

            // Always trigger the two-fingered and drag events since we can only detect when they are released
            two_finger->publish_state(true);
            dragged_ltr->publish_state(true);
            dragged_rtl->publish_state(true);
          }
          else if (event == Released || event == Dragged)
          {
            // Make sure to reset all buttons
            for (int i = 0; i < TwoFinger; i++)
              button_map[i]->publish_state(false);

            button_map[released_position]->publish_state(false);
          }
          else
          {
            ESP_LOGD("custom", "Unknown event: %d", event);
          }
        }
      }
    }
  } // namespace touch_panel
} // namespace esphome
