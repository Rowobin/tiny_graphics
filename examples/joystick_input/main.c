#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"

#include "../../tiny_graphics.h"

#define VRX_PIN 26
#define VRY_PIN 27
#define SW_PIN 22

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

    // adc set up
    adc_init();
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);

    gpio_init(SW_PIN);
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_pull_up(SW_PIN);

    // turn on display
    init_display(&sh1107);
    memset(sh1107.buf, 0, buf_size);
    all_ram(&sh1107);

    while(true){
        memset(sh1107.buf, 0, buf_size);

        adc_select_input(0);
        int16_t x = adc_read() - 2048;
        char buf[12];
        sprintf(buf, "X: %d", x);
        draw_text(&sh1107, buf, (vec2){0, 16}, (vec2f){1.0f, 1.0f}, true);

        adc_select_input(1);
        int16_t y = adc_read() - 2048;
        sprintf(buf, "Y: %d", y);
        draw_text(&sh1107, buf, (vec2){0, 32}, (vec2f){1.0f, 1.0f}, true);

        bool pressed = !gpio_get(SW_PIN);
        if(pressed)
            draw_text(&sh1107, "Pressed: true", (vec2){0, 0}, (vec2f){1.0f, 1.0f}, true);
        else
            draw_text(&sh1107, "Pressed: false", (vec2){0, 0}, (vec2f){1.0f, 1.0f}, true);


        render(&sh1107);
    }
}
