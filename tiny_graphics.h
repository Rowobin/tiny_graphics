/**
 *  Welcome to "tiny_graphics" - a tiny graphics + physics engine
 *  for the even tinier raspberry pi pico
 * 
 *   What can this libray do?
 *      - Handle I2C connections to multiple displays
 *      - Draw points, lines, shapes, sprites and text
 *      - Use math to do basic transformations (translation, rotation
 *      and scaling) on points, lines, shapes and sprites 
 *      - ..more to come!
 * 
 *  This library is compatible with two OLED screens:
 *      - SSD1306 [datasheet: https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf]
 *      - SH1107 [datasheet: https://cdn-shop.adafruit.com/product-files/5297/SH1107V2.1.pdf]
 *  Contributions to make this library compatible with more modules are welcome :D !  
 *
 **/

/** 
 * Standard C libraries
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Pico SDK libraries
 **/
#include "pico/stdlib.h"
#include "hardware/i2c.h"

/**
 * Commands taken from datasheets
 * Used to configure and control the display
 **/ 
#define CONTROL_CMD_STREAM                      0x00  // control byte for a command stream
#define CONTROL_DATA                            0x40  // control byte for data
#define CONTROL_CMD                             0x80  // control byte for commands

#define SET_MEM_MODE                            0x20  // set display memory adressing mode
#define SET_DISPLAY_START_LINE                  0x40  // set display start line for page memory adressing mode
#define SET_CONTRAST_CONTROL                    0x81  // set display contrast
#define SET_CHARGE_PUMP                         0x8D  // set charge pump settings
#define SET_SEG_REMAP_0                         0xA0  // set display orientation (regular)
#define SET_SEG_REMAP_1                         0xA1  // set display orientation (inverted)
#define DISPLAY_ALL_RAM                         0xA4  // set all pixels to their ram values
#define DISPLAY_ALL_ON                          0xA5  // set all pixels to "on"
#define SET_DISPLAY_NORMAL                      0xA6  // enable normal colors (0 = black, 1 = white)
#define SET_DISPLAY_INVERSE                     0xA7  // enable inverse colors (1 = black, 0 = white)
#define SET_MUX_RATIO                           0xA8  // set multiplex ration
#define TURN_OFF                                0xAE  // turn screen off
#define TURN_ON                                 0xAF  // turns screen on
#define SET_COM_OUTPUT_SCAN_DIRECTION           0xC8  // set display orientation
#define SET_DISPLAY_OFFSET                      0xD3  // set display offset
#define SET_DISPLAY_CLOCK                       0xD5  // set display clock divide ratio/oscillator frequency 
#define SET_COM_PINS                            0xDA  // set coms pins hardware configuration

/**
 * OLED model specific values
 **/
#define SSD1306_PAGE_ADDRESSING_MODE            0x02
#define SSD1306_COM_PINS                        0x12

#define SH1107_PAGE_ADDRESSING_MODE             0x20
#define SH1107_COM_PINS                         0x02

/**
 * Values used for draw_text()
 **/
#define CHARACTER_WIDTH 8
#define CHARACTER_HEIGHT 8
#define CHARACTER_DATA_SIZE 8 // CHARACTER_WIDTH * (CHARACTER_HEIGHT / 8)

typedef enum {
    SSD1306,
    SH1107
} display_type;

/**
 * @brief OLED display data structure
 **/
typedef struct {
    i2c_inst_t* i2c;          ///< i2c bus (i2c0 or i2c1)
    uint baudrate;            ///< baudrate, is usually 400 000
    uint gpio_sda;            ///< gpio for i2c data line
    uint gpio_scl;            ///< gpio for i2c clock line
    uint8_t address;          ///< oled display address
    int width;                ///< display width
    int height;               ///< display height
    uint8_t* buf;             ///< screen buffer (size should be width * height / 8)
    display_type type;        ///< oled display model (sh1107 or ssd1306)
} display;

/**
 * @brief 2D vector with integer coordinates
 **/
typedef struct {
    int x;
    int y;
} vec2;

/**
 * @brief 2D vector with float coordinates
 **/
typedef struct {
    float x;
    float y;
} vec2f;

/**
 * @brief Sprite data structure
 **/
typedef struct {
    uint width;
    uint height;
    const uint8_t* data;
} sprite;

/**
 * @brief Initializes GPIO pins required for an I2C connection with a display
 *
 * @param display the display
 **/
void init_i2c(display* display);

/**
 * @brief Deinitializes GPIO pins required for an I2C connection with a display
 *
 * @param display the display
 **/
void deinit_i2c(display* display);

/**
 * @brief Configure and turn on display
 *
 * @param display the display
 **/
void init_display(display* display);

/**
 * @brief Turn off display
 *
 * @param display the display
 **/
void deinit_display(display* display);

/**
 * @brief Configure and turn on SSD1306 display
 *
 * @param display the display
 **/
void init_display_ssd1306(display* display);

/**
 * @brief Configure and turn on SH1107 display
 *
 * @param display the display
 **/
void init_display_sh1107(display* display);

/**
 * @brief Send a command to a display
 *
 * @param display the display
 * @param cmd command
 **/
void send_cmd(display* display, uint8_t cmd);

/**
 * @brief Send a list of commands to a display
 *
 * @param display the display
 * @param cmd_list pointer to list of commands
 * @param size size of list of commands
 **/
void send_cmd_list(display* display, uint8_t* cmd_list, uint size);

/**
 * @brief Send the contents of display->buf to a display's screen
 *
 * @param display the display
 **/
void render(display* display);

/**
 * @brief Turn on all pixels on a display
 *
 * @param display the display
 **/
void all_on(display* display);

/**
 * @brief Set all pixels on a display to their memory values
 *
 * @param display the display
 **/
void all_ram(display* display);

/**
 * @brief Draw a point on display->buf
 *
 * @param display the display
 * @param point point
 * @param on 0 = black | 1 = white
 * 
 **/
void draw_point(display* display, vec2 point, bool on);

/**
 * @brief Draw a line on display->buf
 *
 * @param display the display
 * @param point0 line beginning
 * @param point1 line ending
 * @param on 0 = black | 1 = white
 * 
 **/
void draw_line(display* display, vec2 point0, vec2 point1, bool on);

/**
 * @brief Draw a shape on display->buf
 *
 * @param display the display
 * @param points pointer to list of points (clockwise order recommended)
 * @param size size of list of points
 * @param on 0 = black | 1 = white
 * 
 **/
void draw_shape(display* display, vec2* points, uint size, bool on);

/**
 * @brief Draw a shape filled with a solid color on display->buf
 *
 * @param display the display
 * @param points pointer to list of points (clockwise order recommended)
 * @param size size of list of points
 * @param on 0 = black | 1 = white
 * 
 **/
void draw_shape_fill(display* display, vec2* points, uint size, bool on);

/**
 * @brief Draw a shape filled with a sprite on display->buf
 *
 * @param display the display
 * @param points pointer to list of points (clockwise order recommended)
 * @param tex pointer to list of texture coordinates for each point
 * @param size size of list of points
 * @param sprite the sprite
 * @param inverted invert sprite colors
 * 
 * @note integer scaling is recommended for sprites
 **/
void draw_shape_fill_sprite(display* display, vec2* points, vec2f* tex, uint size, sprite* sprite, bool inverted);

/**
 * @brief Draw a sprite on display->buf
 *
 * @param display the display
 * @param sprite the sprite
 * @param position sprite position
 * @param inverted invert sprite colors
 * 
 **/
void draw_sprite(display* display, sprite* sprite, vec2 position, bool inverted);

/**
 * @brief Draw a sprite on display->buf
 *
 * @param display the display
 * @param sprite the sprite
 * @param position sprite position
 * @param color 0 = black | 1 = white
 * 
 * @note integer scaling is recommended for text characters
 **/
void draw_text(display* display, char* str, vec2 position, vec2f scale, bool color);

/**
 * @brief Translates a list of points based on a 2D vector
 *
 * @param points pointer to list of points
 * @param size size of list of points
 * @param t translation vector
 **/
void translate_points(vec2* points, uint size, vec2 t);

/**
 * @brief Scales a list of points based on a center point and a 2D vector 
 *
 * @param points pointer to list of points
 * @param size size of list of points
 * @param s scale vector
 * @param center center point
 **/
void scale_points(vec2* points, uint size, vec2f s, vec2 center);

/**
 * @brief Rotates a list of points based on a center point and an angle
 *
 * @param points pointer to list of points
 * @param size size of list of points
 * @param r rotation angle
 * @param center center point
 **/
void rotate_points(vec2* points, uint size, float r, vec2 center);

/**
 * @brief Checks if a point is inside a shape
 *
 * @param point the point
 * @param shape pointer to shape points 
 * @param size number of shape points
 * 
 * @return true = point is inside shape | false = point is outside shape
 **/
bool point_inside_shape(vec2 point, vec2* shape, uint size);

/**
 * @brief Calculates center point from a list of points
 *
 * @param shape pointer to list of points 
 * @param size size of list of points
 * 
 * @return center point
 **/
vec2 calculate_center_point(vec2* points, uint size);

/**
 * @brief Calculates height of a shape
 *
 * @param shape pointer to list of points 
 * @param size size of list of points
 * 
 * @return shape height
 **/
int get_shape_height(vec2* points, uint size);

/**
 * @brief Calculates width of a shape
 *
 * @param shape pointer to list of points 
 * @param size size of list of points
 * 
 * @return shape width
 **/
int get_shape_width(vec2* points, uint size);

/**
 * @brief Calculates the signed area of a triangle
 *
 * @param pf0 first triangle vertice
 * @param pf1 second triangle vertice
 * @param pf2 third triangle vertice
 * 
 * @return signed triangle area
 * 
 **/
float triangle_area_signed(vec2f p0, vec2f p1, vec2f p2);
