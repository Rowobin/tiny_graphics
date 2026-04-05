# tiny_graphics

> A tiny graphics + physics engine written for the even tinier raspberry pi pico.

## Why

I'm on a journey to learn more about bare-metal embedded development. I decided to build a project that mixes this goal with my love for computer graphics.

## Features

Right now, tiny_graphics has implemented all the features required for a 2D graphics library. You can:
- draw points, lines and shapes
- translate, scale and rotate those points, lines and shapes
- write text on the screen
- draw 1-bit sprites
- use 1-bit sprites as textures for shapes
- control multiple screens simultaneously

The features required for a physics engine are still in development.

### What hardware can I use this library with?

**Microcontrollers:** any microcontroller with an RP2040/RP2350 MCU.

**Displays:** SSD1306 and SH1107.

## Quick Start

- Install the [Pi Pico extension for VS Code](https://pip-assets.raspberrypi.com/categories/610-raspberry-pi-pico/documents/RP-008276-DS-1-getting-started-with-pico.pdf?disposition=inline).
- Using the Pi Pico extension menu on VS Code, select "New C/C++ project.
- Configure the project according to your preferences.
- Once the project has been created, add "tiny_graphics.h" and "tiny_graphics.c" to it.
- Add "tiny_graphics.c" to the executables in "CMakeLists.txt":
  ````cmake
  add_executable(setup_test
    main.c
    tiny_graphics.c
  )
  ````
- Add "hardware_i2c" to the target link libraries in "CMakeLists.txt":
  ````cmake
  target_link_libraries(setup_test
        pico_stdlib
        hardware_i2c
  )
  ````
- Add the following code to "main.c":
  ````c
  #include <stdio.h>
  #include "pico/stdlib.h"
  #include "hardware/i2c.h"
  
  #include "../../tiny_graphics.h"
  
  int main()
  {
      // init pico sdk
      stdio_init_all();
  
      // create a variable for the display
      int h = 64;
      int w = 128;
      int buf_size = w * (h/8);
      uint8_t buf[buf_size];
      display ssd1306 = {
          .i2c = i2c0,
          .baudrate = 400000,
          .gpio_scl = 17,
          .gpio_sda = 16,
          .address = 0x3C,
          .width = w,
          .height = h,
          .buf = buf,
          .type = SSD1306
      };
  
      // start i2c connection
      init_i2c(&ssd1306);
  
      // turn on display
      init_display(&ssd1306);
      sleep_ms(1000);
  
      // by default, when a display is turned on, all of its pixels are
      // forcefully set to "on" regardless of the content stored in RAM
      // calling "all_ram" will make pixels follow the RAM values
      memset(ssd1306.buf, 0, buf_size);
      render(&ssd1306);
      all_ram(&ssd1306);
      sleep_ms(1000);
  
      // write some text to the screen
      draw_text(&ssd1306, "Hello, World!", (vec2){0,0}, (vec2f){1.0, 1.0f}, true);
      render(&ssd1306);
  }
  ````

## Examples

This library has a few basic examples to showcase core features.

### How to run any example
- Install the [Pi Pico extension for VS Code](https://pip-assets.raspberrypi.com/categories/610-raspberry-pi-pico/documents/RP-008276-DS-1-getting-started-with-pico.pdf?disposition=inline).
- Clone the repository with Git.
- Using the Pi Pico extension menu on VS Code, select "Import Project" and then select the directory for whatever example you want to run.
- After importing the example, you should be able to run it like any other Pi Pico project.

## Contributing

If you want to contribute, by adding new features or improving existing ones, feel free to open a PR!

## License

This project is licensed using the [Unlicense](https://unlicense.org/).
