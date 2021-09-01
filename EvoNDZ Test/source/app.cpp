#include <memory>
#include <imgui/imgui.h>
#include <EvoNDZ/app/application.h>
#include <EvoNDZ/app/scene.h>
#include <EvoNDZ/app/window.h>

class TestScene : public evo::Scene 
{
public:
	void initialize() override { }
	void render() override { }
	void update() override { }
	void terminate() override { }
	
	void gui() override {
		ImGui::Begin("Window 1");
		ImGui::Text("Hello, world!");
		ImGui::End();
	}
};

int main() {
	evo::app::run(800, 600, "EvoNDZ Test", evo::WindowFlags::None(), std::make_unique<TestScene>());

	return 0;
}