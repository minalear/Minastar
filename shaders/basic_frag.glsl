#version 400
in vec3 Color;

out vec4 fragment_color;

void main() {
    fragment_color = vec4(Color, 1.0);
}