#pragma once

//We are linking statically with GLEW
#define GLEW_STATIC

// GLEW header
#include <GL/glew.h>

// Other library headers
#include <GLFW/glfw3.h>

// Project headers
#include "Renderer.h"
#include "Game.h"

int main();