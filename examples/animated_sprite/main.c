#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "../../tiny_graphics.h"

#include "static.h"
#include "animated.h"

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

    // importing a static sprite
    // uint8_t static_cats_data[] = STATIC_SPRITE;
    // sprite static_cats = {STATIC_WIDTH, STATIC_HEIGHT, static_cats_data};

    // importing an animated sprite
    uint8_t animated_cats_data[] = ANIMATED_SPRITE;
    uint width = ANIMATED_WIDTH;
    uint height = ANIMATED_HEIGHT;
    sprite animated_cats[ANIMATED_FRAMES];
    for(int i = 0; i < ANIMATED_FRAMES; i++){
        animated_cats[i] = (sprite){width, height, &animated_cats_data[(width * (height / 8))*i]};
    }

    vec2 square[4] = {
        {0, 0},
        {animated_cats[0].width, 0},
        {animated_cats[0].width, animated_cats[0].height},
        {0, animated_cats[0].height}
    };

    vec2f tex[4] = {
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
        {0.0, 1.0}
    };

    int frame = 0;
    while(true){
        // clear screen
        memset(ssd1306.buf, 0, buf_size);

        // draw static sprite
        // draw_shape_fill_sprite(&ssd1306, square, tex, 4, &static_cats, false);

        // draw animated sprite
        draw_shape_fill_sprite(&ssd1306, square, tex, 4, &animated_cats[frame], false);

        // send buffer data to display
        render(&ssd1306);

        // next frame
        frame++;
        frame = frame % (ANIMATED_FRAMES - 1);

        // this sleep time limits our display to 12 FPS
        sleep_ms(1000 / 12);
    }
}