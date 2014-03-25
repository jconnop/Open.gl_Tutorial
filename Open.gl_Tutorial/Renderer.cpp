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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

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

	GLuint ebo;
	glGenBuffers(1, &ebo);
	this->ebos["firstEBO"] = ebo;

	float vertices[] = {
		-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Top left (X, Y, r, g, b)
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Top right (X, Y, r, g, b)
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom right (X, Y, r, g, b)
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom left (X, Y, r, g, b)
	};
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint elements[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);



	// Combine shaders into a program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, this->vertex_shaders["basicVertex"]);
	glAttachShader(shaderProgram, this->fragment_shaders["basicFragment"]);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Link vertex attribute or some such?
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

	GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));


	return true;
}

bool Renderer::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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