#version 330

// Input
in vec3 frag_color;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    out_color = vec4(frag_color, 1);
    if(out_color.xyz == vec3(0,0,0)){
        out_color = vec4(0,1,1,1);
    }
}
