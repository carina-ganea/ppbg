#version 430

// Input
in float face[2];
// Output
layout(location = 0) out vec4 out_color0;
layout(location = 1) out vec4 out_color1;
layout(location = 2) out vec4 out_color2;
layout(location = 3) out vec4 out_color3;
layout(location = 4) out vec4 out_color4;
layout(location = 5) out vec4 out_color5;

void main()
{
    int i = int(face[0]);
    out_color0 = vec4(0, 0, 0, 0);
    out_color1 = vec4(0, 0, 0, 0);
    out_color2 = vec4(0, 0, 0, 0);
    out_color3 = vec4(0, 0, 0, 0);
    out_color4 = vec4(0, 0, 0, 0);
    out_color5 = vec4(0, 0, 0, 0);
    if (i == 0 && face[1] == 0)
        out_color0 = vec4(1, 1, 1, 1);    
    if( i == 1)
        out_color1 = vec4(1, 1, 0, 1);
    if( i == 2)
        out_color2 = vec4(0, 1, 0, 1);
    if( i == 3)
        out_color3 = vec4(1, 0, 1, 1);
    if( i == 4)
        out_color4 = vec4(0, 1, 1, 1);
    if( i == 5)
        out_color5 = vec4(0, 0, 1, 1);
    if (i == 0 && face[1] == 1)
        out_color0 = vec4(1, 0, 0, 1);
}
