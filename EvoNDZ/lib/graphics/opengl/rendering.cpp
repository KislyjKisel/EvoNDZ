#include "../../../include/EvoNDZ/graphics/opengl/rendering.h"
#include <glad/glad.h>
#include <functional>
#include "../../../include/EvoNDZ/graphics/opengl/vertex_buffer.h"
#include "../../../include/EvoNDZ/graphics/opengl/technique.h"
#include "../../../include/EvoNDZ/graphics/opengl/state.h"
#include "../../../include/EvoNDZ/math/vector2.h"

namespace evo::ogl::rendering {
	evo::ogl::RenderTarget* MainRenderTarget;

	evo::ogl::VertexBuffer* screenQuad;
	evo::ogl::Technique* screenTechnique;

	void Initialize(RenderTarget* renderTarget) {
		MainRenderTarget = renderTarget;

		evo::ogl::Technique::Builder tchb = evo::ogl::Technique::Builder();
		const char* r = tchb.attachShader(R"(
		#version 460 core

		layout(location = 0) in vec2 vPosition;

		const vec2 cHalf = vec2(0.5, 0.5);

		out vec2 fTexCoords;

		void main() {
			fTexCoords = vPosition * cHalf + cHalf;
			gl_Position = vec4(vPosition, 0.0, 1.0);
		}
		)", evo::ogl::Technique::Builder::VertexShader);
		r = tchb.attachShader(R"(
		#version 460 core

		uniform sampler2D uScreenTexture;	

		in vec2 fTexCoords;

		out vec4 FragColor;

		void main() {
			FragColor = texture(uScreenTexture, fTexCoords);
		}
		)", evo::ogl::Technique::Builder::FragmentShader);
		screenTechnique = new evo::ogl::Technique(tchb.link());
		screenQuad = new VertexBuffer();
		screenQuad->data(new Vector2[8]{
			Vector2(-1, -1),
			Vector2(-1, 1),
			Vector2(1, -1),
			Vector2(1, 1)
		}, 4 * sizeof(Vector2), GL_STATIC_DRAW);
	}

	void BeginDraw() {
		state::BindRenderTarget(MainRenderTarget);
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void BeginDraw(Color backgroundColor) {
		state::BindRenderTarget(MainRenderTarget);
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void EndDraw() {
		state::RebindRenderTarget(nullptr);
		state::Disable(state::Capability::DepthTest);
		state::Disable(state::Capability::StencilTest);
		state::BindTechnique(*screenTechnique);
		state::BindVertexBuffer(*screenQuad);

		// todo: use vao
		// todo: use postprocessed texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, MainRenderTarget->getColorTexture());
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);
		glUniform1i(screenTechnique->getUniformLocation("uScreenTexture"), 0); // ugly
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		state::RevertVertexBuffer();
		state::RevertTechnique();
		state::RevertRenderTarget();
		state::Revert(state::Capability::StencilTest);
		state::Revert(state::Capability::DepthTest);
	}
}