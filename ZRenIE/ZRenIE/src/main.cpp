#include "Utility/Shader.hpp"
#include "Utility/FlyCamera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>

#include <iostream>

void error_callback(int error, const char* descr);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
void scrollCallback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);

unsigned int loadTexture(char const* path, bool gammaCorrection);

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// Camera vars
FlyCamera camera(glm::vec3(0.f, 0.f, 3.f));
bool firstMouse = true;
float lastX = WINDOW_WIDTH / 2.f, lastY = WINDOW_HEIGHT / 2.f;

int main()
{

#pragma region GLFW_Setup

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", NULL, NULL);
	if (!window)
	{
		std::cout << "Error: Window creation failed. Terminating program.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#pragma endregion

#pragma region GLAD_Setup

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Failed to initialize GLAD. Terminating program.\n";
		glfwTerminate();
		return -1;
	}

#pragma endregion

#pragma region DATA_Setup

	// TODO: Figure out a way to generalize the file path
	Shader shader = Shader("src/Shaders/cameraVS.glsl", "src/Shaders/cameraFS.glsl");
	shader.use();

	unsigned int textureID = loadTexture("Assets/Images/brickwall.jpg", false);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	shader.setInt("u_Texture", 0);

	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::rotate(matrix, glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f));
	matrix = glm::scale(matrix, glm::vec3(1.5f, 1.5f, 1.5f));
	shader.setMatrix4("u_Matrix", matrix);

	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#pragma endregion

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

#pragma region APPLICATION_LOOP

	glm::mat4 model = glm::mat4(1.f);
	shader.setMatrix4("u_ModelMat", model);

	while (!glfwWindowShouldClose(window))
	{
		// 1st: Process any Inputs
		
		// Keep track of time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 view = camera.GetViewMatrix();
		shader.setMatrix4("u_ViewMat", view);
		
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), screenWidth / (float)screenHeight, .1f, 100.f);
		shader.setMatrix4("u_ProjMat", projection);


		// 2nd: Do the Rendering

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		// 3rd: Poll for Events
		glfwPollEvents();
	}

#pragma region
	
	glfwDestroyWindow(window);
	window = nullptr;
	glfwTerminate();

	return 0;
}

void error_callback(int error, const char* descr)
{
	std::cout << "Error: " << descr << "\n";
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xpos, double ypos)
{
	camera.ProcessMouseScroll(static_cast<float>(ypos));
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.ProcessKeyboard(FlyCamera_Movement::MOVE_FAST, deltaTime);
	else
		camera.ProcessKeyboard(FlyCamera_Movement::SLOW_DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FlyCamera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(FlyCamera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(FlyCamera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(FlyCamera_Movement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(FlyCamera_Movement::UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(FlyCamera_Movement::DOWN, deltaTime);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path, bool gammaCorrection)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum internalFormat = NULL;
		GLenum dataFormat = NULL;
		if (nrComponents == 1)
		{
			internalFormat = dataFormat = GL_RED;
		}
		else if (nrComponents == 3)
		{
			internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
			dataFormat = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
			dataFormat = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}