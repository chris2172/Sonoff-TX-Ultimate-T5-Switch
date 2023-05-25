# Sonoff-TX-Ultimate-T5-Switch

I could not have produced this without the hard work from https://gist.github.com/wolph/42024a983e4dfb0bc1dcbe6882979d21
Who is the genius behind the code that I altered for my own needs.

# Flashing TX Ultimate
![2023-05-25 11 23 06](https://github.com/chris2172/Sonoff-TX-Ultimate-T5-Switch/assets/11930805/b566df68-b753-4c71-b398-a3a891d231b6)
![image](https://github.com/chris2172/Sonoff-TX-Ultimate-T5-Switch/assets/11930805/4b2242b3-7521-4e22-b144-7d6f9c78cf60)

To enable boot mode to allow flashing connect the Ground Pin Hedder to the boot solder point highlited with the pink line
![2023-05-25 11 28 54](https://github.com/chris2172/Sonoff-TX-Ultimate-T5-Switch/assets/11930805/2c64072e-c4c6-4a53-9887-9af410d21c47)

Here I am using the white wire to enable boot and only connect it till the screen says erasing.
![2023-05-25 11 35 13](https://github.com/chris2172/Sonoff-TX-Ultimate-T5-Switch/assets/11930805/78573f3f-3220-4fc0-9eb2-6291fcb2f3ca)

# Working with code
Please make sure the 2 files touch_panel.hpp & touch_panel.cpp are in the config/esphome directory of home assistant so they upload with the yaml config
