#version 430

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
//uniform int face;

// Output
layout(location = 0) out vec2 texture_coord;
//out int cube_face;

void main()
{
    texture_coord = v_texture_coord;
    //cube_face = face;
    gl_Position = Projection * View * Model * vec4(v_position, 1);
}
