#version 400
in vec2 UV;
out vec4 fragment_color;

uniform sampler2D font_bitmap;

void main() {
    vec4 sampled_color = vec4(1.f, 1.f, 1.f, texture(font_bitmap, UV).r);
    fragment_color = vec4(1.f) * sampled_color;
}
