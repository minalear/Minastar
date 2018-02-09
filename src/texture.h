//
// Created by Trevor Fisher on 1/19/2018.
//

#ifndef MINALEAR_TEXTURE_H
#define MINALEAR_TEXTURE_H

namespace minalear {
    class texture {
    private:
        int width, height, nBits;
        unsigned int textureID;

    public:
        texture(const char *);
        int getWidth();
        int getHeight();
        void bind();
    };
}

#endif //MINALEAR_TEXTURE_H
