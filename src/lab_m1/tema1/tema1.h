#pragma once

#include "components/simple_scene.h"
#include "components/camera.h"
#include <string>
using namespace std;

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };
    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        glm::vec3 bezier(float t, glm::vec3 control_p0, glm::vec3 control_p1, glm::vec3 control_p2, glm::vec3 control_p3);
        Mesh* CreateTerrain(const std::string& name, glm::vec3 leftBottomCorner, float length);
        Mesh* CreateTree(const std::string& name, glm::vec3 origin, float length);
        Mesh* CreateRoad(const std::string& name, vector<glm::vec3> roadPoints);
        bool CheckOnRoad(glm::vec3 pos);
        bool CheckTreeOnRoad(glm::vec3 pos);
        inline double TriangleArea(glm::vec3 A, glm::vec3 B, glm::vec3 C);

        // TODO(student): Class variables go here
        float red;
        float green;
        float blue;

        inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
        {
            return glm::transpose(
                glm::mat4(  1, 0, 0, translateX,
                            0, 1, 0, translateY,
                            0, 0, 1, translateZ,
                            0, 0, 0,          1));

        }
        // Scale matrix
        inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
        {
            return glm::transpose(
                glm::mat4(  scaleX, 0, 0, 0,
                            0, scaleY, 0, 0,
                            0, 0, scaleZ, 0,
                            0, 0,      0, 1));

        }
        inline glm::mat4 RotateOX(float radians)
        {
            return glm::transpose(
                glm::mat4(  1,            0,             0, 0,
                            0, cos(radians), -sin(radians), 0,
                            0, sin(radians),  cos(radians), 0,
                            0,            0,             0, 1));

        }
        inline glm::mat4 RotateOY(float radians)
        {
            return glm::transpose(
                glm::mat4(  cos(radians), 0, sin(radians), 0,
                                       0, 1,            0, 0,
                           -sin(radians), 0, cos(radians), 0,
                                       0, 0,            0, 1));

        }
        inline glm::mat4 RotateOZ(float radians)
        {
            return glm::transpose(
                glm::mat4(  cos(radians), -sin(radians), 0, 0,
                            sin(radians),  cos(radians), 0, 0,
                                       0,             0, 1, 0,
                                       0,             0, 0, 1));

        }
        
        int Counter;
        float X, Y, Z;
        float rotateX, rotateY;
        std::string cycle[3];
        glm::vec3 UP = glm::vec3(0, 1, 0);
        float distRosu, distAlbastru;
        glm::vec3 black, grass;
        float movementSpeed;
        glm::mat4 modelMatrix;
        vector<glm::vec3> roadVert;
        vector<unsigned int> indices;
        int nb_trees;
        vector<glm::vec3> treePos;
        ViewportArea miniViewportArea;
        float left, right, bottom, top, zNear, zFar;

    };
}   // namespace m1
