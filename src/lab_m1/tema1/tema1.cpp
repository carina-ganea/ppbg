#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include <string>

const double NILL = 0.000000000001;

using namespace std;
using namespace m1;

Tema1::Tema1()
{
    Counter = 0;
    X = 98;
    Y = 0.5;
    Z = -10;
    black = glm::vec3(0.2, 0.2, 0.2);
    grass = glm::vec3(0.4, 0.8, 0.3);
    distRosu = 2.0f;
    distAlbastru = 2.2f;
    movementSpeed = 20.f;
    rotateX = 3.14;
    rotateY = 0;
    red = 0.5;
    green = 0.6;
    blue = 0.9;
    nb_trees = 800;
    left = -25;
    right = 25;
    bottom = -25;
    top = 25;
    zNear = 0.01;
    zFar = 400;
    treePos = {
    /*glm::vec3(24.0258, 0, 43.84083),
    glm::vec3(31.40061, 0, 29.33704),
    glm::vec3(13.20941, 0, 28.84538),
    glm::vec3(37.54628, 0, 6.2293),
    glm::vec3(42.46282, 0, 5.24599),
    glm::vec3(-25.63125, 0, 68.91518),
    glm::vec3(-40.13504, 0, -25.97404),
    glm::vec3(56.22914, 0, -20.56584),
    glm::vec3(-14.32321, 0, 22.45388),
    glm::vec3(-8.42336, 0, 34.25358),
    glm::vec3(27.95903, 0, -4.09544),
    glm::vec3(35.8255, 0, 69.89849),
    glm::vec3(72.45372, 0, 19.74978),
    glm::vec3(71.47041, 0, 40.64508),
    glm::vec3(-11.37329, 0, -3.60378),
    glm::vec3(-9.40667, 0, -44.41106),
    glm::vec3(4.60547, 0, 72.35676),
    glm::vec3(10.75114, 0, -8.52032),
    glm::vec3(29.92565, 0, -40.96948),
    glm::vec3(-26.86039, 0, 12.86663),
    glm::vec3(-65.45523, 0, 10.90001),
    glm::vec3(-60, 0, -20),
    glm::vec3(88.18665, 0, -14.666),
    glm::vec3(88.6783, 0, 49.74068),
    glm::vec3(66.55387, 0, 71.12762),
    glm::vec3(-63.73444, 0, 61.04872),
    glm::vec3(-60, 0, 40),
    glm::vec3(6.08043, 0, 12.6208),
    glm::vec3(-52.42639, 0, -40.72366)*/
    };


}

Tema1::~Tema1()
{
}

Mesh* Tema1::CreateTerrain(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices = {};
    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = {}; 
    float step = length / 300;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            vertices.push_back(VertexFormat(corner + glm::vec3(i * step, 0, j * step), grass));
            vertices.push_back(VertexFormat(corner + glm::vec3((i + 1) * step, 0, j*step), grass));
            vertices.push_back(VertexFormat(corner + glm::vec3(i * step, 0, (j + 1) *step), grass));
            indices.push_back(i * 300 + j * 3);
            indices.push_back(i * 300 + j * 3 + 1);
            indices.push_back(i * 300 + j * 3 + 2);
            indices.push_back(i * 300 + j * 3 + 1);
            indices.push_back(i * 300 + j * 3 + 4);
            indices.push_back(i * 300 + j * 3 + 2);
        }
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* Tema1::CreateTree(
    const std::string& name,
    glm::vec3 origin,
    float length)
{
    glm::vec3 treeBark = glm::vec3(0.44, 0.36, 0.26);
    glm::vec3 treeLeaves = glm::vec3(0.12, 0.55, 0.13);

    vector<VertexFormat> vertices
    {
        VertexFormat(origin + glm::vec3(-length / 2, -length,  length/2), treeBark),
        VertexFormat(origin + glm::vec3(length / 2, -length,  length / 2),  treeBark),
        VertexFormat(origin + glm::vec3(-length / 2, length,  length / 2), treeBark),
        VertexFormat(origin + glm::vec3(length / 2, length,  length / 2),  treeBark),
        VertexFormat(origin + glm::vec3(-length / 2, -length,  -length / 2), treeBark),
        VertexFormat(origin + glm::vec3(length / 2, -length,  -length / 2), treeBark),
        VertexFormat(origin + glm::vec3(-length / 2, length,  -length / 2),  treeBark),
        VertexFormat(origin + glm::vec3(length / 2, length,  -length / 2), treeBark),

        VertexFormat(origin + glm::vec3(-length*2, length,  length*2), treeLeaves),
        VertexFormat(origin + glm::vec3(length*2, length,  length*2),  treeLeaves),
        VertexFormat(origin + glm::vec3(-length*2, 4*length,  length*2), treeLeaves),
        VertexFormat(origin + glm::vec3(length*2, length * 4,  length*2),  treeLeaves),
        VertexFormat(origin + glm::vec3(-length*2, length,  -length*2), treeLeaves),
        VertexFormat(origin + glm::vec3(length*2, length,  -length*2), treeLeaves),
        VertexFormat(origin + glm::vec3(-length*2, length * 4,  -length*2),  treeLeaves),
        VertexFormat(origin + glm::vec3(length*2, length * 4,  -length*2), treeLeaves),

    };

    vector<unsigned int> indices =
    {
        0, 1, 2,    
        1, 3, 2,    
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4,
        0, 2, 1,

        8, 9, 10,    
        9, 11, 10,   
        10, 11, 15,
        10, 15, 14,
        9, 15, 11,
        9, 13, 15,
        14, 15, 12,
        15, 13, 12,
        8, 12, 9,
        9, 12, 13,
        10, 14, 12,
        8, 10, 12,
        8, 10
    };
    Mesh* square = new Mesh(name);

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* Tema1::CreateRoad(
    const std::string& name,
    vector<glm::vec3> roadPoints)
{
    std::vector<VertexFormat> vertices;

    glm::vec3 P1 = roadPoints[0];
    glm::vec3 P2 = roadPoints[1];
    glm::vec3 D = P1 - P2;
    glm::vec3 P = glm::cross(D, UP);
    glm::vec3 R = P1 + distRosu * P;
    glm::vec3 A = P1 - distAlbastru * P;

    vertices.push_back(VertexFormat(R, black));
    vertices.push_back(VertexFormat(A, black));
    roadVert.push_back(R);
    roadVert.push_back(A);
    //Indices for two triangles - one backwards, one forward
    indices.push_back(2 * roadPoints.size() - 2);   //adding the previous red indice
    indices.push_back(0);       //adding the current red indice
    indices.push_back(1);   //adding the current blue indice
    indices.push_back(0);       //adding the current red indice
    
    indices.push_back(3);   //next blue
    indices.push_back(1);   //adding the current blue indice
    indices.push_back(0);       //adding the current red indice

    for (int i = 1; i < roadPoints.size() - 1; i++) {

        P1 = roadPoints[i];
        P2 = roadPoints[i+1];
        D = P1 - P2;
        P = glm::cross(D, UP);
        R = P1 + distRosu * P;
        A = P1 - distAlbastru * P;

        vertices.push_back(VertexFormat(R, black));
        vertices.push_back(VertexFormat(A, black));
        roadVert.push_back(R);
        roadVert.push_back(A);

        //Indices for two triangles - one backwards, one forward
        indices.push_back(2*i);       //adding the current red indice
        indices.push_back(2*i + 1);   //adding the current blue indice
        indices.push_back(2*i);       //adding the current red indice
        
        indices.push_back(2*i + 3);   //next blue
        indices.push_back(2*i + 1);   //adding the current blue indice
        indices.push_back(2 * i);       //adding the current red indice
    };

    // Add the remaining 2 indices
    P1 = roadPoints[roadPoints.size() - 1];
    P2 = roadPoints[0];
    D = P1 - P2;
    P = glm::cross(D, UP);
    R = P1 + distRosu * P;
    A = P1 - distAlbastru * P;

    vertices.push_back(VertexFormat(R, black));
    vertices.push_back(VertexFormat(A, black));
    roadVert.push_back(R);
    roadVert.push_back(A);

    //Indices for two triangles - one backwards, one forward
    indices.push_back(2 * (roadPoints.size() - 1));       //adding the current red indice
    indices.push_back(2 * (roadPoints.size() - 1) + 1);   //adding the current blue indice
    
    indices.push_back(2 * (roadPoints.size() - 1));       //adding the current red indice
    
    indices.push_back(1);                                 //next blue
    indices.push_back(2 * (roadPoints.size() - 1) + 1);   //adding the current blue indice

    Mesh* road = new Mesh(name);

    //road->SetDrawMode(GL_LINE_STRIP);
    road->InitFromData(vertices, indices);


    return road;
}


void Tema1::Init()
{
    camera->RotateOX(-75);

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("teapot");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* terrain = CreateTerrain("terrain", glm::vec3(-100,-0.25f,-100), 900);
        AddMeshToList(terrain);
    }
    {
        vector<glm::vec3> roadPoints = {
            glm::vec3(-23.45, 0,  -23.34), //A
            glm::vec3(-40.92, 0,  5.77),   //B
            glm::vec3(-42.86, 0,  33.51),  //C
            glm::vec3(-22, 0, 47.37),   //D
            glm::vec3(-7.3, 0,  57.1),     //E
            glm::vec3(20, 0,  60),    //F
            glm::vec3(28.14, 0,  33.5),    //G
            glm::vec3(35.72, 0,  8.81),      //H
            glm::vec3(67.24, 0,  20.71),     //I
            glm::vec3(86.94, 0,  5.77),       //J
            glm::vec3(109.96, 0,  -11.7),     //K
            glm::vec3(80, 0,  -43),    //L
            glm::vec3(54.5, 0,  -61.9),      //M
            glm::vec3(24.59, 0,  -84.5),       //N
            glm::vec3(-6.2, 0,  -52),       //O
        };
        vector<glm::vec3> roadPoints1 = {};
        float folds = 46;
        for (int i = 0; i < roadPoints.size() - 3; i+=3) {
            glm::vec3 A = roadPoints[i];
            glm::vec3 B = roadPoints[i + 1];
            glm::vec3 C = roadPoints[i + 2];
            glm::vec3 D = roadPoints[i + 3];

            for (int j = 0; j < folds; j++) {
                roadPoints1.push_back(bezier(j/folds, A, B, C, D));
            }
        }
        glm::vec3 A = roadPoints[roadPoints.size()-3];
        glm::vec3 B = roadPoints[roadPoints.size() - 2];
        glm::vec3 C = roadPoints[roadPoints.size() - 1];
        glm::vec3 D = roadPoints[0];
        for (int j = 0; j < folds; j++) {
            roadPoints1.push_back(bezier(j / folds, A, B, C, D));
        }
        roadPoints = roadPoints1;
        Mesh* road = CreateRoad("road", roadPoints);
        AddMeshToList(road);

        for (int i = 1; i <= nb_trees; i++) {
            float x = 0;
            float z = 0;
            bool res = true;
            while (res)
            {
                x = -200.f + (std::rand() % 401) + ((float)(std::rand() % 100) / 100);
                z = -200.f + (std::rand() % 401) + ((float)(std::rand() % 100) / 100);

                res = false;
                for (float k = 0; k < 3.f; k += 0.25f) {

                    res = res || CheckTreeOnRoad(glm::vec3(x + k, 0, z + k))
                        || CheckTreeOnRoad(glm::vec3(x - k, 0, z + k))
                        || CheckTreeOnRoad(glm::vec3(x + k, 0, z - k))
                        || CheckTreeOnRoad(glm::vec3(x - k, 0, z - k));
                }
            }
            treePos.push_back(glm::vec3(x, 0, z));
        }

        Mesh* tree = CreateTree("tree", glm::vec3(0, 0, 0), 1.f);
        AddMeshToList(tree);
    }

    string cycle[3] = { "box", "teapot", "sphere" };

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(resolution.x *3/4, resolution.y * 3 / 4, resolution.x / 4.f, resolution.y / 4.f);
}


double Tema1::TriangleArea(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
    glm::vec3 AB = glm::vec3(B.x - A.x, B.y - A.y, B.z - A.z);
    glm::vec3 AC = glm::vec3(C.x - A.x, C.y - A.y, C.z - A.z);
    glm::vec3 crossProd = cross(AB, AC);
    double area = (double)sqrt((double)((double)crossProd.x * (double)crossProd.x + (double)crossProd.y * (double)crossProd.y + (double)crossProd.z * (double)crossProd.z)) / 2;
    return area;
}

bool Tema1::CheckOnRoad(glm::vec3 pos) {
    for( int i = 0; i < indices.size(); i+=3)
    {
        glm::vec3 A = roadVert[indices[i]];
        glm::vec3 B = roadVert[indices[i+1]];
        glm::vec3 C = roadVert[indices[i+2]];

        double total = TriangleArea(A, B, C);
        double sum = 0;
        sum += TriangleArea(A, B, pos);
        sum += TriangleArea(A, C, pos);
        sum += TriangleArea(B, C, pos);

        if (abs(total - sum) <= 0.0001) {
            return true;
        }
    }
    return false;
}

bool Tema1::CheckTreeOnRoad(glm::vec3 pos) {
    for (int i = 0; i < indices.size(); i += 3)
    {
        glm::vec3 A = roadVert[indices[i]];
        glm::vec3 B = roadVert[indices[i+1]];
        glm::vec3 C = roadVert[indices[i+2]];

        double total = TriangleArea(A, B, C);
        double sum = 0;
        sum += TriangleArea(A, B, pos);
        sum += TriangleArea(A, C, pos);
        sum += TriangleArea(B, C, pos);

        if (abs(total - sum) <= NILL) {
            return true;
        }
    }
    return false;
}

void Tema1::FrameStart()
{

}

glm::vec3 Tema1::bezier(float t, glm::vec3 control_p0, glm::vec3 control_p1, glm::vec3 control_p2, glm::vec3 control_p3)
{
    return  (control_p0 * (float)pow((1 - t), 3) +
        control_p1 * 3.f * t * (float)pow((1 - t), 2) +
        control_p2 * 3.f * (float)pow(t, 2) * (1 - t) +
        control_p3 * (float)pow(t, 3));
}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    glClearColor(red, green, blue, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
    camera->SetPosition(glm::vec3(X - 7.5 * sin(rotateX), Y + 4.0f, Z - 7.5 * cos(rotateX)));
    camera->RotateOX(20);
    camera->SetPerspective(60, window->props.aspectRatio, 0.01f, 200);

    // Render the object again but with different properties
    modelMatrix = glm::mat4(1);
    modelMatrix *= Translate(X, Y, Z);
    modelMatrix *= RotateOY(rotateX);
    modelMatrix *= Scale(1.5, 1, 4);

    RenderMesh(meshes["box"], shaders["VertexColor"], modelMatrix, glm::vec3(X,Y,Z));


    RenderMesh(meshes["terrain"], shaders["VertexColor"], glm::vec3(0, 0.0f, 0), glm::vec3(1), glm::vec3(X, Y, Z));
    RenderMesh(meshes["road"], shaders["VertexColor"], glm::vec3(0, 0.0f, 0), glm::vec3(1), glm::vec3(X, Y, Z));


    for (int i = 0; i < nb_trees; i++) {
        RenderMesh(meshes["tree"], shaders["VertexColor"], treePos[i], glm::vec3(1, 2.0f, 1), glm::vec3(X, Y, Z));
    }
    
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
    camera->SetOrthographic(left, right, bottom, top, zNear, zFar);
    camera->SetPosition(glm::vec3(0, 0, 0));
    camera->RotateOX(-750);
    camera->SetPosition(glm::vec3(X, Y + 3.0f, Z));
    // Render the object
    RenderMesh(meshes[cycle[Counter]], glm::vec3(0, 1.f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    modelMatrix = glm::mat4(1);
    modelMatrix *= Translate(X, Y, Z);
    modelMatrix *= RotateOY(rotateX);
    modelMatrix *= Scale(1.5, 1, 4);
    
    RenderMesh(meshes["box"], shaders["VertexColor"], modelMatrix);

    RenderMesh(meshes["terrain"], shaders["VertexColor"], glm::vec3(0, 0.0f, 0));
    RenderMesh(meshes["road"], shaders["VertexColor"], glm::vec3(0, 0.0f, 0));

    for (int i = 0; i < nb_trees; i++) {
        RenderMesh(meshes["tree"], shaders["VertexColor"], treePos[i]);
    }
    camera->RotateOX(730);

}


void Tema1::FrameEnd()
{
    //DrawCoordinateSystem();
    
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_2)) {
        if (window->KeyHold(GLFW_KEY_S)) {
            float posX = X - sin(rotateX) * movementSpeed * deltaTime;
            float posZ = Z - cos(rotateX) * movementSpeed * deltaTime;
            bool ok = CheckOnRoad(glm::vec3(posX, 0, posZ));
            if (ok) 
            {
                Z = posZ;
                X = posX;
            }           
        }
        if (window->KeyHold(GLFW_KEY_W)) {
            float posZ = Z + cos(rotateX) * movementSpeed * deltaTime;
            float posX = X + sin(rotateX) * movementSpeed * deltaTime;
            bool ok = CheckOnRoad(glm::vec3(posX, 0, posZ));
            if (ok)
            {
                Z = posZ;
                X = posX;
            }
        }
        if (window->KeyHold(GLFW_KEY_D)) {
            rotateX -= deltaTime;
            rotateY = deltaTime * 572;
            camera->RotateOY(-deltaTime * 572);
        }
        if (window->KeyHold(GLFW_KEY_A)) {
            rotateX += deltaTime;
            rotateY = -deltaTime * 572;
            camera->RotateOY(deltaTime * 572);
        }
        if (window->KeyHold(GLFW_KEY_E)) {
            Y += movementSpeed * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_Q)) {
            Y -= movementSpeed * deltaTime;
        }
        
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_R) {
        red = 1 - red;
    }
    if (key == GLFW_KEY_G) {
        green = 1 - green;
    }
    if (key == GLFW_KEY_ENTER) {
        Counter++;
        if (Counter == 3) {
            Counter = 0;
        }
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event 
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Tema1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
