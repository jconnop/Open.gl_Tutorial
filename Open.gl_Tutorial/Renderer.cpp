#include "main.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	this->window = 0;
	glfwTerminate();
}

GLFWwindow * Renderer::InitWindow(int glMajor, int glMinor, bool fullscreen, int x, int y, std::string title)
{
	// Init GLFW Library
	glfwInit();

	// Set up window options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create Window object
	GLFWwindow* window = 0;
	if (fullscreen)
	{
		window = glfwCreateWindow(x, y, title.c_str(), glfwGetPrimaryMonitor(), nullptr); // Fullscreen
	}
	else
	{
		window = glfwCreateWindow(x, y, title.c_str(), nullptr, nullptr); // Windowed
	}

	// Activate window
	glfwMakeContextCurrent(window);

	// Init GLEW library
	glewExperimental = GL_TRUE;
	glewInit();

	this->window = window;
	return window;
}

GLFWwindow *Renderer::getWindow()
{
	return this->window;
}

bool Renderer::LoadShaders()
{
	// Load vertex shader. Revise to scale
	GLuint vertexShader;
	if (!this->loadAndCompileShader("Shaders/Vertex/basicVertex.glsl", GL_VERTEX_SHADER, &vertexShader))
	{
		std::cout << "ERROR: Failed to load and compile basicVertex.glsl" << std::endl;
		return false;
	}
	this->vertex_shaders["basicVertex"] = vertexShader;

	// Load fragment shader. Revise to scale
	GLuint fragmentShader;
	if (!this->loadAndCompileShader("Shaders/Fragment/basicFragment.glsl", GL_FRAGMENT_SHADER, &fragmentShader))
	{
		std::cout << "ERROR: Failed to load and compile basicFragment.glsl" << std::endl;
		return false;
	}
	this->fragment_shaders["basicFragment"] = fragmentShader;


	return true;
}

bool Renderer::LoadScene()
{

	return true;
}

bool Renderer::RenderScene()
{
	return true;
}

bool Renderer::loadAndCompileShader(const std::string relativePath, const GLenum type, GLuint *shader)
{
	// Load file
	std::string file = Util::readTextFile(relativePath);
	if (!file.compare(std::string(""))){
		std::cerr << "ERROR: Failed to load " << relativePath << " into string" << std::endl;
		return false;
	}
	const char * fileContents = file.c_str();

	// Compile shader
	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, &fileContents, NULL);
	glCompileShader(*shader);

	// TODO: Check for errors
	return true;
}