//
// Created by Trevor Fisher on 2/15/2018.
//

#include <cassert>
#include <cstring>
#include "font.h"
#include "file_handler.h"

using namespace minalear;
using namespace std;

font::font(const char *image_filename, const char *data_filename) {
    //Load texture
    bitmap = new texture(image_filename);

    //Parse data file (binary format) (http://www.angelcode.com/products/bmfont/doc/file_format.html#bin)
    uint32_t file_size;
    uint8_t *binary_data = (uint8_t*)read_binary_file(data_filename, file_size);
    int index_ptr = 3; //First three bytes are BMF

    //File version is fourth byte
    int version = binary_data[index_ptr++];
    assert(version == 3);

    //Each block starts with one byte type identifier, followed by four bytes that gives the size of the block
    //1 - info (header), 2 - common, 3 - pages, 4 - chars, 5 - kerning pairs

    int char_index = 0;
    while (index_ptr < file_size) {
        //1-byte block type
        int block_type = binary_data[index_ptr++];

        //4-byte block size
        uint32_t block_size = uint32_t(
                binary_data[index_ptr + 3] << 24 |
                binary_data[index_ptr + 2] << 16 |
                binary_data[index_ptr + 1] <<  8 |
                binary_data[index_ptr + 0]
        );
        index_ptr += 4;

        if (block_type == 1) { //INFO
            info.font_size          = binary_data[index_ptr +  1] << 8 | binary_data[index_ptr + 0];
            info.bit_field          = binary_data[index_ptr +  2];
            info.char_set           = binary_data[index_ptr +  3];
            info.stretch_h          = binary_data[index_ptr +  5] << 8 | binary_data[index_ptr + 4];
            info.aa                 = binary_data[index_ptr +  6];
            info.padding_up         = binary_data[index_ptr +  7];
            info.padding_right      = binary_data[index_ptr +  8];
            info.padding_down       = binary_data[index_ptr +  9];
            info.padding_left       = binary_data[index_ptr + 10];
            info.spacing_horizontal = binary_data[index_ptr + 11];
            info.spacing_vertical   = binary_data[index_ptr + 12];
            info.outline            = binary_data[index_ptr + 13];

            strcpy(info.font_name, (const char*)(binary_data + index_ptr + 14));
            index_ptr += block_size;
        }
        else if (block_type == 2) { //COMMON
            common.line_height   = binary_data[index_ptr +  1] << 8 | binary_data[index_ptr + 0];
            common.base          = binary_data[index_ptr +  3] << 8 | binary_data[index_ptr + 2];
            common.scale_w       = binary_data[index_ptr +  5] << 8 | binary_data[index_ptr + 4];
            common.scale_h       = binary_data[index_ptr +  7] << 8 | binary_data[index_ptr + 6];
            common.pages         = binary_data[index_ptr +  9] << 8 | binary_data[index_ptr + 8];
            common.bit_field     = binary_data[index_ptr + 10];
            common.alpha_channel = binary_data[index_ptr + 11];
            common.red_channel   = binary_data[index_ptr + 12];
            common.green_channel = binary_data[index_ptr + 13];
            common.blue_channel  = binary_data[index_ptr + 14];
            index_ptr += block_size;
        }
        else if (block_type == 4) {
            //Character numbers determined by taking the block size divided by 20.
            const int NUM_CHARS = (block_size - index_ptr) / 20;
            chars = new font_char[NUM_CHARS];
            num_chars = NUM_CHARS;

            //Loop through each block and load character information
            while (char_index < NUM_CHARS) {
                chars[char_index].id =
                        binary_data[index_ptr + 3] << 24 |
                        binary_data[index_ptr + 2] << 16 |
                        binary_data[index_ptr + 1] << 8 |
                        binary_data[index_ptr + 0];
                chars[char_index].ch        = (unsigned char)chars[char_index].id;
                chars[char_index].x         = binary_data[index_ptr +  5] << 8 | binary_data[index_ptr +  4];
                chars[char_index].y         = binary_data[index_ptr +  7] << 8 | binary_data[index_ptr +  6];
                chars[char_index].width     = binary_data[index_ptr +  9] << 8 | binary_data[index_ptr +  8];
                chars[char_index].height    = binary_data[index_ptr + 11] << 8 | binary_data[index_ptr + 10];
                chars[char_index].x_offset  = binary_data[index_ptr + 13] << 8 | binary_data[index_ptr + 12];
                chars[char_index].y_offset  = binary_data[index_ptr + 15] << 8 | binary_data[index_ptr + 14];
                chars[char_index].x_advance = binary_data[index_ptr + 17] << 8 | binary_data[index_ptr + 16];
                chars[char_index].page      = binary_data[index_ptr + 18];
                chars[char_index].channel   = binary_data[index_ptr + 19];

                index_ptr += block_size / NUM_CHARS;
                char_index++;
            }
        }
        else if (block_type == 3 || block_type == 5) { //Discard
            index_ptr += block_size;
        }
    }

    delete[] binary_data;
}
font::~font() {
    delete bitmap;
    delete[] chars;
}

font_char font::get_char_info(char ch) {
    //Basic profiling seems this is fast enough for basic usage.  Keeping for now.
    for (int i = 0; i < num_chars; i++) {
        if (chars[i].ch == ch)
            return chars[i];
    }

    return get_char_info(' ');
}