#pragma once

#include <cstdint>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec2 pos;
	glm::vec4 tex_pos;
};

constexpr uint32_t BOARD_SIZE = 64;
const uint32_t SCREEN_WIDTH = 1000;
const uint32_t SCREEN_HEIGHT = 1000;