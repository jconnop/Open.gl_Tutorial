/**
Renderer is a class that wraps all the OpenGL functionality
*/

#include "main.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	GLFWwindow * InitWindow(int glMajor, int glMinor, bool fullscreen, int x, int y, std::string title);
	GLFWwindow *getWindow();
	bool LoadScene();
	bool RenderScene();
private:

protected:
	GLFWwindow *window;
};