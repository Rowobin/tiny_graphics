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
    draw_text(&ssd1306, "Hello, world!", (vec2){0,0}, (vec2f){1.0, 1.0f}, true);
    render(&ssd1306);
}
