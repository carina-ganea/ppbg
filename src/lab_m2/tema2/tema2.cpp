#include "lab_m2/tema2/tema2.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m2;


struct Particle1
{
    int particleIndex;
    glm::vec4 position;
    glm::vec4 speed;
    glm::vec4 resumedSpeed;
    glm::vec4 rotation;
    float rotation_angle;
    glm::vec4 initialPos;
    glm::vec4 initialSpeed;
    glm::vec4 initialRotation;
    float initial_rotation_angle;

    Particle1() {}

    Particle1(const int particleIndex, const glm::vec4& pos, const glm::vec4& speed, const glm::vec4& rotation, const float rotation_angle)
    {
        SetInitial(particleIndex, pos, speed, rotation, rotation_angle);
    }

    void SetInitial(const int index, const glm::vec4& pos, const glm::vec4& speed, const glm::vec4& rotation, const float rotation_angle)
    {
        particleIndex = index;

        position = pos;
        initialPos = pos;

        this->speed = speed;
        initialSpeed = speed;

        this->rotation = rotation;
        initialRotation = rotation;

        this->rotation_angle = rotation_angle;
        initial_rotation_angle = rotation_angle;


    }
};


ParticleEffect<Particle1>* particleEffect;
static glm::mat4* modelMatrix = new glm::mat4[20];
static float currentAngle[20];
unsigned int nrParticles = 20;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPositionAndRotation(glm::vec3(0, 8, 8), glm::quat(glm::vec3(-40 * TO_RADIANS, 0, 0)));
    camera->Update();

    for (int i = 0; i < 10; i++) {
        modelMatrix[i] = glm::mat4(1);
        currentAngle[i] = 0;
    }


    {
        Mesh* mesh = new Mesh("quad");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "quad.obj");
        mesh->UseMaterials(false);
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for rendering to texture
    LoadShader("Simple", false);
    LoadShader("Particle");

    

    particleEffect = new ParticleEffect<Particle1>();
    particleEffect->Generate(nrParticles, true);

    auto particleSSBO = particleEffect->GetParticleBuffer();
    Particle1* data = const_cast<Particle1*>(particleSSBO->GetBuffer());

    int cubeSize = 20;
    int hSize = cubeSize / 2;

    for (unsigned int i = 0; i < nrParticles; i++)
    {
        
        glm::vec4 pos(1);
        pos.x = 0.1;
        pos.y = 0;
        pos.z = 0;

        glm::vec4 speed(0);
        speed.x = (rand() % 20 - 10);
        speed.z = (rand() % 20 - 10);
        speed.y = (rand() % 20 - 10);

        glm::vec4 rotation(0);
        rotation.x = (rand() % 21 - 10) / 10.0f;
        rotation.z = (rand() % 21 - 10) / 10.0f;
        rotation.y = (rand() % 21 - 10) / 10.0f;

        float rotationAngle = pow((-1), rand() %2) * (rand() % 100 + 1.0f) / 200;
        data[i].SetInitial(i, pos, speed, rotation, rotationAngle);
    }

    particleSSBO->SetBufferData(data);

    // Parameters related to surface generation
    no_of_generated_points = 5;            // number of points on a Bezier curve
    no_of_instances = 6;                    // number of instances (number of curves that contain the surface)
    max_translate = 8.0f;                   // for the translation surface, it's the distance between the first and the last curve
    max_rotate = glm::radians(360.0f);

    // Define control points
    control_p0 = glm::vec3(-2.0, -2, 0);
    control_p1 = glm::vec3(-1.25, 0, 0);
    control_p2 = glm::vec3(-0.75, 0.75, 0);
    control_p3 = glm::vec3(-2.0, 2, 0);

    auto resolution = window->GetResolution();


    frame_buffer = new FrameBuffer();
    frame_buffer->Generate(resolution.x, resolution.y, 6, true);
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    glLineWidth(3);

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendEquation(GL_FUNC_ADD);

    static glm::vec3 mirrorPos[6] = { glm::vec3(0, 0, -20), glm::vec3(20, 0, 0), glm::vec3(0, 0, 20), glm::vec3(-20, 0, 0), glm::vec3(0, 20, 0), glm::vec3(0, -20, 0) };
    static glm::vec3 mirrorRotation[6] = { glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0,1,0), glm::vec3(1, 0, 0), glm:: vec3(1, 0, 0)};
    static float mirrorRadians[6] = { RADIANS(180), RADIANS(90), RADIANS(360), RADIANS(270), RADIANS(270), RADIANS(90) };

    // Save camera position and rotation
    auto camera = GetSceneCamera();

    glm::vec3 camPosition = camera->m_transform->GetWorldPosition();
    glm::quat camRotation = camera->m_transform->GetWorldRotation();

    frame_buffer->Bind();

    glm::ivec2 resolution = window->GetResolution();

    glm::mat4 cameraView[6], cameraProj[6];
    glm::vec3 cameraPos[6];

    for (int i = 0; i < 6; i++) {
        camera->SetPosition(mirrorPos[i]);
        camera->SetRotation(mirrorRotation[i] * mirrorRadians[i]);
        //if (i == 4) {
        //    camera->SetRotation(glm::vec3(90, 0, 180));
        //}
        camera->SetOrthographic(40, 40, 0.01, 400);

        cameraView[i] = camera->GetViewMatrix();
        cameraProj[i] = camera->GetProjectionMatrix();
        cameraPos[i] = camera->m_transform->GetWorldPosition();
    }

        {
            auto shader = shaders["Particle"];
            if (shader->GetProgramID())
            {
                shader->Use();
                float dt = 0.01f;
                auto particleSSBO = particleEffect->GetParticleBuffer();
                Particle1* data = const_cast<Particle1*>(particleSSBO->GetBuffer());
                for (int i = 0; i < nrParticles; i++) {
                    glm::mat4 model = glm::mat4(1);
                    
                    float angle_step = data[i].rotation_angle * deltaTimeSeconds * 5;
                    currentAngle[i] += angle_step;
                    if (currentAngle[i] > 6.28) {
                        currentAngle[i] -= 6.28;
                    }

                    glm::vec3 pos = data[i].position;
                    glm::vec3 spd = data[i].speed;
                    glm::vec3 translate_to_center = glm::vec3(-pos.x, -pos.y, -pos.z);
                    pos = pos + spd * dt + spd * dt * dt * 2.0f;
                    spd = spd + spd * dt;
                    
                    data[i].position = glm::vec4(pos,1);
                    data[i].speed = glm::vec4(spd, 1);

                    glm::vec3 rotation = data[i].rotation;
                    //model = glm::translate(model, -translate_to_center);
                    model = glm::rotate(model, currentAngle[i], rotation);
                    //model = glm::translate(model, translate_to_center);
                    modelMatrix[i] = model;
                }
                particleSSBO->SetBufferData(data);
                glUniform3f(glGetUniformLocation(shader->program, "control_p0"), control_p0.x, control_p0.y, control_p0.z);
                glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p1.x, control_p1.y, control_p1.z);
                glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p2.x, control_p2.y, control_p2.z);
                glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p3.x, control_p3.y, control_p3.z);
                glUniform1i(glGetUniformLocation(shader->program, "no_of_instances"), no_of_instances);
                glUniform1i(glGetUniformLocation(shader->program, "no_of_generated_points"), no_of_generated_points);
                glUniform1i(glGetUniformLocation(shader->program, "no_of_faces"), 6);
                //glUniformMatrix4fv(glGetUniformLocation(shader->program, "ModelMatrix"), 10, GL_FALSE, glm::value_ptr(modelMatrix[0]));
                particleEffect->RenderInstanced(modelMatrix, cameraView, cameraProj, cameraPos, shader, 20, 20);
            }
        }
        
    
        frame_buffer->BindDefault();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
    {
        camera->SetPosition(camPosition);
        camera->SetRotation(camRotation);
        camera->SetPerspective(60, window->props.aspectRatio, 0.01f, 200);
        cameraView[0] = camera->GetViewMatrix();
        cameraProj[0] = camera->GetProjectionMatrix();
        cameraPos[0] = camera->m_transform->GetWorldPosition();

        auto shader = shaders["Particle"];
        if (shader->GetProgramID())
        {
            shader->Use();

            //particleSSBO->SetBufferData(data);
            glUniform3f(glGetUniformLocation(shader->program, "control_p0"), control_p0.x, control_p0.y, control_p0.z);
            glUniform3f(glGetUniformLocation(shader->program, "control_p1"), control_p1.x, control_p1.y, control_p1.z);
            glUniform3f(glGetUniformLocation(shader->program, "control_p2"), control_p2.x, control_p2.y, control_p2.z);
            glUniform3f(glGetUniformLocation(shader->program, "control_p3"), control_p3.x, control_p3.y, control_p3.z);
            glUniform1i(glGetUniformLocation(shader->program, "no_of_instances"), no_of_instances);
            glUniform1i(glGetUniformLocation(shader->program, "no_of_generated_points"), no_of_generated_points);
            glUniform1i(glGetUniformLocation(shader->program, "no_of_faces"), 1);
            //glUniformMatrix4fv(glGetUniformLocation(shader->program, "ModelMatrix"), 10, GL_FALSE, glm::value_ptr(modelMatrix[0]));
            particleEffect->RenderInstanced(modelMatrix, cameraView, cameraProj, cameraPos, shader, 20, 20);
        }
    }

    // Render the mirrored scenes
    for(int i = 0; i < 6; i++)
    {
        auto shader = shaders["Simple"];
       
        frame_buffer->BindTexture(i, GL_TEXTURE0);
        glm::mat4 modelMatrix(1);
        modelMatrix = glm::translate(modelMatrix, mirrorPos[i]);
        modelMatrix = glm::rotate(modelMatrix, mirrorRadians[i], mirrorRotation[i]);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(20));
        
        RenderMesh(meshes["quad"], shader, modelMatrix);
    }
}


void Tema2::FrameEnd()
{
#if 0
    DrawCoordinateSystem();
#endif
}


void Tema2::LoadShader(const std::string& name, bool hasGeomtery)
{
    std::string shaderPath = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M2, "tema2", "shaders");

    // Create a shader program for particle system
    {
        Shader* shader = new Shader(name);
        shader->AddShader(PATH_JOIN(shaderPath, name + ".VS.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(shaderPath, name + ".FS.glsl"), GL_FRAGMENT_SHADER);
        if (hasGeomtery)
        {
            shader->AddShader(PATH_JOIN(shaderPath, name + ".GS.glsl"), GL_GEOMETRY_SHADER);
        }

        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}

void DrawScene() {

}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input
    if (window->KeyHold(GLFW_KEY_P)) {
        auto particleSSBO = particleEffect->GetParticleBuffer();
        Particle1* data = const_cast<Particle1*>(particleSSBO->GetBuffer());

        for (int i = 0; i < 10; i++) {
            if(data[i].speed != glm::vec4(0, 0, 0, 1))
                data[i].resumedSpeed = data[i].speed;
            data[i].speed = glm::vec4(0, 0, 0, 1);
            data[i].rotation_angle = 0;
        }
        particleSSBO->SetBufferData(data);
    }
    else {
        auto particleSSBO = particleEffect->GetParticleBuffer();
        Particle1* data = const_cast<Particle1*>(particleSSBO->GetBuffer());
        for (int i = 0; i < 10; i++) {
            if (data[i].rotation_angle == 0) {
                data[i].rotation_angle = data[i].initial_rotation_angle;
                data[i].speed = data[i].resumedSpeed;
            }
        }
        particleSSBO->SetBufferData(data);
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_R) {
        auto particleSSBO = particleEffect->GetParticleBuffer();
        Particle1* data = const_cast<Particle1*>(particleSSBO->GetBuffer());
        // TODO(student): Change the values of the color components.
        for (int i = 0; i < 10; i++) {
            //data[i].initialSpeed = glm::vec4(0, 0, 0, 1);
            data[i].speed = data[i].initialSpeed;
            data[i].position = data[i].initialPos;
            data[i].rotation = data[i].initialRotation;
            currentAngle[i] = 0;
        }
        particleSSBO->SetBufferData(data);
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
   
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Tema2::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
