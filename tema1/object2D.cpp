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
    glm::vec3 color2 = color;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color2),
        VertexFormat(corner + glm::vec3(length, length, 0), color2),
        VertexFormat(corner + glm::vec3(0, length, 0), color2),
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

Mesh* object2D::StrO(std::string name, glm::vec3 leftBottomCorner, float w, glm::vec3 color) {
    glm::vec3 corner = leftBottomCorner;
    glm::vec3 color2 = color;
    float theta;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    std::vector<VertexFormat> vertices;
    for (int i = 0; i < 360; i++) {
        theta = i * 3.1425 / 180;
        vertices.push_back(VertexFormat(corner + glm::vec3(150 * cos(theta), 150 * sin(theta), 0), color2));
    }


    Mesh* O = new Mesh(name);
 
    std::vector<unsigned int> indices;
    for (int i = 0; i < 360; i++) {
        indices.push_back(i);
    }
    indices.push_back(0);

    O->InitFromData(vertices, indices);
    return O;
}






