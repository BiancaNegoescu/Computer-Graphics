#pragma once

#include "components/simple_scene.h"
#include <windows.h>
#include <stdio.h>
#include <vector>



namespace m1
{
    class tema1 : public gfxc::SimpleScene
    {
       

    public:
    struct ViewportSpace
    {
        ViewportSpace() : x(0), y(0), width(1), height(1) {}
        ViewportSpace(int x, int y, int width, int height)
            : x(x), y(y), width(width), height(height) {}
        int x;
        int y;
        int width;
        int height;
    };

    struct LogicSpace
    {
        LogicSpace() : x(0), y(0), width(1), height(1) {}
        LogicSpace(float x, float y, float width, float height)
            : x(x), y(y), width(width), height(height) {}
        float x;
        float y;
        float width;
        float height;
    };

     public:
        tema1();
        ~tema1();

        void Init() override;

     private:
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix, glm::mat3 visMatrix2, float deltaTimeSeconds);
        void DrawEnemy(glm::mat3 visMatrix);
        void AruncaProiectil(float);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);
        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        

        // TODO(student): Class variables go here
    protected:
        float cx, cy;
        float length;
        float playerX, playerY;
        float squareSide;
        float playerAngle;
        float cameraX;
        float cameraY;
        float zoomPercentage;
        float movement;
        SYSTEMTIME time0;
        int dead;
        float ox, oy;
        float vitezaProiectil;
        float rotatieProiectil;
        float degrees;
        int proiectilAruncat;
        
        float translateEnemyX, translateEnemyY;
        float translateProiectilX, translateProiectilY;
        struct Coord {
            float x;
            float y;
            float latime;
            float inaltime;
            float killed;
            
        };
        float health;
        float score;
        float latimeProiectil;
        float inaltimeProiectil;
        std::vector <Coord> coordsInamici;
        float mapX, mapY, lungimeMap, latimeMap, colizProiMap;

        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float semn;
        float timp;
        float lastShot;
        float currentShot;
        float allowedToShot;
        float click;
        float coliziuneInamic;
        float angularStep;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        LogicSpace logicSpaceMare;
        ViewportSpace viewSpaceMare;
        glm::mat3 visMatrix;
        glm::mat3 visMatrix2;
        GLenum cullFace;
        GLenum polygonMode;
        glm::mat3 mouseRotate;

    };
}   // namespace m1
