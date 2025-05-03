// Board.cpp
#include "Board.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Board::Board() // replace to the global shader in shader lib
    : m_Shader("Resources/shaders/board.glsl")
{
    m_Board = {
        bRook,bKnight,bBishop,bQueen,bKing,bBishop,bKnight,bRook,
        bPawn,bPawn,  bPawn,  bPawn, bPawn, bPawn,  bPawn,  bPawn,
        Empty,Empty,  Empty,  Empty, Empty, Empty,  Empty,  Empty,
        Empty,Empty,  Empty,  Empty, Empty, Empty,  Empty,  Empty,
        Empty,Empty,  Empty,  Empty, Empty, Empty,  Empty,  Empty,
        Empty,Empty,  Empty,  Empty, Empty, Empty,  Empty,  Empty,
        wPawn,wPawn,  wPawn,  wPawn, wPawn, wPawn,  wPawn,  wPawn,
        wRook,wKnight,wBishop,wQueen,wKing,wBishop,wKnight,wRook
    };

    m_Vertices.reserve(64 * 4);
    m_Indices.reserve(64 * 6);

    // one quad per square
    for (int sq = 0; sq < 64; ++sq) {
        int file = sq % 8, rank = sq / 8;
        float x0 = file - 4.f, y0 = rank - 4.f;
        float x1 = x0 + 1.f, y1 = y0 + 1.f;

        // placeholder UVs overwritten in updatePieceUVs()
        m_Vertices.push_back({ {x0,y0}, {0,0}, (float)sq });
        m_Vertices.push_back({ {x1,y0}, {1,0}, (float)sq });
        m_Vertices.push_back({ {x1,y1}, {1,1}, (float)sq });
        m_Vertices.push_back({ {x0,y1}, {0,1}, (float)sq });

        uint32_t b = sq * 4;
        m_Indices.insert(m_Indices.end(),
            { b, b + 1, b + 2, b + 2, b + 3, b });
    }

    setupBuffers();
}

Board::~Board() {
}

// refact 
void Board::setupBuffers() {

    m_Vao.bind();
    m_Vbo.bind();
    m_Vbo.load_buffer(m_Vertices); 

    m_Ebo.bind();
    m_Ebo.load_buffer(m_Indices.data(), m_Indices.size());

    m_Vao.link_attrib(m_Vbo, 0, 2, GL_FLOAT,
        sizeof(Vertex),
        (void*)offsetof(Vertex, pos));
    m_Vao.link_attrib(m_Vbo, 1, 2, GL_FLOAT,
        sizeof(Vertex),
        (void*)offsetof(Vertex, uv));
    m_Vao.link_attrib(m_Vbo, 2, 1, GL_FLOAT,
        sizeof(Vertex),
        (void*)offsetof(Vertex, pickId));

    m_Vao.unbind();
    m_Vbo.unbind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Board::updatePieceUVs() {
    
    for (int sq = 0; sq < 64; ++sq) 
    {
        auto uv = getAtlasUV(m_Board[sq]);
        int b = sq * 4;
        m_Vertices[b + 0].uv = { uv.bl.x , uv.bl.y };
		m_Vertices[b + 1].uv = { uv.tr.x , uv.bl.y };
        m_Vertices[b + 2].uv = { uv.bl .x , uv.tr.y };
		m_Vertices[b + 3].uv = { uv.bl.x , uv.tr.y };
    }
    
    m_Vao.bind();
    m_Vbo.bind();

    // to replace
    glBufferSubData(GL_ARRAY_BUFFER,
        0,
        m_Vertices.size() * sizeof(Vertex),
        m_Vertices.data());
    m_Vao.unbind();
    m_Vbo.unbind();
}

void Board::render(const glm::mat4& viewProj) {
    m_ViewProj = viewProj;
    m_Shader.bind();
    m_Shader.set_uniform_mat4f("u_ViewProj", m_ViewProj);
    m_Shader.set_uniform_1i("u_AtlasTex", m_Texture.get_texture_ID());
    m_Shader.set_uniform_1i("u_Selected", m_Selected);
    m_Shader.set_uniform_vec3f("u_LightCol", glm::vec3(0.9f));
    m_Shader.set_uniform_vec3f("u_DarkCol", glm::vec3(0.2f, 0.25f, 0.3f));
    m_Shader.set_uniform_vec3f("u_HighlightCol", glm::vec3(1.0f, 1.0f, 0.0f));

    updatePieceUVs();

    // will replace these

    glActiveTexture(GL_TEXTURE0 + m_Texture.get_texture_ID());
    glBindTexture(GL_TEXTURE_2D,
        Texture::get_texture(m_Texture.get_texture_ID())
        .get_texture_ID());

    m_Vao.bind();
    glDrawElements(GL_TRIANGLES,
        (GLsizei)m_Indices.size(),
        GL_UNSIGNED_INT,
        nullptr);
    m_Vao.unbind();
}

int Board::pickSquare(double mx, double my) 
{

    int w = 800, h = 600;
    glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);

    float nx = (mx / w) * 8.f - 4.f;
    float ny = ((h - my) / h) * 8.f - 4.f;

    int file = int(std::floor(nx));
    int rank = int(std::floor(ny));

    if (file < 0 || file > 7 || rank < 0 || rank > 7)
        return -1;

    return rank * 8 + file;
}

bool Board::handleClick(GLFWwindow* window) 
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)
        != GLFW_PRESS)
        return false;

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    int sq = pickSquare(x, y);
    if (sq < 0) return false;

    if (m_Selected < 0) 
    {
        if (m_Board[sq] != Empty)
            m_Selected = sq;
    }
    else 
    {
        movePiece(m_Selected, sq);
        m_Selected = -1;
        return true;
    }
    return false;
}

void Board::movePiece(int from, int to) {
    m_Board[to] = m_Board[from];
    m_Board[from] = Empty;
}
