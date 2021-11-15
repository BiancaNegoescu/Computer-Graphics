#include "lab_m1/tema1/tema1.h"
#include "transform2D.h"
#include "object2D.h"

#include <vector>
#include <iostream>
#include <cmath>
#include "utils/gl_utils.h"
#include "core/engine.h"







using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


tema1::tema1()
{
    // TODO(student): Never forget to initialize class variables!

}


tema1::~tema1()
{
}


void tema1::Init()
{

    dead = 0;
    GetLocalTime(&time0);
   /* struct Coord {
        float x;
        float y;
        float latime;
        float inaltime;
        float killed;
    };*/
    coordsInamici = { {0,  -50,   10,  22.5,  0}, {60,0,10,22.5,0}, {-40,-30,10,22.5,0} };
    mapX = -100;
    mapY = -60;
    lungimeMap = 200;
    latimeMap = 120;
    health = 200;
    score = 0;
   
    mouseRotate;
    zoomPercentage = 1;
    vitezaProiectil = 0;
    movement = 10;
    proiectilAruncat = 0;
    float cameraX = 0;
    float cameraY = 0;
    translateProiectilX = 0;
    translateProiectilY=0;
    glm::vec3 corner = glm::vec3(0, 0, 0);
    playerX = 0;
    playerY = 0;
    translateEnemyX = 0; 
    translateEnemyY = 0;
    degrees = 0;
    rotatieProiectil = 0;
    allowedToShot = 0;
    click = 0;
    colizProiMap = 0;

    ox = 0;
    oy = 0;
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    

    squareSide = 10;
    playerAngle = 0;

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 100;   // logic width
    logicSpace.height = 100;

    logicSpaceMare.x = 0;
    logicSpaceMare.y = 0;
    logicSpaceMare.width = 500;
    logicSpaceMare.height = 500;
    semn;
    timp = 0;
    lastShot = 0;
    currentShot;
    coliziuneInamic = 0;
    latimeProiectil = 3;
    inaltimeProiectil = 4;

    playerX = (corner.x + logicSpace.width) / 2;
    playerY = (corner.y + logicSpace.height ) / 2 + 1; //mai aare ochii care il face mai mare

    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    


    Mesh* square1 = object2D::CreateSquare("square1", corner, length, glm::vec3(1, 1, 0.4));
    AddMeshToList(square1);

    // creez healtbg
    vector<VertexFormat> verticesbg
    {
        VertexFormat(glm::vec3(40, 35,  0), glm::vec3(0.5), glm::vec3(0,0,0)), // 0

        VertexFormat(glm::vec3(80, 35, 0), glm::vec3(0.5), glm::vec3(0,0,0)), // 1
        VertexFormat(glm::vec3(80, 45, 0), glm::vec3(0.5), glm::vec3(0,0,0)), // 2
         VertexFormat(glm::vec3(40, 45, 0), glm::vec3(0.5), glm::vec3(0,0,0)), // 3


    };

    vector<unsigned int> indicesbg =
    {
            0,1,2,
            0,2,3


    };

    meshes["bg"] = new Mesh("generatedbg");
    meshes["bg"]->InitFromData(verticesbg, indicesbg);

    // creez harta
    // harta are lungimea de 200 si latimea de 120

    vector<VertexFormat> verticesMap
    {
        VertexFormat(glm::vec3(-100, -60,  0), glm::vec3(1,1,0.4), glm::vec3(0,0,0)), // 0
        VertexFormat(glm::vec3(-100,60, 0), glm::vec3(1,1,0.4), glm::vec3(0,0,0)), // 1
        VertexFormat(glm::vec3(100, 60, 0), glm::vec3(1,1,0.4), glm::vec3(0,0,0)), // 2
        VertexFormat(glm::vec3(100, -60, 0), glm::vec3(1,1,0.4), glm::vec3(0,0,0)), // 3

    };

    vector<unsigned int> indicesMap =
    {
            0,3,1,
            1,3,2

    };

    meshes["map"] = new Mesh("generatedMap");
    meshes["map"]->InitFromData(verticesMap, indicesMap);

    // creez health1
    vector<VertexFormat> verticesHealth1
    {
       VertexFormat(glm::vec3(60, 35, 0), glm::vec3(0,1,0), glm::vec3(0,0,0)), // 3
        VertexFormat(glm::vec3(80, 35, 0), glm::vec3(0,1,0), glm::vec3(0,0,0)), // 4
        VertexFormat(glm::vec3(80, 45, 0), glm::vec3(0,0,0), glm::vec3(0,0,0)) // 5
      

    };

    vector<unsigned int> indicesHealth1 =
    {
            0,1,2
            

    };

    meshes["health1"] = new Mesh("generatedHealth1");
    meshes["health1"]->InitFromData(verticesHealth1, indicesHealth1);

    // creez health2
    vector<VertexFormat> verticesHealth2
    {
        VertexFormat(glm::vec3(60, 35,  0), glm::vec3(0,1,0), glm::vec3(0,0,0)), // 0
       
        VertexFormat(glm::vec3(80, 45, 0), glm::vec3(0,1,0), glm::vec3(0,0,0)), // 1
        VertexFormat(glm::vec3(60, 45, 0), glm::vec3(0,0,0), glm::vec3(0,0,0)), // 2
       

    };

    vector<unsigned int> indicesHealth2 =
    {
            0,1,2
           

    };

    meshes["health2"] = new Mesh("generatedHealth2");
    meshes["health2"]->InitFromData(verticesHealth2, indicesHealth2);

    // creez health3
    vector<VertexFormat> verticesHealth3
    {
        VertexFormat(glm::vec3(40, 35, 0), glm::vec3(0,1,0), glm::vec3(0,0,0)), // 0
        VertexFormat(glm::vec3(60, 35, 0), glm::vec3(0,1,0), glm::vec3(0,0,0)), // 1
        VertexFormat(glm::vec3(60, 45, 0), glm::vec3(0,0,0), glm::vec3(0,0,0)), // 2
       

    };

    vector<unsigned int> indicesHealth3 =
    {
            0,1,2
          

    };

    meshes["health3"] = new Mesh("generatedHealth3");
    meshes["health3"]->InitFromData(verticesHealth3, indicesHealth3);

    // creez health4
    vector<VertexFormat> verticesHealth4
    {
       
        VertexFormat(glm::vec3(40, 35, 0), glm::vec3(0,1,0), glm::vec3(0,0,0)), // 3
        VertexFormat(glm::vec3(60, 45, 0), glm::vec3(0,1,0), glm::vec3(0,0,0)), // 4
        VertexFormat(glm::vec3(40, 45, 0), glm::vec3(0,0,0), glm::vec3(0,0,0)) // 5

    };

    vector<unsigned int> indicesHealth4 =
    {
            0,1,2
          

    };

    meshes["health4"] = new Mesh("generatedHealth4");
    meshes["health4"]->InitFromData(verticesHealth4, indicesHealth4);
   
    // creez player
    
    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1,0.4,0.4), glm::vec3(0,0,0)), // 0
        VertexFormat(glm::vec3(0,10, 0), glm::vec3(1,0.4,0.4), glm::vec3(0,0,0)), // 1
        VertexFormat(glm::vec3(10, 10, 0), glm::vec3(1,0.4,0.4), glm::vec3(0,0,0)), // 2
        VertexFormat(glm::vec3(10, 0, 0), glm::vec3(1,0.4,0.4), glm::vec3(0,0,0)), // 3

    };

    vector<unsigned int> indices =
    {
            0,3,1,
            1,3,2

    };

    meshes["player"] = new Mesh("generatedPlayer");
    meshes["player"]->InitFromData(vertices, indices);

    // creez proiectil

    vector<VertexFormat> verticesProiectil
    {
        VertexFormat(glm::vec3(3.5, -2,  0), glm::vec3(0,0,0), glm::vec3(0,0,0)), // 0
        VertexFormat(glm::vec3(6.5,-2, 0), glm::vec3(0,0,0), glm::vec3(0,0,0)), // 1
        VertexFormat(glm::vec3(5, 0, 0), glm::vec3(0,0,0), glm::vec3(0,0,0)), // 2
        VertexFormat(glm::vec3(5, -4, 0), glm::vec3(0,0,0), glm::vec3(0,0,0)), // 3

    };

    vector<unsigned int> indicesProiectil =
    {
            0,1,2,
            0,3,1

    };

    meshes["proiectil"] = new Mesh("generatedProiectil");
    meshes["proiectil"]->InitFromData(verticesProiectil, indicesProiectil);



    // creez obstacol
    // primul obstacol are lungimea de 30 si h = 50
    vector<VertexFormat> verticesObstacle
    {
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1,0.27,0), glm::vec3(0,0,0)), // 0
        VertexFormat(glm::vec3(0,50, 0), glm::vec3(1,0.27,0), glm::vec3(0,0,0)), // 1
        VertexFormat(glm::vec3(30, 50, 0), glm::vec3(1,0.27,0), glm::vec3(0,0,0)), // 2
        VertexFormat(glm::vec3(30, 0, 0), glm::vec3(1,0.27,0), glm::vec3(0,0,0)), // 3

    };

    vector<unsigned int> indicesObstacle =
    {
            0,3,1,
            1,3,2

    };

    meshes["obstacol"] = new Mesh("generatedObstacol");
    meshes["obstacol"]->InitFromData(verticesObstacle, indicesObstacle);

    // creez obstacol2
    // L = 80, h = 20

    vector<VertexFormat> verticesObstacle2
    {
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1,0.27,0), glm::vec3(0,0,0)), // 0
        VertexFormat(glm::vec3(0,20, 0), glm::vec3(1,0.27,0), glm::vec3(0,0,0)), // 1
        VertexFormat(glm::vec3(80, 20, 0), glm::vec3(1,0.27,0), glm::vec3(0,0,0)), // 2
        VertexFormat(glm::vec3(80, 0, 0), glm::vec3(1,0.27,0), glm::vec3(0,0,0)), // 3

    };

    vector<unsigned int> indicesObstacle2 =
    {
            0,3,1,
            1,3,2

    };

    meshes["obstacol2"] = new Mesh("generatedObstacol2");
    meshes["obstacol2"]->InitFromData(verticesObstacle2, indicesObstacle2);

    // creez ochi 1
    vector<VertexFormat> verticesEye1 
    {
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), // 0
        VertexFormat(glm::vec3(1.5,2,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), // 1
        VertexFormat(glm::vec3(3.5,2,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), // 2
        VertexFormat(glm::vec3(5,0,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), // 3
        VertexFormat(glm::vec3(3.5,-2,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //4
        VertexFormat(glm::vec3(1.5,-2,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //5
        VertexFormat(glm::vec3(1.5,0,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //6
        VertexFormat(glm::vec3(3.5,0,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //7

    };

    vector<unsigned int> indicesEye1 =
    {

            0,6,1,
            6,7,1,
            1,7,2,
            7,3,2,
            0,5,6,
            5,4,6,
            6,4,7,
            7,4,3

    };

    meshes["eye1"] = new Mesh("generatedEye1");
    meshes["eye1"]->InitFromData(verticesEye1, indicesEye1);

    // creez ochi 2
    vector<VertexFormat> verticesEye2
    {
        VertexFormat(glm::vec3(5,0,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), // 0
        VertexFormat(glm::vec3(6.5,2,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //1
        VertexFormat(glm::vec3(8.5,2,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //2
        VertexFormat(glm::vec3(10,0,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //3
        VertexFormat(glm::vec3(8.5,-2,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //4
        VertexFormat(glm::vec3(6.5,-2,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //5
        VertexFormat(glm::vec3(6.5,0,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //6
        VertexFormat(glm::vec3(8.5,0,0), glm::vec3(0.11, 0.56, 1), glm::vec3(0,0,0)), //7

    };

    vector<unsigned int> indicesEye2 =
    {

            0,6,1,
            6,7,1,
            1,7,2,
            7,3,2,
            0,5,6,
            5,4,6,
            6,4,7,
            7,4,3

    };

    meshes["eye2"] = new Mesh("generatedEye2");
    meshes["eye2"]->InitFromData(verticesEye2, indicesEye2);
    

    // creez inamic

    vector<VertexFormat> verticesInamic
    {
        VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0.5,0,0), glm::vec3(0,0,0)), // 0
        VertexFormat(glm::vec3(0,10, 0), glm::vec3(0.5,0,0), glm::vec3(0,0,0)), // 1
        VertexFormat(glm::vec3(5, 10, 0), glm::vec3(0.5,0,0), glm::vec3(0,0,0)), // 2
        VertexFormat(glm::vec3(10, 20, 0), glm::vec3(0.5,0,0), glm::vec3(0,0,0)), // 3
        VertexFormat(glm::vec3(0, 20, 0), glm::vec3(0.5,0,0), glm::vec3(0,0,0)), // 4
        VertexFormat(glm::vec3(2.5, 20, 0), glm::vec3(0.5,0,0), glm::vec3(0,0,0)), // 5
        VertexFormat(glm::vec3(7.5, 20, 0), glm::vec3(0.5,0,0), glm::vec3(0,0,0)), // 6
        VertexFormat(glm::vec3(8.75, 22.5, 0), glm::vec3(0,0,0), glm::vec3(0,0,0)), // 7
        VertexFormat(glm::vec3(1.25, 22.5, 0), glm::vec3(0,0,0), glm::vec3(0,0,0)), // 8
        VertexFormat(glm::vec3(10, 10, 0), glm::vec3(0.5,0,0), glm::vec3(0,0,0)), // 9
        VertexFormat(glm::vec3(10,0, 0), glm::vec3(0.5,0,0), glm::vec3(0,0,0)), // 10


    };

    vector<unsigned int> indicesInamic =
    {
            0,1,2,
            2,10,9,
            4,2,3,
            4,5,8,
            6,3,7

    };

    meshes["inamic"] = new Mesh("generatedInamic");
    meshes["inamic"]->InitFromData(verticesInamic, indicesInamic);


}

// 2D visualization matrix
glm::mat3 tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}

glm::mat3 tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(1, 0.4, 0.4, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


void tema1::Update(float deltaTimeSeconds)
{
    
    timp += deltaTimeSeconds;
   
  
   
   /* if ((proiectilAruncat == 0) && (allowedToShot == 1) && (timp - lastShot == 3)) {
        allowedToShot = 0;
    }*/

    glm::ivec2 resolution = window->GetResolution();
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);

    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    DrawScene(visMatrix2, visMatrix, deltaTimeSeconds);  

}



void tema1::DrawScene(glm::mat3 visMatrix2, glm::mat3 visMatrix, float deltaTimeSeconds)
{

    glm::ivec2 resolution = window->GetResolution();
    if (dead == 0) {

            modelMatrix = visMatrix * transform2D::Translate(translateX, translateY);
            modelMatrix *= transform2D::Translate(playerX, playerY);
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= mouseRotate;
            modelMatrix *= transform2D::Translate(-cx, -cy);
            RenderMesh2D(meshes["eye1"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix * transform2D::Translate(translateX, translateY);
            modelMatrix *= transform2D::Translate(playerX, playerY);
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= mouseRotate;
            modelMatrix *= transform2D::Translate(-cx, -cy);
            RenderMesh2D(meshes["eye2"], shaders["VertexColor"], modelMatrix);


            modelMatrix = visMatrix * transform2D::Translate(translateX, translateY);
            modelMatrix *= transform2D::Translate(playerX, playerY);
            modelMatrix *= transform2D::Translate(cx, cy);
            modelMatrix *= mouseRotate;
            modelMatrix *= transform2D::Translate(-cx, -cy);
            RenderMesh2D(meshes["player"], shaders["VertexColor"], modelMatrix);

        

        
    }

    for (int i = 0; i < coordsInamici.size(); i++) {
        // coliziune player=inamic
        if ( coordsInamici[i].killed == 0 &&
            ((playerX + translateX  <= (playerX + coordsInamici[i].x + coordsInamici[i].latime))
                && (playerX + translateX + squareSide >= playerX + coordsInamici[i].x))

            &&
            ((playerY+ translateY  <= (playerY + coordsInamici[i].y + coordsInamici[i].inaltime))
                && (playerY + translateY + squareSide >= playerY + coordsInamici[i].y))
            ) {
            
            health--;
        }
    }

    if (health <= 0) {
        dead = 1;
        cout << "GAME OVER!!!" << "\n";

    }

    if (health > 0) {
        modelMatrix = visMatrix * transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Translate(playerX, playerY);
        modelMatrix *= transform2D::Translate(cx, cy);
        //modelMatrix *=  transform2D::Rotate(M_PI / 2);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        RenderMesh2D(meshes["health1"], shaders["VertexColor"], modelMatrix);
    }
    if (health > 50) {
        modelMatrix = visMatrix * transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Translate(playerX, playerY);
        modelMatrix *= transform2D::Translate(cx, cy);
        //modelMatrix *= transform2D::Rotate(M_PI / 2);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        RenderMesh2D(meshes["health2"], shaders["VertexColor"], modelMatrix);
    } 
    if (health > 100) {
       
        modelMatrix = visMatrix * transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Translate(playerX, playerY);
        modelMatrix *= transform2D::Translate(cx, cy);
        //modelMatrix *=  transform2D::Rotate(M_PI / 2);
        modelMatrix *= transform2D::Translate(-cx, -cy);
   
       

        RenderMesh2D(meshes["health3"], shaders["VertexColor"], modelMatrix);
    }
    if (health > 150) {
       
        modelMatrix = visMatrix * transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Translate(playerX, playerY);
        modelMatrix *= transform2D::Translate(cx, cy);
        //modelMatrix *= transform2D::Rotate(M_PI / 2);
        modelMatrix *= transform2D::Translate(-cx, -cy);
      
        RenderMesh2D(meshes["health4"], shaders["VertexColor"], modelMatrix);
    }
    modelMatrix = visMatrix * transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(playerX, playerY);
    modelMatrix *= transform2D::Translate(cx, cy);
    //modelMatrix *= transform2D::Rotate(M_PI / 2);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    RenderMesh2D(meshes["bg"], shaders["VertexColor"], modelMatrix);
    


    modelMatrix = visMatrix * transform2D::Translate(0,0);
    modelMatrix *= transform2D::Translate(playerX, playerY);
    modelMatrix *= transform2D::Scale(0.9, 0.9);
    modelMatrix *= transform2D::Translate(-100, -60); // in coltul mapei
   RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(0, 0);
    modelMatrix *= transform2D::Translate(playerX, playerY);
    modelMatrix *= transform2D::Translate(70, 10); // 100 - 30, 60 -50
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(0, 0);
    modelMatrix *= transform2D::Translate(playerX, playerY);
    modelMatrix *= transform2D::Translate(-20 ,20); 
    modelMatrix *= transform2D::Rotate(1.57);
    modelMatrix *= transform2D::Scale(0.8, 0.8);
   RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(0, 0);
    modelMatrix *= transform2D::Translate(playerX, playerY);
    modelMatrix *= transform2D::Translate(100-80, -60); // coltul mapei dreapta jos
   RenderMesh2D(meshes["obstacol2"], shaders["VertexColor"], modelMatrix);

   /*modelMatrix = visMatrix * transform2D::Translate(playerX, playerY);
   modelMatrix *= transform2D::Translate(cx, cy);
   modelMatrix *= mouseRotate;
   modelMatrix *= transform2D::Translate(-cx, -cy);
   RenderMesh2D(meshes["proiectil"], shaders["VertexColor"], modelMatrix);*/

   if (allowedToShot)
   { 
       float x_translate;
       float y_translate;
       if (semn == 0) {
           x_translate = abs(deltaTimeSeconds * cos(rotatieProiectil) * vitezaProiectil * 10);
           y_translate = -deltaTimeSeconds * sin(rotatieProiectil) * vitezaProiectil * 10;
       }
       else {
           x_translate = -deltaTimeSeconds * cos(rotatieProiectil) * vitezaProiectil * 10;
           y_translate = deltaTimeSeconds * sin(rotatieProiectil) * vitezaProiectil * 10;
       }
       glm::mat3 model_matrix = glm::mat3(1);
       model_matrix = visMatrix * transform2D::Translate(translateProiectilX + translateX +  x_translate,translateProiectilY + translateY +  y_translate);
       //model_matrix *= transform2D::Translate(playerX, playerY);
       model_matrix *= transform2D::Translate(cx, cy);
       model_matrix *= mouseRotate;
       model_matrix *= transform2D::Translate(-cx, -cy);

       
      // RenderMesh2D(meshes["proiectil"], shaders["VertexColor"], model_matrix);
      /* translateProiectilX += x_translate;
       translateProiectilY += y_translate;
       lastShot = currentShot;*/

      


      

       //for (int i = 0; i < coordsInamici.size(); i++) {
       //    if (coordsInamici[i].x < translateProiectilX + latimeProiectil &&
       //        coordsInamici[i].x + coordsInamici[i].latime > translateProiectilX &&
       //        coordsInamici[i].y < translateProiectilY + inaltimeProiectil &&
       //        coordsInamici[i].inaltime + coordsInamici[i].y > translateProiectilY
       //        ) { // daca e coliziue randez
       //        coordsInamici[i].killed = 1;
       //        cout << "kileed " <<i<< '\n';
       //      
       //    }
       //}

       for (int i = 0; i < coordsInamici.size(); i++) {
           if (dead == 0 &&
               ((translateProiectilX + translateX <= (playerX + coordsInamici[i].x + coordsInamici[i].latime))
                   && ((translateProiectilX + translateX + inaltimeProiectil) >= playerX + coordsInamici[i].x))

               &&
               ((translateProiectilY + translateY <= (playerY + coordsInamici[i].y + coordsInamici[i].inaltime))
                   && ((translateProiectilY + translateY + latimeProiectil) >= playerY + coordsInamici[i].y))
               ) { // daca e coliziue proiectil-inamic
              
              
               coordsInamici[i].killed = 1;
               score = score + 100;
               

           } 
           cout << "SCORE: " << score << "\n";       
       }

       // verificare coliziune  proiectil-perete 
       
       if (!((translateProiectilX + inaltimeProiectil >= playerX - 10 - translateX + 100) || (translateProiectilX <= playerX - translateX - 100)
           || (translateProiectilY + inaltimeProiectil >= playerY - 10 - translateY + 60) || (translateProiectilY <= playerY - translateY - 60)
           ))
            { // daca nu e coliziune cu mapa, il mai randez
      // cout << playerX << " " << playerY << "\n"<<translateX<<" " <<translateY<<" " << translateProiectilX << " " << translateProiectilY << "\n"; 
           RenderMesh2D(meshes["proiectil"], shaders["VertexColor"], model_matrix);
       }
       //RenderMesh2D(meshes["proiectil"], shaders["VertexColor"], model_matrix);
       translateProiectilX += x_translate;
       translateProiectilY += y_translate;
       lastShot = currentShot;

   }

  /* modelMatrix = visMatrix * transform2D::Translate(coordsInamici[0].x, coordsInamici[0].y);
   modelMatrix *= transform2D::Translate(playerX, playerY);
   RenderMesh2D(meshes["inamic"], shaders["VertexColor"], modelMatrix);*/
   
  
   for (int i = 0; i < coordsInamici.size(); i++) {
       
       
       if (coordsInamici[i].killed == 0.f) {
           
           modelMatrix = glm::mat3(1);
           float x = coordsInamici[i].x;
           float y = coordsInamici[i].y;
           //modelMatrix = visMatrix * transform2D::Translate(translateEnemyX, translateEnemyY);
           modelMatrix = visMatrix * transform2D::Translate(coordsInamici[i].x, coordsInamici[i].y);
           modelMatrix *= transform2D::Translate(playerX, playerY);
           RenderMesh2D(meshes["inamic"], shaders["VertexColor"], modelMatrix);
        }
   }

       ////desenare inamic jos dreapta
       // modelMatrix = visMatrix*transform2D::Translate(translateEnemyX, translateEnemyY)* transform2D::Translate(0, -50) *  transform2D::Translate(playerX, playerY);
      
       // RenderMesh2D(meshes["inamic"], shaders["VertexColor"], modelMatrix);

       // //desenare inamic dreapta

       // modelMatrix = visMatrix * transform2D::Translate(translateEnemyX, translateEnemyY) * transform2D::Translate(60, 0) * transform2D::Translate(playerX, playerY);

       // RenderMesh2D(meshes["inamic"], shaders["VertexColor"], modelMatrix);

       // //desenare inamic jos stanga
       // modelMatrix = visMatrix * transform2D::Translate(translateEnemyX, translateEnemyY) * transform2D::Translate(-40, -30) * transform2D::Translate(playerX, playerY);

       // RenderMesh2D(meshes["inamic"], shaders["VertexColor"], modelMatrix);
    

    modelMatrix = glm::mat3(1);
   
    modelMatrix = visMatrix * transform2D::Translate(playerX, playerY);
    RenderMesh2D(meshes["map"], shaders["VertexColor"], modelMatrix);

}


void tema1::AruncaProiectil(float speed)
{
    
    vitezaProiectil = speed;
    translateProiectilX = playerX;
    translateProiectilY = playerY;
    
    allowedToShot = 1;
   
}

void tema1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void tema1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.

    auto camera = GetSceneCamera();
    glm::ivec2 resolution = window->GetResolution();

    
    
    if (dead == 0) {
        if (window->KeyHold(GLFW_KEY_S))
        {

            if (translateY - 2.5 > -60) {
                logicSpace.y -= deltaTime * 100.f;
                translateY -= deltaTime * 100.f;
            }

            translateEnemyY += deltaTime * 100.f;

        }
        if (window->KeyHold(GLFW_KEY_W))
        {

            if (translateY + squareSide + 2.5 < 60) {
                translateY += deltaTime * 100.f;
                logicSpace.y += deltaTime * 100.f;
            }

            translateEnemyY += deltaTime * 100.f;

        }
        if (window->KeyHold(GLFW_KEY_D))
        {


            if (translateX + squareSide + 2.5 < 100) {
                translateX += deltaTime * 100.f;
                logicSpace.x += deltaTime * 100.f;
            }
            translateEnemyX += deltaTime * 100.f;

        }
        if (window->KeyHold(GLFW_KEY_A))
        {


            if (translateX - 2.5 > -100) {
                translateX -= deltaTime * 100.f;
                logicSpace.x -= deltaTime * 100.f;
            }

            translateEnemyX -= deltaTime * 100.f;

        }
    }
    if (window->KeyHold(GLFW_KEY_Z))
    {
        GLfloat zoomAmount = deltaTime * zoomPercentage*100;

        logicSpace.x += logicSpace.width / movement;
        logicSpace.y += logicSpace.height / movement;
        logicSpace.width -= zoomAmount;
        logicSpace.height -= zoomAmount;
        logicSpace.x -= logicSpace.width / movement;
        logicSpace.y -= logicSpace.height / movement;
    }
    if (window->KeyHold(GLFW_KEY_X))
    {
        GLfloat zoomAmount = deltaTime * zoomPercentage*100;
        logicSpace.x += logicSpace.width / movement;
        logicSpace.y += logicSpace.height / movement;
        logicSpace.width += zoomAmount;
        logicSpace.height += zoomAmount;
        logicSpace.x -= logicSpace.width / movement;
        logicSpace.y -= logicSpace.height / movement;


    }
    

}


void tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {
        // TODO(student): Change the values of the color components.

    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.

}


void tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // rotate bow towards mouse position
        glm::ivec2 resolution = window->GetResolution();
        float cateta1 = mouseY - (resolution.y / 2);
        float cateta2 = mouseX - (resolution.x / 2);
        float ipotenuza = sqrt(cateta1 * cateta1 + cateta2 * cateta2);
        float sinus = cateta2 / ipotenuza;
        float cosinus = cateta1 / ipotenuza;
        degrees = (float)atan(cateta1 /cateta2);
        
        mouseRotate = glm::transpose(
            glm::mat3(cosinus, -sinus, 0,
                sinus, cosinus, 0,
                0, 0, 1));
    
}


void tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    proiectilAruncat = 1;
    click = timp;
    if (dead == 0) {
        if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
            rotatieProiectil = degrees;
            proiectilAruncat = 0;
            //is_charging_shot = false;
            //power_indicator_scale_factor = 1.f;
            //power_indicator_matrix = glm::mat3(1);
            //float speed = (time_elapsed - click_time) * 15.f;
            vitezaProiectil = 10;
            if (mouseX >= 630) {
                semn = 0;
            }
            else {
                semn = 1;
            }
            // speed = min(20.f, speed);
            // currentShot = timp;
            currentShot = timp;
            if (timp - lastShot >= 3 || lastShot == 0) { // arunca doar dupa 3 secune sau daca e priul shot
                AruncaProiectil(vitezaProiectil);
            }

        }
    }
    
}


void tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    
    
}


void tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void tema1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
