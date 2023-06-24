#version 430

//Input
layout(location = 0) in vec2 tex_coords;

// Uniform properties
uniform vec3 colour;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    out_color = vec4(colour, 0);
}
