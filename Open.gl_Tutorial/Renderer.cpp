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
	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	this->vaos["firstVAO"] = vao;
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);
	this->vbos["firstVBO"] = vbo;


	float vertices[] = {
		0.0f, 0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Combine shaders into a program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, this->vertex_shaders["basicVertex"]);
	glAttachShader(shaderProgram, this->fragment_shaders["basicFragment"]);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Link vertex attribute or some such?
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	return true;
}

bool Renderer::RenderScene()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);

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