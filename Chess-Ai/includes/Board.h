#pragma once

#include "util.h"        
#include "Texture.h"
#include "Shader.h"
#include "VAO.h"
#include "EBO.h"
#include "VBO.h"
#include <glm/glm.hpp>
#include <array>
#include <vector>
#include <GLFW/glfw3.h>

class Board {
public:
    Board();
    ~Board();


    void render(const glm::mat4& viewProj);
    bool handleClick(GLFWwindow* window);
    void movePiece(int from, int to);

private:
    std::array<Piece, 64> m_Board;
    int m_Selected = -1;

    VAO m_Vao;
    VBO m_Vbo;
    EBO m_Ebo;
    Shader m_Shader;
    Texture m_Texture;

    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;

    glm::mat4 m_ViewProj;

    void setupBuffers();
    void updatePieceUVs();
    int  pickSquare(double mx, double my);
};