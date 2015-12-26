#version 150

attribute vec2 a_position;
attribute vec4 a_color;
// attribute vec2 a_texCoord;

uniform mat4 u_model;
uniform mat4 u_projection;

varying vec4 v_color;

void main() {
    v_color = a_color;

    gl_Position = u_projection * u_model * vec4( a_position, 0.0, 1.0 );
}