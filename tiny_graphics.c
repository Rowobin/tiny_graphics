#include "tiny_graphics.h"

/**
 * Characters used for draw_text()
 **/
const uint8_t characters[] = {
    /*   */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* ! */ 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x00,
    /* " */ 0x00, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0x00,
    /* # */ 0x00, 0x24, 0x7E, 0x24, 0x24, 0x7E, 0x24, 0x00,
    /* $ */ 0x00, 0x12, 0x2A, 0x6B, 0x2A, 0x24, 0x00, 0x00,
    /* % */ 0x00, 0x62, 0x64, 0x08, 0x10, 0x26, 0x46, 0x00,
    /* & */ 0x00, 0x2C, 0x52, 0x4A, 0x24, 0x0A, 0x00, 0x00,
    /* ' */ 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
    /* ( */ 0x00, 0x00, 0x00, 0x3C, 0x42, 0x00, 0x00, 0x00,
    /* ) */ 0x00, 0x00, 0x00, 0x42, 0x3C, 0x00, 0x00, 0x00,
    /* * */ 0x00, 0x48, 0x30, 0x78, 0x30, 0x48, 0x00, 0x00,
    /* + */ 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00,
    /* , */ 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* - */ 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00,
    /* . */ 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* / */ 0x00, 0x00, 0x02, 0x0C, 0x30, 0x40, 0x00, 0x00,
    /* 0 */ 0x00, 0x3C, 0x46, 0x4A, 0x52, 0x3C, 0x00, 0x00,
    /* 1 */ 0x00, 0x00, 0x22, 0x7E, 0x02, 0x00, 0x00, 0x00,
    /* 2 */ 0x00, 0x22, 0x46, 0x4A, 0x4A, 0x32, 0x00, 0x00,
    /* 3 */ 0x00, 0x24, 0x42, 0x52, 0x52, 0x2C, 0x00, 0x00,
    /* 4 */ 0x00, 0x08, 0x18, 0x28, 0x48, 0x7E, 0x00, 0x00,
    /* 5 */ 0x00, 0x64, 0x52, 0x52, 0x52, 0x4C, 0x00, 0x00,
    /* 6 */ 0x00, 0x3C, 0x52, 0x52, 0x52, 0x4C, 0x00, 0x00,
    /* 7 */ 0x00, 0x40, 0x40, 0x4E, 0x50, 0x60, 0x00, 0x00,
    /* 8 */ 0x00, 0x2C, 0x52, 0x52, 0x52, 0x2C, 0x00, 0x00,
    /* 9 */ 0x00, 0x32, 0x4A, 0x4A, 0x4A, 0x3C, 0x00, 0x00,
    /* : */ 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* ; */ 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* < */ 0x00, 0x00, 0x08, 0x14, 0x22, 0x00, 0x00, 0x00,
    /* = */ 0x00, 0x00, 0x14, 0x14, 0x14, 0x14, 0x00, 0x00,
    /* > */ 0x00, 0x00, 0x22, 0x14, 0x08, 0x00, 0x00, 0x00,
    /* ? */ 0x00, 0x20, 0x40, 0x5A, 0x50, 0x20, 0x00, 0x00,
    /* @ */ 0x00, 0x3C, 0x42, 0x5A, 0x5A, 0x4C, 0x20, 0x00,
    /* A */ 0x00, 0x06, 0x18, 0x68, 0x68, 0x18, 0x06, 0x00,
    /* B */ 0x00, 0x7E, 0x52, 0x52, 0x52, 0x2C, 0x00, 0x00,
    /* C */ 0x00, 0x18, 0x24, 0x42, 0x42, 0x42, 0x24, 0x00,
    /* D */ 0x00, 0x7E, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
    /* E */ 0x00, 0x7E, 0x52, 0x52, 0x52, 0x42, 0x00, 0x00,
    /* F */ 0x00, 0x7E, 0x50, 0x50, 0x50, 0x40, 0x00, 0x00,
    /* G */ 0x00, 0x18, 0x24, 0x42, 0x4A, 0x4A, 0x2C, 0x00,
    /* H */ 0x00, 0x7E, 0x10, 0x10, 0x10, 0x10, 0x7E, 0x00,
    /* I */ 0x00, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00, 0x00,
    /* J */ 0x00, 0x04, 0x42, 0x42, 0x42, 0x7C, 0x40, 0x00,
    /* K */ 0x00, 0x7E, 0x08, 0x18, 0x24, 0x42, 0x00, 0x00,
    /* L */ 0x00, 0x7E, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00,
    /* M */ 0x00, 0x7E, 0x20, 0x10, 0x10, 0x20, 0x7E, 0x00,
    /* N */ 0x00, 0x7E, 0x20, 0x10, 0x08, 0x04, 0x7E, 0x00,
    /* O */ 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00,
    /* P */ 0x00, 0x7E, 0x50, 0x50, 0x50, 0x20, 0x00, 0x00,
    /* Q */ 0x00, 0x3C, 0x42, 0x42, 0x4A, 0x44, 0x3A, 0x00,
    /* R */ 0x00, 0x7E, 0x50, 0x58, 0x54, 0x22, 0x00, 0x00,
    /* S */ 0x00, 0x24, 0x52, 0x4A, 0x4A, 0x4A, 0x24, 0x00,
    /* T */ 0x00, 0x40, 0x40, 0x7E, 0x40, 0x40, 0x00, 0x00,
    /* U */ 0x00, 0x7C, 0x02, 0x02, 0x02, 0x02, 0x7C, 0x00,
    /* V */ 0x00, 0x60, 0x18, 0x06, 0x06, 0x18, 0x60, 0x00,
    /* W */ 0x00, 0x7E, 0x04, 0x08, 0x08, 0x04, 0x7E, 0x00,
    /* X */ 0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00,
    /* Y */ 0x00, 0x40, 0x30, 0x0E, 0x30, 0x40, 0x00, 0x00,
    /* Z */ 0x00, 0x42, 0x46, 0x4A, 0x52, 0x62, 0x42, 0x00,
    /* [ */ 0x00, 0x00, 0x00, 0x7E, 0x42, 0x00, 0x00, 0x00,
    /* \ */ 0x00, 0x00, 0x40, 0x30, 0x0C, 0x02, 0x00, 0x00,
    /* ] */ 0x00, 0x00, 0x00, 0x42, 0x7E, 0x00, 0x00, 0x00,
    /* ^ */ 0x00, 0x10, 0x20, 0x40, 0x20, 0x10, 0x00, 0x00,
    /* _ */ 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00,
    /* ` */ 0x00, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* a */ 0x00, 0x04, 0x2A, 0x2A, 0x2A, 0x2C, 0x1E, 0x00,
    /* b */ 0x00, 0x3E, 0x14, 0x12, 0x12, 0x12, 0x0C, 0x00,
    /* c */ 0x00, 0x00, 0x1C, 0x22, 0x22, 0x22, 0x00, 0x00,
    /* d */ 0x00, 0x0C, 0x12, 0x12, 0x12, 0x14, 0x3E, 0x00,
    /* e */ 0x00, 0x1C, 0x2A, 0x2A, 0x2A, 0x18, 0x00, 0x00,
    /* f */ 0x00, 0x00, 0x08, 0x3E, 0x28, 0x20, 0x00, 0x00,
    /* g */ 0x00, 0x18, 0x28, 0x2A, 0x2A, 0x12, 0x3C, 0x00,
    /* h */ 0x00, 0x3E, 0x08, 0x08, 0x08, 0x06, 0x00, 0x00,
    /* i */ 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00,
    /* j */ 0x00, 0x02, 0x02, 0x0A, 0x2C, 0x00, 0x00, 0x00,
    /* k */ 0x00, 0x3E, 0x04, 0x0A, 0x12, 0x00, 0x00, 0x00,
    /* l */ 0x00, 0x00, 0x00, 0x3E, 0x02, 0x00, 0x00, 0x00,
    /* m */ 0x00, 0x3E, 0x20, 0x10, 0x10, 0x20, 0x3E, 0x00,
    /* n */ 0x00, 0x3E, 0x10, 0x20, 0x20, 0x20, 0x3E, 0x00,
    /* o */ 0x00, 0x1C, 0x22, 0x22, 0x22, 0x1C, 0x00, 0x00,
    /* p */ 0x00, 0x3E, 0x14, 0x24, 0x24, 0x24, 0x18, 0x00,
    /* q */ 0x00, 0x18, 0x24, 0x24, 0x24, 0x14, 0x3E, 0x00,
    /* r */ 0x00, 0x3E, 0x10, 0x20, 0x20, 0x10, 0x00, 0x00,
    /* s */ 0x00, 0x12, 0x2A, 0x2A, 0x2A, 0x24, 0x00, 0x00,
    /* t */ 0x00, 0x00, 0x10, 0x3E, 0x12, 0x00, 0x00, 0x00,
    /* u */ 0x00, 0x3C, 0x02, 0x02, 0x04, 0x3E, 0x00, 0x00,
    /* v */ 0x00, 0x30, 0x0C, 0x02, 0x02, 0x0C, 0x30, 0x00,
    /* w */ 0x00, 0x3E, 0x02, 0x04, 0x04, 0x02, 0x3E, 0x00,
    /* x */ 0x00, 0x12, 0x0A, 0x04, 0x04, 0x0A, 0x12, 0x00,
    /* y */ 0x00, 0x12, 0x0A, 0x04, 0x08, 0x10, 0x00, 0x00,
    /* z */ 0x00, 0x22, 0x26, 0x2A, 0x32, 0x22, 0x00, 0x00,
    /* { */ 0x00, 0x00, 0x08, 0x34, 0x42, 0x00, 0x00, 0x00,
    /* | */ 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00,
    /* } */ 0x00, 0x00, 0x00, 0x42, 0x34, 0x08, 0x00, 0x00,
    /* ~ */ 0x00, 0x00, 0x08, 0x08, 0x10, 0x10, 0x00, 0x00,
};

void init_i2c(display* display){
    i2c_init(display->i2c, 400000);
    gpio_set_function(display->gpio_sda, GPIO_FUNC_I2C);
    gpio_set_function(display->gpio_scl, GPIO_FUNC_I2C);
    gpio_pull_up(display->gpio_sda);
    gpio_pull_up(display->gpio_scl);
}

void deinit_i2c(display* display){
    gpio_pull_down(display->gpio_scl);
    gpio_pull_down(display->gpio_sda);
    gpio_set_function(display->gpio_scl, GPIO_FUNC_NULL);
    gpio_set_function(display->gpio_sda, GPIO_FUNC_NULL);
    i2c_deinit(display->i2c);
}

void init_display(display* display){
    switch(display->type){
        case SSD1306:
            init_display_ssd1306(display);
            break;
        case SH1107:
            init_display_sh1107(display);
            break;
        default:
            break;
    }
}

void deinit_display(display* display){
    send_cmd(display, TURN_OFF);
}

void init_display_ssd1306(display* display){
    uint8_t cmds[] = {
        TURN_OFF,
        SET_MEM_MODE,
        SSD1306_PAGE_ADDRESSING_MODE,
        SET_MUX_RATIO,
        display->height-1,
        SET_DISPLAY_OFFSET,
        0x00,
        SET_DISPLAY_START_LINE,
        SET_SEG_REMAP_1,
        SET_COM_OUTPUT_SCAN_DIRECTION,
        SET_COM_PINS,
        SSD1306_COM_PINS,
        SET_CONTRAST_CONTROL,
        0x7F,
        DISPLAY_ALL_ON,
        SET_DISPLAY_NORMAL,
        SET_DISPLAY_CLOCK,
        0x80,
        SET_CHARGE_PUMP,
        0x14,
        TURN_ON,
    };
    send_cmd_list(display, cmds, sizeof(cmds) / sizeof(uint8_t));
}

void init_display_sh1107(display* display){
    uint8_t cmds[] = {
        TURN_OFF,
        SET_MEM_MODE,
        SH1107_PAGE_ADDRESSING_MODE,
        SET_MUX_RATIO,
        display->height-1,
        SET_DISPLAY_OFFSET,
        0x00,
        SET_DISPLAY_START_LINE,
        SET_COM_PINS,
        SH1107_COM_PINS,
        SET_CONTRAST_CONTROL,
        0x7F,
        DISPLAY_ALL_ON,
        SET_DISPLAY_NORMAL,
        SET_DISPLAY_CLOCK,
        0x80,
        SET_CHARGE_PUMP,
        0x14,
        TURN_ON,
    };
    send_cmd_list(display, cmds, sizeof(cmds) / sizeof(uint8_t));    
}

void send_cmd(display* display, uint8_t cmd){
    uint8_t buf[2] = {CONTROL_CMD, cmd};
    i2c_write_blocking(display->i2c, display->address, buf, 2, false);
}

void send_cmd_list(display* display, uint8_t* cmd_list, uint size){
    uint8_t buf[size+1];
    buf[0] = CONTROL_CMD_STREAM;
    memcpy(&buf[1], cmd_list, size);
    i2c_write_blocking(display->i2c, display->address, buf, size + 1, false);
}

void render(display* display){
    for(int page = 0; page < display->height >> 3; page++){
        send_cmd(display, 0xB0 | page); // set page
        send_cmd(display, 0x00); // set min column
        send_cmd(display, 0x10); // set max column

        uint8_t buf[display->width+1];
        buf[0] = CONTROL_DATA;
        memcpy(&buf[1], &display->buf[page * display->width], display->width);
        i2c_write_blocking(display->i2c, display->address, buf, display->width+1, false);
    }
}

void all_on(display* display){
    send_cmd(display, DISPLAY_ALL_ON);
}

void all_ram(display* display){
    send_cmd(display, DISPLAY_ALL_RAM);
}

void draw_point(display* display, vec2 point, bool on){
    int x = point.x;
    int y = point.y;
    if(y >= display->height || y < 0 || x >= display->width || x < 0) return;
    if(on){
        display->buf[display->width * (y >> 3) + x] |= (0b00000001 << (y & 7));
    }else{
        display->buf[display->width * (y >> 3) + x] &= (0b11111111 - (0b00000001 << (y & 7)));
    }
}

void draw_line(display* display, vec2 point0, vec2 point1, bool on){
    int dx = abs(point1.x - point0.x);
    int dy = abs(point1.y - point0.y);

    int sx = (point0.x < point1.x) ? 1 : -1;
    int sy = (point0.y < point1.y) ? 1 : -1;

    int err = dx - dy;
    int x = point0.x;
    int y = point0.y;

    do{
        draw_point(display, (vec2){x, y}, on);
        int e2 = 2 * err;
        if(e2 > -dy){
            err -= dy;
            x += sx;       
        }
        if(e2 < dx){
            err += dx;
            y += sy;
        }
    } while (x != point1.x || y != point1.y);
}

void draw_shape(display* display, vec2* points, uint size, bool on){
    for(int i = 0; i < size; i++){
        draw_line(display, points[i], points[(i+1)%size], on);
    }
}

void draw_shape_fill(display* display, vec2* points, uint size, bool on){
    draw_shape(display, points, 4, on);

    int xmin = points[0].x;
    int xmax = points[0].x;
    int ymin = points[0].y;
    int ymax = points[0].y;

    for(uint i = 1; i < size; i++){
        xmin = MIN(xmin, points[i].x);
        xmax = MAX(xmax, points[i].x);
        ymin = MIN(ymin, points[i].y);
        ymax = MAX(ymax, points[i].y);
    }

    for(int y = ymin; y < ymax; y++){
        for(int x = xmin; x < xmax; x++){
            vec2 point = {x, y};
            if(point_inside_shape(point, points, size)){
                draw_point(display, (vec2){x, y}, on);
            }
        }
    }
}

void draw_shape_fill_sprite(display* display, vec2* points, vec2f* tex, uint size, sprite* sprite, bool inverted) {
    int xmin = points[0].x;
    int xmax = points[0].x;
    int ymin = points[0].y;
    int ymax = points[0].y;

    for(uint i = 1; i < size; i++){
        xmin = MIN(xmin, points[i].x);
        xmax = MAX(xmax, points[i].x);
        ymin = MIN(ymin, points[i].y);
        ymax = MAX(ymax, points[i].y);
    }

    for(int y = ymin; y < ymax; y++){
        for(int x = xmin; x < xmax; x++){
            vec2f point = {x + 0.5f, y + 0.5f};
            vec2f a = {points[0].x, points[0].y};
            for(int i = 1; i + 1 < size; i++){
                vec2f b = {points[i].x, points[i].y};
                vec2f c = {points[i+1].x, points[i+1].y};;

                float abc = triangle_area_signed(a, b, c);
                float pbc = triangle_area_signed(point, b, c);
                float pca = triangle_area_signed(point, c, a);

                float wa = pbc / abc;
                float wb = pca / abc;
                float wc = 1.0 - (wa + wb);

                if(wa < 0.0 || wb < 0.0 || wc < 0.0) continue;

                float u = tex[0].x * wa + tex[i].x * wb + tex[i+1].x * wc;
                float v = tex[0].y * wa + tex[i].y * wb + tex[i+1].y * wc;
                
                int tx = (int) (u * sprite->width) % sprite->width;
                int ty = (int) (v * sprite->height) % sprite->height;

                int8_t byte = sprite->data[ty/8 * sprite->width + tx];
                draw_point(display, (vec2){x, y}, ((byte >> (7 - (ty & 7))) & 1) ^ inverted);
                break;
            }
        }
    }
}

void draw_sprite(display* display, sprite* sprite, vec2 position, bool inverted){
    int width = sprite->width;
    int height = sprite->height;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            uint8_t byte = sprite->data[y/8 * width + x];
            draw_point(display, (vec2){x + position.x, y + position.y}, ((byte >> (7 - (y & 7))) & 1) ^ inverted);
        }
    }
}

void draw_text(display* display, char* str, vec2 position, vec2f scale, bool color){
    vec2 square[] = {
        {0,0},
        {8,0},
        {8,8},
        {0,8}
    };
    vec2f tex[] = {
        {0.0,0.0},
        {1.0,0.0},
        {1.0,1.0},
        {0.0,1.0}
    };
    int size = 4;
    vec2 space = {8,8};

    translate_points(square, size, position);
    scale_points(square, size, scale, position);
    space.x *= scale.x;
    space.y *= scale.y;

    sprite character;
    character.height = CHARACTER_HEIGHT;
    character.width = CHARACTER_WIDTH;

    int i = 0;
    while(str[i] != '\0'){
        int c_i = (int) str[i];
        if(c_i == 10){
            int dif_x = position.x - square[0].x;
            translate_points(square, 4, (vec2){dif_x, space.y});
        } else {
            character.data = &characters[(c_i-32)*CHARACTER_DATA_SIZE];
            draw_shape_fill_sprite(display, square, tex, size, &character, !color);
            translate_points(square, 4, (vec2){space.x, 0});
        }
        i += 1;
    }
}

void translate_points(vec2* points, uint size, vec2 t){
    for(uint i = 0; i < size; i++){
        points[i].x += t.x;
        points[i].y += t.y;
    }
}

void scale_points(vec2* points, uint size, vec2f s, vec2 center){
    for(uint i = 0; i < size; i++){
        float dx = points[i].x - center.x;
        float dy = points[i].y - center.y;

        float sx = dx * s.x;
        float sy = dy * s.y;

        points[i].x = (int)round(center.x + sx);
        points[i].y = (int)round(center.y + sy);
    }
}

void rotate_points(vec2* points, uint size, float r, vec2 center)
{
    float c = cosf(r);
    float s = sinf(r);
    for (uint i = 0; i < size; i++)
    {
        float dx = points[i].x - center.x;
        float dy = points[i].y - center.y;

        float rx = c * dx - s * dy;
        float ry = s * dx + c * dy;

        points[i].x = (int)round(center.x + rx);
        points[i].y = (int)round(center.y + ry);
    }
}

bool point_inside_shape(vec2 point, vec2* shape, uint size){
    vec2f pointf = {point.x, point.y};
    vec2f a = {shape[0].x, shape[0].y};
    for(int i = 1; i + 1 < size; i++){
        vec2f b = {shape[i].x, shape[i].y};
        vec2f c = {shape[i+1].x, shape[i+1].y};

        float abc = triangle_area_signed(a, b, c);
        float pbc = triangle_area_signed(pointf, b, c);
        float pca = triangle_area_signed(pointf, c, a);

        float wa = pbc / abc;
        float wb = pca / abc;
        float wc = 1.0 - (wa + wb);

        if(wa < 0.0 || wb < 0.0 || wc < 0.0) continue;

        return true;
    }
    return false;
}

vec2 calculate_center_point(vec2* points, uint size){
    int sum_x = 0;
    int sum_y = 0;
    for(uint i = 0; i < size; i++){
        sum_x += points[i].x;
        sum_y += points[i].y;
    }
    return (vec2){sum_x / size, sum_y / size};
}

int get_shape_height(vec2* points, uint size){
    int ymin = points[0].y;
    int ymax = points[0].y;
    for(int i = 1; i < size; i++){
        ymin = MIN(points[i].y, ymin);
        ymax = MAX(points[i].y, ymax);
    }
    return ymax-ymin;
}

int get_shape_width(vec2* points, uint size){
    int xmin = points[0].x;
    int xmax = points[0].x;
    for(int i = 1; i < size; i++){
        xmin = MIN(points[i].x, xmin);
        xmax = MAX(points[i].x, xmax);
    }
    return xmax - xmin;
}

float triangle_area_signed(vec2f p0, vec2f p1, vec2f p2){
    return 0.5 * ((p1.y-p0.y)*(p1.x+p0.x)+(p2.y-p1.y)*(p2.x+p1.x)+(p0.y-p2.y)*(p0.x+p2.x));
}