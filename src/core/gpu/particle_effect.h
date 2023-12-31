#pragma once

#include <vector>
#include <chrono>

#include "utils/gl_utils.h"
#include "utils/glm_utils.h"

#include "components/camera.h"
#include "components/transform.h"

#include "core/gpu/shader.h"
#include "core/gpu/texture2D.h"
#include "core/gpu/ssbo.h"


// TODO(developer): Decouple gfxc components from this class
template <class T>
class ParticleEffect
{
 public:
    ParticleEffect();
    virtual ~ParticleEffect();

    virtual void Generate(unsigned int particleCount, bool createLocalBuffer = false);
    virtual void FillRandomData(std::function<T(void)> generator);
    virtual void Render(gfxc::Camera *camera, Shader *shader, unsigned int nrParticles = -1);
    virtual void RenderInstanced(glm::mat4* ModelMatrix, glm::mat4* ViewMatrix, glm::mat4* ProjectionMatrix, glm::vec3* WorldPosition, Shader* shader, unsigned int nrParticles, unsigned int nrInstances);

    virtual SSBO<T>* GetParticleBuffer() const
    {
        return particles;
    }

    virtual unsigned int GetSize() const
    {
        return particleCount;
    }

 public:
    gfxc::Transform * source;

 protected:
    unsigned int particleCount;
    GLuint VAO;
    GLuint VBO;
    SSBO<T> *particles;
};


template <class T>
ParticleEffect<T>::ParticleEffect()
{
    source = new gfxc::Transform();
    particles = nullptr;
}


template <class T>
ParticleEffect<T>::~ParticleEffect()
{
    SAFE_FREE(source);
    SAFE_FREE(particles);
}


template <class T>
void ParticleEffect<T>::Render(gfxc::Camera *camera, Shader *shader, unsigned int nrParticles)
{
    // Bind MVP
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(source->GetModel()));
    glUniformMatrix4fv(shader->loc_view_matrix, 1, false, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, false, glm::value_ptr(camera->GetProjectionMatrix()));
    glUniform3fv(shader->loc_eye_pos, 1, glm::value_ptr(camera->m_transform->GetWorldPosition()));

    // Bind Particle Storage
    particles->BindBuffer(0);

    // Render Particles
    glBindVertexArray(VAO);
    glDrawElements(GL_POINTS, MIN(particleCount, nrParticles), GL_UNSIGNED_INT, 0);
}

template <class T>
void ParticleEffect<T>::RenderInstanced(glm::mat4* ModelMatrix, glm::mat4* ViewMatrix, glm::mat4* ProjectionMatrix, glm::vec3* WorldPosition, Shader* shader, unsigned int nrParticles, unsigned int nrInstances)
{
    // Bind MVP
    glUniformMatrix4fv(shader->loc_model_matrix, 10, GL_FALSE, glm::value_ptr(ModelMatrix[0]));
    glUniformMatrix4fv(shader->loc_view_matrix, 6, false, glm::value_ptr(ViewMatrix[0]));
    glUniformMatrix4fv(shader->loc_projection_matrix, 6, false, glm::value_ptr(ProjectionMatrix[0]));
    glUniform3fv(shader->loc_eye_pos, 6, glm::value_ptr(WorldPosition[0]));

    // Bind Particle Storage
    particles->BindBuffer(0);

    // Render Particles
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_POINTS, MIN(particleCount, nrParticles), GL_UNSIGNED_INT, (void*)0, nrInstances);
}

template <class T>
void ParticleEffect<T>::Generate(unsigned int particleCount, bool createLocalBuffer)
{
    this->particleCount = particleCount;

    SAFE_FREE(particles);
    particles = new SSBO<T>(particleCount, createLocalBuffer);

    unsigned int *indices = new unsigned int[particleCount];
    unsigned int *p = indices;
    for (unsigned int i = 0; i < particleCount; i++)
    {
        *p = i;
        p++;
    }

    GLuint IBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, particleCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    delete[] indices;
}


template <class T>
void ParticleEffect<T>::FillRandomData(std::function<T(void)> generator)
{
    particles->ReadBuffer();
    auto data = const_cast<T*>(particles->GetBuffer());
    for (unsigned int i = 0; i < particleCount; i++) {
        data[i] = generator();
    }
    particles->SetBufferData(data);
}
