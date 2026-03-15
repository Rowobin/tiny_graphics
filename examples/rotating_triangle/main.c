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

    // by default, when a display is turned on, all of its pixels are
    // forcefully set to "on" regardless of the content stored in RAM
    // calling "all_ram" will make pixels follow the RAM values
    memset(ssd1306.buf, 0, buf_size);
    render(&ssd1306);
    all_ram(&ssd1306);

    // in tiny_graphics, shapes are just groups of vertices
    // to draw a triangle, we 3 vertices
    vec2 triangle[3] = {
        {0,0},
        {32, 0},
        {16, 32}
    };

    // move triangle to the center of the display
    translate_points(triangle, 3, (vec2){48,16});

    // get center point of the triangle
    vec2 center = calculate_center_point(triangle, 3);

    // define rotation angle
    float rotation = M_PI / 8;

    while(true){
        // clear screen
        memset(ssd1306.buf, 0, buf_size);

        // rotate triangle
        rotate_points(triangle, 3, rotation, center);

        // draw triangle to buffer
        draw_shape(&ssd1306, triangle, 3, true);

        // send buffer data to display
        render(&ssd1306);

        // this sleep time limits our display to 12 FPS
        sleep_ms(1000 / 12);
    }
}