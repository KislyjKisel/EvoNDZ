#pragma once
#include <EvoNDZ/app/scene.h>
#include <EvoNDZ/input/input.h>
#include <EvoNDZ/util/timer.h>
#include <vector>
#include <memory>
#include <EvoNDZ/graphics/camera2d.h>
#include <EvoNDZ/graphics/simple2d/renderer.h>
#include <EvoNDZ/math/geometry.h>

using namespace evo::math;

namespace evo
{
	class TestScene final : public evo::Scene {
	public:
		void initialize() override { 
			m_renderer = std::make_unique<evo::s2d::Renderer>(); 
			m_camera.set_aspect_ratio(app::aspect_ratio());

			input::InputMap::Current = &m_inputMap;
		}
		void update() override { }
		void gui() override { }
		void terminate() override { }
		void render() override {
			static evo::Timer timer;
			static float lt = 0.f; 
			Vector2f mp = m_camera.screen_to_world(input::mouse_position_normalized());
			float t = timer.time<float>();
			float dt = t - lt;
			
			float r = 0.3;
			Box2f rect1 = Box2f({0, 0}, { 0.2, 0.1 });

			Box2f rect2 = Box2f::Between(mp, mp + Vector2f{ 0.1f, 0.1f });

			m_renderer->rectangle(rect1.centroid(), rect1.size(), 0.f, Color3f{ 0., 0.f, 1.f }, 0.1);
			m_renderer->rectangle(rect2.centroid(), rect2.size(), 0.f, Color3f { 0.f, 1.f, 0.f }, 0.1);
			if (intersect(rect1, rect2)) {
				auto recti = intersection(rect1, rect2);
				m_renderer->rectangle(recti.centroid(), recti.size(), 0.f, Color3f { 1.f, 0.f, 0.f }, 0.f);
			}

			constexpr Segment2f ise { { 1.f, 1.f }, { 0.5f, 0.f } };
			constexpr Vector2f ro { -1, 0.8 };
			constexpr Ball2f lb { { -1, -0.3 }, 0.05f };
			
			auto rectc = rect1.enclose(Segment2f(ro, mp));
			m_renderer->rectangle(rectc.centroid(), rectc.size(), 0.f, Color4f { 1.f, 0.f, 0.f, 0.33f }, 0.2f);

			Ray2f la { ro, (mp - ro).normalized() };

			m_renderer->line(la.origin, mp, 0.01f, Color4f{ Color3f::White(), 0.3f }, 0.1f);
			m_renderer->circle(lb.center, lb.radius, Color4f{ 0.1, 0.4, 0.6, 0.7 }, 0.5f);
			
			auto mseg = Segment2f(ro, mp);
			auto lli = intersection(mseg, lb);
			auto ssi = intersection(ise, mseg);
			m_renderer->line(ise.a, ise.b, 0.004f, Color3f{ 0.6f, 0.3, 0.9 }, 0.5);
			if (ssi.has_value()) m_renderer->circle( ssi.value(), 0.01f, Color3f{ 0.f, 1.f, 1.f });

			for (size_t i = 0; i < lli.size(); ++i) {
				m_renderer->circle(lli[i], 0.009f, Color3f { 1.f, 1.f, 0.f }, 0.0);
			}

			m_renderer->render(m_camera);
		}

	private:
		std::unique_ptr<evo::s2d::Renderer> m_renderer;
		Camera2D<float> m_camera;
		input::InputMap m_inputMap;
	};
}