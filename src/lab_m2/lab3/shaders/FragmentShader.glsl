#version 430

// Input
layout(location = 0) in vec2 texture_coord;
//in int cube_face;

// Uniform properties
uniform sampler2D texture_1;
//uniform vec3 mirror_color;

// Output
layout(location = 0) out vec4 out_color;


void main()
{

    vec4 color = texture(texture_1, texture_coord);

    out_color = color;
}
