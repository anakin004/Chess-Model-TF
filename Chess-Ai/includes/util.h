#pragma once

#include <cstdint>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec2 pos;
	glm::vec4 tex_pos;
};

constexpr uint32_t BOARD_SIZE = 64;