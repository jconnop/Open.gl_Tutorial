#pragma once

//We are linking statically with GLEW
#define GLEW_STATIC

// GLEW header
#include <GL/glew.h>

// Other library headers
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

// Project headers
#include "Renderer.h"
#include "Game.h"
#include "Util.h"

int main();