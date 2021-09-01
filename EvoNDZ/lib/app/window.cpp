#include "../../include/EvoNDZ/app/window.h"
#include <GLFW/glfw3.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "../../include/EvoNDZ/app/glfw_exception.h"

namespace evo
{
	namespace detail
	{
		template<typename Setter>
		void glfwWindowSetHintsAttribs(Setter setter, BooleanFlags<WindowFlags> wf) {
			auto sh = [wf, &setter](const WindowFlags f, int attr) {
				auto fs = wf.at(f); if (fs) setter(attr, fs.value() ? GLFW_TRUE : GLFW_FALSE);
			};

			sh(WindowFlags::MousePassthrough	(),	GLFW_MOUSE_PASSTHROUGH			);
			sh(WindowFlags::Maximized		(),	GLFW_MAXIMIZED					);
			sh(WindowFlags::Floating			(),	GLFW_FLOATING					);
			sh(WindowFlags::Resizable		(),	GLFW_RESIZABLE					);
			sh(WindowFlags::Transparent		(),	GLFW_TRANSPARENT_FRAMEBUFFER		);
			sh(WindowFlags::Decorated		(),	GLFW_DECORATED					);
			sh(WindowFlags::Visible			(),	GLFW_VISIBLE						);
		}
	}

	Window::Window(int width, int height, const char* title, BooleanFlags<WindowFlags> hints) {
		// Hints must be specified before window creation 
		/*if (hints & WindowFlags::MousePassthrough	()) glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
		if (hints & WindowFlags::Maximized			()) glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
		if (hints & WindowFlags::Floating			()) glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
		if (hints & WindowFlags::Resizable			()) glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);*/
		
		detail::glfwWindowSetHintsAttribs(glfwWindowHint, hints);

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		
		if (m_window == nullptr) {
			throw GlfwException("GLFW Window creation failed.");
		}
	}

	Window::~Window() {
		if (m_window != nullptr)
			glfwDestroyWindow(m_window);
	}

	void Window::initialize_imgui() {
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void Window::framebuffer_size(int& width, int& height) {
		glfwGetFramebufferSize(m_window, &width, &height);
	}

	void Window::swap_buffers() {
		glfwSwapBuffers(m_window);
	}

	void Window::make_context_current() {
		glfwMakeContextCurrent(m_window);
	}

	void Window::close() {
		glfwSetWindowShouldClose(m_window, true);
	}

	bool Window::closing() {
		return glfwWindowShouldClose(m_window);
	}

	void Window::set_size(int width, int height) {
		glfwSetWindowSize(m_window, width, height);
	}

	void Window::set_title(const char* title) {
		glfwSetWindowTitle(m_window, title);
	}

	void Window::set_key_callback(void (*f)( GLFWwindow*, int, int, int, int )) {
		glfwSetKeyCallback(m_window, f);
	}

	void Window::set_mouse_callback(void (*f)( GLFWwindow*, int, int, int )) {
		glfwSetMouseButtonCallback(m_window, f);
	}

	void Window::set_scroll_callback(void (*f)( GLFWwindow*, double, double )) {
		glfwSetScrollCallback(m_window, f);
	}

	void Window::set_input_mode(int mode, int value) {
		glfwSetInputMode(m_window, mode, value);
	}

	void Window::cursor_position(double& x, double& y) {
		glfwGetCursorPos(m_window, &x, &y);
	}

	void Window::size(int& w, int& h) {
		glfwGetWindowSize(m_window, &w, &h);
	}

	void Window::set_flags(BooleanFlags<WindowFlags> wf) {
		detail::glfwWindowSetHintsAttribs([this](int k, int v) { glfwSetWindowAttrib(m_window, k, v); }, wf);
	}
}