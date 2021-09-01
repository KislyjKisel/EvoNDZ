#include "../../include/EvoNDZ/input/input.h"
#include <algorithm>
#include <GLFW/glfw3.h>

namespace evo::input
{
	Key MouseKey(int glfwMouseButton) noexcept {
		return (Key)((glfwMouseButton + 1u) << 24u);
	}
	Key JoystickKey(int index) noexcept {
		return (Key)((index + 1) << 16u);
	}

	void InputMap::add_key_event(EventID id) {
		size_t index = m_keyEvents.size();
		m_keyEvents.emplace_back();
		m_idEventMap.insert({ id, index });
	}

	void InputMap::remove_key_event(EventID id) {
		auto it = m_idEventMap.find(id);
		if (it == m_idEventMap.end()) return;
		std::erase_if(m_keyEventMap, [&it](const std::pair<KeyStatePair, size_t>& p) {
			return p.second == it->second;
		});
		m_keyEvents.erase(m_keyEvents.begin() + it->second);
		m_idEventMap.erase(it);
	}

	EventInterface<> InputMap::key_event(EventID id) {
		return m_keyEvents[m_idEventMap.at(id)];
	}

	void InputMap::on_scroll(double x, double y) {
		m_scrollEvent(x, y);
	}
	
	void InputMap::on_key(Key key, bool pressed) {
		if(pressed) m_anyKeyEvent(key);

		KeyStatePair ks { key, pressed };
		auto it = m_keyEventMap.find(ks);
		if (it == m_keyEventMap.end()) [[unlikely]] return;
		m_keyEvents[it->second]();
	}

	void InputMap::bind(EventID id, Key key, bool pressed) {
		size_t index = m_idEventMap.at(id);
		KeyStatePair ks { key, pressed };
		auto it = m_keyEventMap.find(ks);
		if (it == m_keyEventMap.end()) {
			m_keyEventMap.insert({ ks, index });
		}
		else {
			it->second = index;
		}
	}

	void InputMap::simple_key(EventID id, evo::input::Key key, bool press, std::function<void()> f) {
		add_key_event(id);
		key_event(id) += f;
		bind(id, key, press);
	}

	void InputMap::simple_switch(EventID idY, EventID idN, evo::input::Key key, std::function<void()> y, std::function<void()> n) {
		add_key_event(idY);
		key_event(idY) += y;
		bind(idY, key, true);
		add_key_event(idN);
		key_event(idN) += n;
		bind(idN, key, false);
	}

	void InputMap::unbind(EventID id) {
		auto it = m_idEventMap.find(id);
		if (it == m_idEventMap.end()) return;
		std::erase_if(m_keyEventMap, [&it](const std::pair<KeyStatePair, size_t>& p) {
			return p.second == it->second;
		});
	}

	void keyboard_callback(GLFWwindow*, int key, int, int action, int) {
		if (InputMap::Current && action != GLFW_REPEAT) InputMap::Current->on_key((Key)key, action == GLFW_PRESS);
	}
	void mouse_button_callback(GLFWwindow*, int btn, int act, int) {
		if (InputMap::Current) [[likely]] InputMap::Current->on_key(MouseKey(btn), act == GLFW_PRESS);
	}
	void mouse_scroll_callback(GLFWwindow*, double x, double y) {
		if (InputMap::Current) [[likely]] InputMap::Current->on_scroll(x, y);
	}

	std::vector<unsigned char> joystick_buttons;
	std::vector<float> joystick_axes;

	void update_joystick_input() {
		if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
			int size;
			const unsigned char* btns = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &size);

			if (size != joystick_buttons.size()) [[unlikely]] {
				joystick_buttons.resize(size);
				std::copy(btns, btns + size, joystick_buttons.data());
			}
			else [[likely]] {
				if (!InputMap::Current) [[unlikely]] return;
				for (int i = 0; i < size; ++i) {
					if (joystick_buttons[i] != btns[i]) {
						InputMap::Current->on_key(JoystickKey(i), btns[i] == GLFW_PRESS);
						joystick_buttons[i] = btns[i];
					}
				}
			}

			const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &size);
			if (size != joystick_axes.size()) [[unlikely]] {
				joystick_axes.resize(size);
			}
			std::copy(axes, axes + size, joystick_axes.data());
		}
		else {
			joystick_buttons.clear();
			joystick_axes.clear();
		}
	}

	std::span<const float> get_joystick_axes() noexcept {
		return joystick_axes;
	}
}