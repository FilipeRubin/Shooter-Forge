#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core.hpp"
#include "Scene/SceneManagement.hpp"
#include "Gameplay/PlayerBase.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Renderer.hpp"
//#include "Graphics/Sprite.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"
#include "Utilities/Time.hpp"
#include <iostream>

//#define BENCHMARK_TESTS
#ifdef BENCHMARK_TESTS
#include <chrono>
#include <Windows.h>
#endif

static GLFWwindow* s_pWindow = nullptr;

static Engine::Utilities::Vector2 s_mousePos = Engine::Utilities::Vector2();

void Engine::WindowSizeWrapper(int width, int height)
{
	Core::WindowSize(width, height);
}

void Engine::KeyPressedWrapper(int key, bool pressed)
{
	Core::KeyPressed(key, pressed);
}

void Engine::MouseButtonWrapper(int button, bool pressed)
{
	Core::MouseButton(button, pressed);
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Engine::WindowSizeWrapper(width, height);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Engine::KeyPressedWrapper(key, action != GLFW_RELEASE);
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	s_mousePos.x = (float)xpos;
	s_mousePos.y = (float)ypos;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Engine::MouseButtonWrapper(button, action != GLFW_RELEASE);
}

void Engine::Core::WindowSize(int width, int height)
{
	float fWidth = (float)width;
	float fHeight = (float)height;

	Graphics::Renderer::windowSize.x = fWidth;
	Graphics::Renderer::windowSize.y = fHeight;
	Graphics::Camera::pCurrentCamera->aspect = fWidth / fHeight;
}

void Engine::Core::KeyPressed(int key, bool pressed)
{
	Input::Keyboard::UpdateKeyState(key, pressed);
}

void Engine::Core::MouseButton(int button, bool pressed)
{
	Input::Mouse::UpdateButtonState(button, pressed);
}

bool Engine::Core::Init(Parameters params)
{
	if (!glfwInit())
		return false;
	s_pWindow = glfwCreateWindow(params.windowWidth, params.windowHeight, params.applicationName, nullptr, nullptr);

	if (s_pWindow == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(s_pWindow);
	glfwSetWindowSizeCallback(s_pWindow, window_size_callback);
	glfwSetKeyCallback(s_pWindow, key_callback);
	glfwSetCursorPosCallback(s_pWindow, cursor_pos_callback);
	glfwSetMouseButtonCallback(s_pWindow, mouse_button_callback);
	glfwSwapInterval(params.vsync ? 1 : 0);

	if (!gladLoadGL())
	{
		glfwTerminate();
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Initialize stuff here
	Graphics::Renderer::windowSize.x = (float)params.windowWidth;
	Graphics::Renderer::windowSize.y = (float)params.windowHeight;
	Graphics::Renderer::Init(params.defaultArraySize);
	Input::Keyboard::Init();
	Input::Mouse::Init(Utilities::Vector2((float)params.windowWidth / 2.0f, (float)params.windowHeight / 2.0f));

	return true;
}

void Engine::Core::Start(Scene::SceneBase*&& pFirstScene)
{
	Scene::SceneManagement::SetScene((Scene::SceneBase*&&)pFirstScene);

#ifdef BENCHMARK_TESTS
	std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
	unsigned int frameCount = 0U;
#endif

	while (!glfwWindowShouldClose(s_pWindow))
	{
		// If mouse should be locked in the center of the screen
		if (Input::Mouse::GetLockMouse())
		{
			glfwSetInputMode(s_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(s_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		Utilities::Time::UpdateDeltaTime((float)glfwGetTime());

		Input::Mouse::SetPos(s_mousePos);

		if (Scene::SceneManagement::HasNextScene())
			Scene::SceneManagement::LoadNextScene();
		Scene::SceneManagement::Render();
		
		Graphics::Renderer::RenderAll();

		Input::Keyboard::Process();
		Input::Mouse::Process();

		glfwSwapBuffers(s_pWindow);
		glfwPollEvents();
#ifdef BENCHMARK_TESTS
		frameCount++;
		if (frameCount == 10000U)
			break;
#endif
	}

#ifdef BENCHMARK_TESTS
	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::wstring frameCountStr = (std::wstringstream() << duration.count()).str();
	MessageBox(NULL, frameCountStr.c_str(), L"10000 frames rendered", MB_OK);
#endif

	// Cleanup
	Scene::SceneManagement::Cleanup();

	glfwDestroyWindow(s_pWindow);
	glfwTerminate();
}