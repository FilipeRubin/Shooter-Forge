#pragma once
#include "Scene/SceneBase.hpp"

// Core.hpp
// 
// Purpose: The class responsible for initializing the engine, its dependencies and other classes.
// 
// Obs1: Friend functions suffixed by "Wrapper" alongside static functions with similar name are "bridges" from GLFW callbacks to the engine's code flow.
//

namespace Engine
{
	class Core
	{
	public:
		struct Parameters
		{
			const char* applicationName = "Game"; // The title of the game's window.
			int windowWidth = 800; // The width of the game's window, in pixels.
			int windowHeight = 600; // The height of the game's window, in pixels.
			bool vsync = true; // If true, it'll lock the max framerate to the screen's refresh rate.
			size_t defaultArraySize = 10U; // Default size for rendering arrays. Arrays get automatically resized if needed, at a performance cost.
		};
	private:
		Core() = delete;
		Core(const Core&) = delete;
		Core(Core&&) = delete;
		// "Bridge" functions from GLFW callbacks to Engine::Core
		friend void WindowSizeWrapper (int width , int  height );
		friend void KeyPressedWrapper (int key   , bool pressed);
		friend void MouseButtonWrapper(int button, bool pressed);
		static void WindowSize        (int width , int  height );
		static void KeyPressed        (int key   , bool pressed);
		static void MouseButton       (int button, bool pressed);
	public:
		static bool Init(Parameters params = Parameters());
		static void Start(Scene::SceneBase*&& pFirstScene);
	};
}