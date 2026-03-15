#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "../../tiny_graphics.h"

#include "skelly.h"

// wrap_sprite is a method that uses draw_shape_fill_sprite to
// draw a sprite and "fake" that the sprite is wrapping around the screen
//
// this is not the most optimal implementation of this method, but it's a 
// good example of the types of abstractions that can be built on top of tiny_graphics
void wrap_sprite(display* display, vec2* shape, vec2f* tex, int size, sprite* sprite, bool inverted);

int main()
{
    // init pico sdk
    stdio_init_all();

    // create a variable for the display
    int h = 128;
    int w = 128;
    int buf_size = w * (h/8);
    uint8_t buf[buf_size];
    display sh1107 = {
        .i2c = i2c1,
        .baudrate = 400000,
        .gpio_scl = 19,
        .gpio_sda = 18,
        .address = 0x3C,
        .width = w,
        .height = h,
        .buf = buf,
        .type = SH1107
    };

    // start i2c connection
    init_i2c(&sh1107);

    // turn on display
    init_display(&sh1107);

    // by default, when a display is turned on, all of its pixels are
    // forcefully set to "on" regardless of the content stored in RAM
    // calling "all_ram" will make pixels follow the RAM values
    memset(sh1107.buf, 0, buf_size);
    render(&sh1107);
    all_ram(&sh1107);

    // import sprite data
    // the script in "/utils" can be used to convert png files
    // into read to use header files
    uint8_t data[] = SKELLY_SPRITE;
    sprite skelly = { SKELLY_WIDTH, SKELLY_HEIGHT, data};

    // this example uses draw_shape_wrap_fill, which draws
    // a sprite on top of a pre existing shape
    vec2 square[4] = {
        {0, 32},
        {32, 32},
        {32, 64},
        {0, 64}
    };

    // sprite texture coordinates for each shape vertex
    vec2f square_tex[4] = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}
    };

    while(true){
        // clear screen
        memset(sh1107.buf, 0, buf_size);

        // translate square
        translate_points(square, 4, (vec2){4,2});

        // draw sprite (wrapping around the screen)
        wrap_sprite(&sh1107, square, square_tex, 4, &skelly, false);

        // send buffer data to display
        render(&sh1107);

        // this sleep time limits our display to 12 FPS
        sleep_ms(1000 / 12);
    }
}

void wrap_sprite(display* display, vec2* shape, vec2f* tex, int size, sprite* sprite, bool inverted){    
    bool reset_x_under = true;
    bool reset_x_over = true;
    bool reset_y_under = true;
    bool reset_y_over = true;
    for(int i = 0; i < size; i++){
        if(shape[i].x < display->width) reset_x_over = false;
        if(shape[i].x >= 0) reset_x_under = false;
        if(shape[i].y < display->height) reset_y_over = false;
        if(shape[i].y >= 0) reset_y_under = false;
    }

    for(int i = 0; i < size; i++){
        if(reset_x_over) shape[i].x -= display->width;
        if(reset_x_under) shape[i].x += display->width;
        if(reset_y_over) shape[i].y -= display->height;
        if(reset_y_under) shape[i].y += display->height;
    }

    for(int dy = -1; dy <= 1; dy++){
        for(int dx = -1; dx <= 1; dx++){
            vec2 shape_cpy[size];
            for(int i = 0; i < size; i++){
                shape_cpy[i].x = shape[i].x + display->width * dx;
                shape_cpy[i].y = shape[i].y + display->height * dy;
            }
            draw_shape_fill_sprite(display, shape_cpy, tex, 4, sprite, inverted);
        }
    }
}