#include "Utility/Shader.hpp"
#include "Utility/FlyCamera.hpp"
#include "Utility/Model.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

enum EditState
{
	Editor,
	Game
};
EditState editState;

void error_callback(int error, const char* descr);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xpos, double ypos);

void processInput(GLFWwindow* window);

unsigned int loadTexture(char const* path, bool gammaCorrection);

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;

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

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// TODO: Figure out a way to generalize the file path
	Shader shader = Shader("src/Shaders/modelVS.glsl", "src/Shaders/modelFS.glsl");
	
	Model backpack = Model("Assets/Models/Backpack/backpack.obj");

#pragma endregion

	// Lock the mouse in camera control mode by default
	editState = EditState::Game;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);

	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

#pragma region APPLICATION_LOOP

	glm::mat4 model = glm::mat4(1.0f);
	shader.setMatrix4("model", model);

	while (!glfwWindowShouldClose(window))
	{
		// 1st: Process any Inputs
		
		// Keep track of time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		

		// Window setup code here...

		// Assuming you have these variables for your 3D object's transform
		static float position[3] = { 0.0f, 0.0f, 0.0f };
		static float rotation[3] = { 0.0f, 0.0f, 0.0f }; // Euler angles in degrees
		static float scale[3] = { 1.0f, 1.0f, 1.0f };

		bool changed = false;
		// Create a window for the transform component
		ImGui::Begin("Transform");

		// Style settings for better appearance
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);

		// Position
		ImGui::Text("Position");
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
		changed |= ImGui::DragFloat3("##position", position, 0.1f);
		ImGui::PopItemWidth();
		ImGui::NextColumn();

		// Rotation
		ImGui::Text("Rotation");
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
		changed |= ImGui::DragFloat3("##rotation", rotation, 0.5f);
		ImGui::PopItemWidth();
		ImGui::NextColumn();

		// Scale
		ImGui::Text("Scale");
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
		changed |= ImGui::DragFloat3("##scale", scale, 0.01f);
		ImGui::PopItemWidth();
		ImGui::NextColumn();

		ImGui::Columns(1);
		ImGui::PopStyleVar();

		ImGui::End();


		shader.use();

		if (changed)
		{
			model = glm::mat4(1.f);

			model = glm::translate(model, glm::vec3(position[0], position[1], position[2]));

			glm::mat4 rotationMat =
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f)) * // yaw
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)) * // pitch
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // row
			model = model * rotationMat;

			model = glm::scale(model, glm::vec3(scale[0], scale[1], scale[2]));

			shader.setMatrix4("model", model);
		}

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMatrix4("projection", projection);
		shader.setMatrix4("view", view);


		// 2nd: Do the Rendering

		backpack.Draw(shader);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

		// 3rd: Poll for Events
		glfwPollEvents();
	}

#pragma region
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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
	if (editState != EditState::Editor)
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
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse)
	{
		// Release mouse from locked position:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		editState = EditState::Game;
	}
}

void scrollCallback(GLFWwindow* window, double xpos, double ypos)
{
	camera.ProcessMouseScroll(static_cast<float>(ypos));
}

void processInput(GLFWwindow* window)
{
	static int prevEscapeState = GLFW_RELEASE;
	int currEscapeState = glfwGetKey(window, GLFW_KEY_ESCAPE);

	if (currEscapeState == GLFW_PRESS && editState == EditState::Game)
	{
		// Release mouse from locked position:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (prevEscapeState == GLFW_PRESS && currEscapeState == GLFW_RELEASE && editState == EditState::Game)
	{
		editState = EditState::Editor;
	}
	else if (currEscapeState == GLFW_PRESS && editState == EditState::Editor)
	{
		glfwSetWindowShouldClose(window, true);
	}

	prevEscapeState = currEscapeState;


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