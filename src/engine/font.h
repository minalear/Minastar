//
// Created by Trevor Fisher on 2/15/2018.
//

#ifndef SINISTAR_FONT_H
#define SINISTAR_FONT_H

#include <cstdint>
#include "texture.h"

namespace minalear {
    struct font_char {
        unsigned char ch;
        uint32_t id;
        uint16_t x, y;
        uint16_t width, height;
        uint16_t x_offset, y_offset;
        uint16_t x_advance;
        uint8_t page;
        uint8_t channel;
    };
    struct block_info {
        uint16_t font_size;
        uint8_t bit_field;
        uint8_t char_set;
        uint16_t stretch_h;
        uint8_t aa;
        uint8_t padding_up;
        uint8_t padding_right;
        uint8_t padding_down;
        uint8_t padding_left;
        uint8_t spacing_horizontal;
        uint8_t spacing_vertical;
        uint8_t outline;
        char font_name[30];
    };
    struct block_common {
        uint16_t line_height;
        uint16_t base;
        uint16_t scale_w;
        uint16_t scale_h;
        uint16_t pages;
        uint8_t  bit_field;
        uint8_t  alpha_channel;
        uint8_t  red_channel;
        uint8_t  green_channel;
        uint8_t  blue_channel;
    };

    class font {
    public:
        texture *bitmap;
        font_char *chars;
        int num_chars;

        block_info info;
        block_common common;

        font(const char* image_filename, const char* data_filename);
        ~font();
        font_char get_char_info(char ch);
    };
}

#endif //SINISTAR_FONT_H
