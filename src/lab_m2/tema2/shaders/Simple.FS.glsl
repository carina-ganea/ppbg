#version 430

// Input
layout(location = 0) in vec2 texture_coord;
 
// Uniform properties
layout(binding = 0) uniform sampler2D face;
// Output
layout(location = 0) out vec4 out_color;


void main()
{
    vec3 color = vec3(0, 0, 0);
    color = texture(face, texture_coord).xyz;
    
    out_color = vec4(color, 1);
}
