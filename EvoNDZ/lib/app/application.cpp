#include "../../include/EvoNDZ/app/application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <fstream>
#include "../../include/EvoNDZ/graphics/opengl/state.h"
#include "../../include/EvoNDZ/app/window.h"
#include "../../include/EvoNDZ/app/scene.h"
#include "../../include/EvoNDZ/app/glfw_exception.h"
#include "../../include/EvoNDZ/app/glad_exception.h"
#include "../../include/EvoNDZ/app/network_exception.h"
#include "../../include/EvoNDZ/input/input.h"


namespace evo::app
{
	std::unique_ptr<Window> window;
	std::unique_ptr<evo::Scene> scene;
	std::unique_ptr<ogl::State> gl_state;
	double window_width, window_height;

#ifndef EVO_DISABLE_LOGGING
	std::ofstream logger_stream;
	evo::dbg::Logger logger = evo::dbg::Logger(logger_stream);
#endif

	void initialize(int width, int height, const char* title, BooleanFlags<WindowFlags> flags) {
		//init glfw
		if (glfwInit() == GL_FALSE) {
			throw GlfwException("GLFW Initialization Failed.");
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//create window
		window = std::make_unique<Window>(width, height, title, flags);
		window->make_context_current();
		window_width = width;
		window_height = height;

		//glad load
		if (!gladLoadGL()) {
			throw GladException("Glad failed GL loading.");
		}

		//setup viewport
		glViewport(0, 0, width, height);

		gl_state = std::make_unique<ogl::State>();

		//set input callbacks
		window->set_key_callback(input::keyboard_callback);
		window->set_mouse_callback(input::mouse_button_callback);
		window->set_scroll_callback(input::mouse_scroll_callback);

		//setup imgui
		ImGui::CreateContext();
		window->initialize_imgui();
		ImGui::StyleColorsDark();
		ImGui::GetIO().IniFilename = nullptr;

		//open logger stream
#ifndef EVO_DISABLE_LOGGING
		logger_stream.open("log.txt");
#endif
	}

	void run_loop() {
		while (!window->closing()) {
			glfwPollEvents();
			input::update_joystick_input();


			if (scene) {
				scene->update();
				scene->render();
			}

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			if (scene) scene->gui();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			window->swap_buffers();
		}
	}

	void terminate() {
		if(scene) scene->terminate();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		gl_state.reset();

		window.reset();
		glfwTerminate();

#ifndef EVO_DISABLE_LOGGING
		logger_stream.close();
#endif
	}

	void set_scene(std::unique_ptr<evo::Scene>&& s) {
		if (scene) {
			scene->terminate();
		}
		scene = std::move(s);
		scene->initialize();
	}

	void run(int windowWidth, int windowHeight, const char* title, BooleanFlags<WindowFlags> flags, std::unique_ptr<evo::Scene>&& s) {
		initialize(windowWidth, windowHeight, title, flags);
		set_scene(std::move(s));
		run_loop();
		terminate();
	}

	void exit() {
		window->close();
	}

	void set_window_flags(BooleanFlags<WindowFlags> f) {
		window->set_flags(f);
	}


	ogl::State* gl() {
		return gl_state.get();
	}


	void set_window_size(int width, int height) {
		window->set_size(width, height);
		window_width = width;
		window_height = height;
	}
	void set_window_title(const char* title) {
		window->set_title(title);
	}

	void window_size(int& width, int& height) {
		window->size(width, height);
	}

	void window_size(double& w, double& h) {
		w = window_width;
		h = window_height;
	}

	double aspect_ratio() {
		return window_width / window_height;
	}
}

namespace evo::input
{
	void lock_cursor() {
		app::window->set_input_mode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void unlock_cursor() {
		app::window->set_input_mode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void mouse_position(double& x, double& y) {
		app::window->cursor_position(x, y);
	}

	Vector2d mouse_position_normalized() {
		Vector2d mp;
		app::window->cursor_position(mp.x, mp.y);
		return (mp / Vector2<double>(app::window_width, app::window_height) * 2.0 - 1.0).inversed_y();
	}
}