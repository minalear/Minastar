#version 400
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

out vec3 Color;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
    Color = aColor;
    gl_Position = proj * view * model * vec4(aPos, 0.0, 1.0);
}