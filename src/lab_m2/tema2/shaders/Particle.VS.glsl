#version 430
// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model[10];
//uniform mat4 ModelMatrix[10];
out int instance;

struct Particle1
{
    int particleIndex;
    vec4 position;
    vec4 speed;
    vec4 rotation;
    float rotationAngle;
    vec4 iposition;
    vec4 ispeed;
    vec4 irotation;
    float irotationAngle;
    
};


layout(std430, binding = 0) buffer particles {
    Particle1 data[];
};

float rand(vec2 co)
{
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}


void main()
{
    int particleIndex = data[gl_VertexID].particleIndex;
    vec3 pos = data[gl_VertexID].position.xyz;
    vec3 spd = data[gl_VertexID].speed.xyz;
    instance = gl_InstanceID;
    //vec3 rotation = data[gl_VertexID].rotation.xyz;

        
    float dt = 0.05;

    pos = pos + spd * dt + spd * dt * dt * 2.0;
    spd = spd + spd * dt;

    //if(pos.y < -200 || pos.y > 200)
    //{
    //    pos = data[gl_VertexID].iposition.xyz;
    //    spd = data[gl_VertexID].ispeed.xyz;
    //}


    data[gl_VertexID].position.xyz =  pos;
    data[gl_VertexID].speed.xyz =  spd;
    data[gl_VertexID].rotationAngle = data[gl_VertexID].irotationAngle;

    
    gl_Position = Model[particleIndex] * vec4(pos, 1);

    
}