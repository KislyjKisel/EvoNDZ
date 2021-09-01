#pragma once
#include <type_traits>
#include "../util/enum.h"

struct GLFWwindow;

namespace evo
{
	struct WindowFlags : Flags<WindowFlags> {
		EVO_FLAGS(WindowFlags);
		EVO_FLAGS_E(MousePassthrough,	0);
		EVO_FLAGS_E(Maximized,			1);
		EVO_FLAGS_E(Floating,			2);
		EVO_FLAGS_E(Resizable,			3);
		EVO_FLAGS_E(Transparent,			4);
		EVO_FLAGS_E(Decorated,			5);
		EVO_FLAGS_E(Visible,				6);
	};

	class Window {
	public:
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(int width, int height, const char* title, BooleanFlags<WindowFlags> hints = WindowFlags::None().with(false));
		~Window();

		Window(Window&& w) noexcept : m_window(w.m_window) {
			w.m_window = nullptr;
		}

		void initialize_imgui();
		void framebuffer_size(int& width, int& height);
		void swap_buffers();
		void make_context_current();
		void close();
		bool closing();
		void set_size(int width, int height);
		void set_title(const char* title);
		void set_key_callback(void (*)(GLFWwindow*, int, int, int, int));
		void set_mouse_callback(void (*)(GLFWwindow*, int, int, int));
		void set_scroll_callback(void (*)(GLFWwindow*, double, double));
		void set_input_mode(int mode, int value);
		void cursor_position(double& x, double& y);
		void size(int& width, int& height);
		void set_flags(BooleanFlags<WindowFlags>);

	private:
		GLFWwindow* m_window;
	};
}