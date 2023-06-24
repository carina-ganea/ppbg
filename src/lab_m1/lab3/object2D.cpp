#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length / 2, length * 1.73f / 2, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 color,
    int precision,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices_filled;
    std::vector<unsigned int> indices_unfilled;

    vertices.push_back(VertexFormat(center, color));
    for(int i = 0; i <= precision; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(precision);
        vertices.push_back(VertexFormat(center + glm::vec3(length / 2 * cosf(theta), length / 2* sinf(theta), 0), color));
        indices_filled.push_back(i);
        indices_filled.push_back(0);
        indices_filled.push_back(i + 1);
        
        indices_unfilled.push_back(i+1);
    };

    Mesh* circle = new Mesh(name);
    

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
        circle->InitFromData(vertices, indices_unfilled);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices_filled.pop_back();
        indices_filled.push_back(1);
        circle->InitFromData(vertices, indices_filled);
    }
    
    return circle;
}
