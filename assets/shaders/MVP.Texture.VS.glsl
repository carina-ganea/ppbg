#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 carPos;

// Output
out vec3 frag_normal;
out vec3 frag_color;
out vec2 tex_coord;


void main()
{
    frag_normal = v_normal;
    frag_color = v_color;
    tex_coord = v_texture_coord;
    vec3 position =  (Model * vec4(v_position, 1.0)).xyz;
    position = vec3(position.x, position.y - (pow(length(carPos - position), 2) * 0.01), position.z); 

    gl_Position = Projection * View * vec4(position, 1.0);
    
}
