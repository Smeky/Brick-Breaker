#version 330

layout (location = 0) in vec2 a_position;
// layout (location = 1) in vec4 a_color;
// layout (location = 2) in vec2 a_texCoords;

uniform mat4 u_model;
uniform mat4 u_projection;

void main() {
    gl_Position = vec4( a_position, 0.0, 1.0 );
    // gl_Position = u_projection * u_model * vec4( a_position, 0.0, 1.0 );
}