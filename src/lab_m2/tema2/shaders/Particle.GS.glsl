#version 430

// Input and output topologies
layout(points) in;
layout(triangle_strip, max_vertices = 170) out;

// Uniform properties
uniform mat4 View[6];
uniform mat4 Projection[6];
uniform vec3 eye_position[6];
uniform vec3 control_p0, control_p1, control_p2, control_p3;
uniform int no_of_instances, no_of_generated_points, no_of_faces;

//Input
in int instance[];
// Output
out float face[2];
vec3 vpos = gl_in[0].gl_Position.xyz;

vec3 rotateY(vec3 point, float u)
{
    float x = point.x * cos(u) - point.z * sin(u);
    float z = point.x * sin(u) + point.z * cos(u);
    return vec3(x, point.y, z);
}

vec3 translateX(vec3 point, float t)
{
    return vec3(point.x + t, point.y, point.z);
}

vec3 bezier(float t)
{
    return  control_p0 * pow((1 - t), 3) +
        control_p1 * 3 * t * pow((1 - t), 2) +
        control_p2 * 3 * pow(t, 2) * (1 - t) +
        control_p3 * pow(t, 3);
}
void EmitPoint(vec3 offset, int i)
{
    vec3 pos = vec3(1,0,0) * offset.x + vec3(0, 1, 0) * offset.y + vec3(0, 0, 1) * offset.z + vpos;
    face[0] = float(i);
    gl_Position = Projection[i] * View[i] * vec4(pos, 1.0);
    EmitVertex();
}

void main()
{
    float ds = 1.05;
    if (no_of_faces == 6) {
        face[1] = 1;
    }
    else {
        face[1] = 0;
    }
    float step = 1. / no_of_generated_points;
    float distance = 6.28 / no_of_instances;
    if( instance[0] < no_of_instances){
        for (int i = 0; i < no_of_faces; i++) {
            for (float t = 0; t <= 1; t += step)
            {
                vec3 offset = rotateY(bezier(t), instance[0] * distance);
                EmitPoint(offset, i);

                offset = rotateY(bezier(t), (instance[0] + 1) * distance);
                EmitPoint(offset, i);
            }
           EndPrimitive();
        }  
    }
}