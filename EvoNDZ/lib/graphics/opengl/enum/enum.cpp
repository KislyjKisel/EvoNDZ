#include <glad/glad.h>
#include "../../../../include/EvoNDZ/util/array.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/blend_factor.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/blend_equation.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/buffer_usage.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/capability.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/depth_function.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/logical_pixel_operation.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/shader_type.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/draw_mode.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/storage_flags.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/texture_format.h"
#include "../../../../include/EvoNDZ/graphics/opengl/enum/buffer_bit.h"

namespace evo::ogl
{
#pragma region BlendFactor
	BlendFactor BlendFactor::Zero()						noexcept { return GL_ZERO; }
	BlendFactor BlendFactor::One()						noexcept { return GL_ONE; }
	BlendFactor BlendFactor::SrcColor()					noexcept { return GL_SRC_COLOR; }
	BlendFactor BlendFactor::OneMinusSrcColor()			noexcept { return GL_ONE_MINUS_SRC_COLOR; }
	BlendFactor BlendFactor::DstColor()					noexcept { return GL_DST_COLOR; }
	BlendFactor BlendFactor::OneMinusDstColor()			noexcept { return GL_ONE_MINUS_DST_COLOR; }
	BlendFactor BlendFactor::SrcAlpha()					noexcept { return GL_SRC_ALPHA; }
	BlendFactor BlendFactor::OneMinusSrcAlpha()			noexcept { return GL_ONE_MINUS_SRC_ALPHA; }
	BlendFactor BlendFactor::DstAlpha()					noexcept { return GL_DST_ALPHA; }
	BlendFactor BlendFactor::OneMinusDstAlpha()			noexcept { return GL_ONE_MINUS_DST_ALPHA; }
	BlendFactor BlendFactor::ConstantColor()			noexcept { return GL_CONSTANT_COLOR; }
	BlendFactor BlendFactor::OneMinusConstantColor()	noexcept { return GL_ONE_MINUS_CONSTANT_COLOR; }
	BlendFactor BlendFactor::ConstantAlpha()			noexcept { return GL_CONSTANT_ALPHA; }
	BlendFactor BlendFactor::OneMinusConstantAlpha()	noexcept { return GL_ONE_MINUS_CONSTANT_ALPHA; }
	BlendFactor BlendFactor::SrcAlphaSaturate()			noexcept { return GL_SRC_ALPHA_SATURATE; }
	BlendFactor BlendFactor::Src1Color()				noexcept { return GL_SRC1_COLOR; }
	BlendFactor BlendFactor::OneMinusSrc1Color()		noexcept { return GL_ONE_MINUS_SRC1_COLOR; }
	BlendFactor BlendFactor::Src1Alpha()				noexcept { return GL_SRC1_ALPHA; }
	BlendFactor BlendFactor::OneMinusSrc1Alpha()		noexcept { return GL_ONE_MINUS_SRC1_ALPHA; }
#pragma endregion
#pragma region BlendEquation
	BlendEquation BlendEquation::Add()				noexcept { return GL_FUNC_ADD; }
	BlendEquation BlendEquation::Subtract()			noexcept { return GL_FUNC_SUBTRACT; }
	BlendEquation BlendEquation::ReverseSubtract()	noexcept { return GL_FUNC_REVERSE_SUBTRACT; }
	BlendEquation BlendEquation::Min()				noexcept { return GL_MIN; }
	BlendEquation BlendEquation::Max()				noexcept { return GL_MAX; }
#pragma endregion
#pragma region BufferUsage
	BufferUsage BufferUsage::DynamicDraw() { return GL_DYNAMIC_DRAW;	}
	BufferUsage BufferUsage::StaticDraw	() { return GL_STATIC_DRAW;		}
	BufferUsage BufferUsage::StreamDraw	() { return GL_STREAM_DRAW;		}
	BufferUsage BufferUsage::DynamicRead() { return GL_DYNAMIC_READ;	}
	BufferUsage BufferUsage::StaticRead	() { return GL_STATIC_READ;		}
	BufferUsage BufferUsage::StreamRead	() { return GL_STREAM_READ;		}
	BufferUsage BufferUsage::DynamicCopy() { return GL_DYNAMIC_COPY;	}
	BufferUsage BufferUsage::StaticCopy	() { return GL_STATIC_COPY;		}
	BufferUsage BufferUsage::StreamCopy	() { return GL_STREAM_COPY;		}
#pragma endregion
#pragma region Capability
	const std::array<Capability, 33>& Capability::Capabilities() { 
		static auto a = make_array<Capability, gl_enum_t>(
			[] (gl_enum_t v, size_t i) constexpr { return Capability(v, i); }, 
				GL_CLIP_DISTANCE0,
				GL_CLIP_DISTANCE1, 
				GL_CLIP_DISTANCE2, 
				GL_CLIP_DISTANCE3, 
				GL_CLIP_DISTANCE4, 
				GL_CLIP_DISTANCE5, 
				GL_CLIP_DISTANCE6, 
				GL_CLIP_DISTANCE7, 
				GL_COLOR_LOGIC_OP, 
				GL_CULL_FACE, 
				GL_DEBUG_OUTPUT,
				GL_DEBUG_OUTPUT_SYNCHRONOUS,
				GL_DEPTH_CLAMP,
				GL_DEPTH_TEST,
				GL_DITHER, 
				GL_FRAMEBUFFER_SRGB, 
				GL_LINE_SMOOTH, 
				GL_MULTISAMPLE, 
				GL_POLYGON_OFFSET_FILL, 
				GL_POLYGON_OFFSET_LINE, 
				GL_POLYGON_OFFSET_POINT, 
				GL_POLYGON_SMOOTH, 
				GL_PRIMITIVE_RESTART, 
				GL_PRIMITIVE_RESTART_FIXED_INDEX, 
				GL_RASTERIZER_DISCARD, 
				GL_SAMPLE_ALPHA_TO_COVERAGE, 
				GL_SAMPLE_ALPHA_TO_ONE, 
				GL_SAMPLE_COVERAGE, 
				GL_SAMPLE_SHADING, 
				GL_SAMPLE_MASK, 
				GL_STENCIL_TEST, 
				GL_TEXTURE_CUBE_MAP_SEAMLESS, 
				GL_PROGRAM_POINT_SIZE
			); 
		return a;
	}
#pragma endregion
#pragma region DepthFunction
	DepthFunction DepthFunction::Never()		noexcept { return GL_NEVER; }
	DepthFunction DepthFunction::Less()			noexcept { return GL_LESS; }
	DepthFunction DepthFunction::Equal()		noexcept { return GL_EQUAL; }
	DepthFunction DepthFunction::LessEqual()	noexcept { return GL_LEQUAL; }
	DepthFunction DepthFunction::Greater()		noexcept { return GL_GREATER; }
	DepthFunction DepthFunction::NotEqual()		noexcept { return GL_NOTEQUAL; }
	DepthFunction DepthFunction::GreaterEqual() noexcept { return GL_GEQUAL; }
	DepthFunction DepthFunction::Always()		noexcept { return GL_ALWAYS; }
#pragma endregion
#pragma region LogicalPixelOperation
	LogicalPixelOperation LogicalPixelOperation::Clear() noexcept { return GL_CLEAR; }
	LogicalPixelOperation LogicalPixelOperation::Set() noexcept { return GL_SET; }
	LogicalPixelOperation LogicalPixelOperation::Copy() noexcept { return GL_COPY; }
	LogicalPixelOperation LogicalPixelOperation::CopyInverted() noexcept { return GL_COPY_INVERTED; }
	LogicalPixelOperation LogicalPixelOperation::Noop() noexcept { return GL_NOOP; }
	LogicalPixelOperation LogicalPixelOperation::Invert() noexcept { return GL_INVERT; }
	LogicalPixelOperation LogicalPixelOperation::And() noexcept { return GL_AND; }
	LogicalPixelOperation LogicalPixelOperation::Nand() noexcept { return GL_NAND; }
	LogicalPixelOperation LogicalPixelOperation::Or() noexcept { return GL_OR; }
	LogicalPixelOperation LogicalPixelOperation::Nor() noexcept { return GL_NOR; }
	LogicalPixelOperation LogicalPixelOperation::Xor() noexcept { return GL_XOR; }
	LogicalPixelOperation LogicalPixelOperation::Equiv() noexcept { return GL_EQUIV; }
	LogicalPixelOperation LogicalPixelOperation::AndReverse() noexcept { return GL_AND_REVERSE; }
	LogicalPixelOperation LogicalPixelOperation::AndInverted() noexcept { return GL_AND_INVERTED; }
	LogicalPixelOperation LogicalPixelOperation::OrReverse() noexcept { return GL_OR_REVERSE; }
	LogicalPixelOperation LogicalPixelOperation::OrInverted() noexcept { return GL_OR_INVERTED; }
#pragma endregion
#pragma region ShaderType
	ShaderType ShaderType::Float()	{ return ShaderType(1, GL_FLOAT, 1 * sizeof(gl_float_t)); }
	ShaderType ShaderType::FVec2()	{ return ShaderType(2, GL_FLOAT, 2 * sizeof(gl_float_t)); }
	ShaderType ShaderType::FVec3()	{ return ShaderType(3, GL_FLOAT, 3 * sizeof(gl_float_t)); }
	ShaderType ShaderType::FVec4()	{ return ShaderType(4, GL_FLOAT, 4 * sizeof(gl_float_t)); }

	ShaderType ShaderType::Bool()	{ return ShaderType(1, GL_BOOL, 1 * sizeof(gl_boolean_t)); }
	ShaderType ShaderType::BVec2()	{ return ShaderType(2, GL_BOOL, 2 * sizeof(gl_boolean_t)); }
	ShaderType ShaderType::BVec3()	{ return ShaderType(3, GL_BOOL, 3 * sizeof(gl_boolean_t)); }
	ShaderType ShaderType::BVec4()	{ return ShaderType(4, GL_BOOL, 4 * sizeof(gl_boolean_t)); }

	ShaderType ShaderType::Int()		{ return ShaderType(1, GL_INT, 1 * sizeof(gl_int_t)); }
	ShaderType ShaderType::IVec2()	{ return ShaderType(2, GL_INT, 2 * sizeof(gl_int_t)); }
	ShaderType ShaderType::IVec3()	{ return ShaderType(3, GL_INT, 3 * sizeof(gl_int_t)); }
	ShaderType ShaderType::IVec4()	{ return ShaderType(4, GL_INT, 4 * sizeof(gl_int_t)); }

	ShaderType ShaderType::UInt()	{ return ShaderType(1, GL_UNSIGNED_INT, 1 * sizeof(gl_uint_t)); }
	ShaderType ShaderType::UVec2()	{ return ShaderType(2, GL_UNSIGNED_INT, 2 * sizeof(gl_uint_t)); }
	ShaderType ShaderType::UVec3()	{ return ShaderType(3, GL_UNSIGNED_INT, 3 * sizeof(gl_uint_t)); }
	ShaderType ShaderType::UVec4()	{ return ShaderType(4, GL_UNSIGNED_INT, 4 * sizeof(gl_uint_t)); }

	ShaderType ShaderType::Double() { return ShaderType(1, GL_DOUBLE, 1 * sizeof(gl_double_t)); }
	ShaderType ShaderType::DVec2()	{ return ShaderType(2, GL_DOUBLE, 2 * sizeof(gl_double_t)); }
	ShaderType ShaderType::DVec3()	{ return ShaderType(3, GL_DOUBLE, 3 * sizeof(gl_double_t)); }
	ShaderType ShaderType::DVec4()	{ return ShaderType(4, GL_DOUBLE, 4 * sizeof(gl_double_t)); }
#pragma endregion
#pragma region DrawMode
	DrawMode DrawMode::Points					() { return GL_POINTS;						}
	DrawMode DrawMode::LineStrip				() { return GL_LINE_STRIP;					}	
	DrawMode DrawMode::LineLoop					() { return GL_LINE_LOOP;					}
	DrawMode DrawMode::Lines					() { return GL_LINES;						}
	DrawMode DrawMode::LineStripAdjacency		() { return GL_LINE_STRIP_ADJACENCY;		}
	DrawMode DrawMode::LinesAdjacency			() { return GL_LINES_ADJACENCY;				}
	DrawMode DrawMode::TriangleStrip			() { return GL_TRIANGLE_STRIP;				}
	DrawMode DrawMode::TriangleFan				() { return GL_TRIANGLE_FAN;				}
	DrawMode DrawMode::Triangles				() { return GL_TRIANGLES;					}
	DrawMode DrawMode::TriangleStripAdjacency	() { return GL_TRIANGLE_STRIP_ADJACENCY;	}
	DrawMode DrawMode::TrianglesAdjacency		() { return GL_TRIANGLES_ADJACENCY;			}
	DrawMode DrawMode::Patches					() { return GL_PATCHES;						}
#pragma endregion
#pragma region StorageFlags
	StorageFlags StorageFlags::DynamicStorageBit	() { return StorageFlags(GL_DYNAMIC_STORAGE_BIT	); }
	StorageFlags StorageFlags::MapPersistentBit		() { return StorageFlags(GL_MAP_PERSISTENT_BIT	); }
	StorageFlags StorageFlags::MapCoherentBit		() { return StorageFlags(GL_MAP_COHERENT_BIT	); }
	StorageFlags StorageFlags::MapWriteBit			() { return StorageFlags(GL_MAP_WRITE_BIT		); }
	StorageFlags StorageFlags::MapReadBit			() { return StorageFlags(GL_MAP_READ_BIT		); }
	StorageFlags StorageFlags::ClientStorageBit		() { return StorageFlags(GL_CLIENT_STORAGE_BIT	); }
#pragma endregion
#pragma region TextureFormat
	TextureFormat TextureFormat::RGBA2() { return { GL_RGBA2, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA4() { return { GL_RGBA4, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA8() { return { GL_RGBA8, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA12() { return { GL_RGBA12, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA16() { return { GL_RGBA16, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA8S() { return { GL_RGBA8_SNORM, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA16S() { return { GL_RGBA16_SNORM, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA8UI() { return { GL_RGBA8UI, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA16UI() { return { GL_RGBA16UI, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA32UI() { return { GL_RGBA32UI, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA8I() { return { GL_RGBA8I, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA16I() { return { GL_RGBA16I, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA32I() { return { GL_RGBA32I, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA16F() { return { GL_RGBA16F, true, false, false, true }; }
	TextureFormat TextureFormat::RGBA32F() { return { GL_RGBA32F, true, false, false, true }; }

	TextureFormat TextureFormat::RGB4() { return { GL_RGB4, true, false, false, true }; }
	TextureFormat TextureFormat::RGB5() { return { GL_RGB5, true, false, false, true }; }
	TextureFormat TextureFormat::RGB8() { return { GL_RGB8, true, false, false, true }; }
	TextureFormat TextureFormat::RGB10() { return { GL_RGB10, true, false, false, true }; }
	TextureFormat TextureFormat::RGB12() { return { GL_RGB12, true, false, false, true }; }
	TextureFormat TextureFormat::RGB16() { return { GL_RGB16, true, false, false, true }; }
	TextureFormat TextureFormat::RGB8S() { return { GL_RGB8_SNORM, true, false, false, true }; }
	TextureFormat TextureFormat::RGB16S() { return { GL_RGB16_SNORM, true, false, false, true }; }
	TextureFormat TextureFormat::RGB8UI() { return { GL_RGB8UI, true, false, false, true }; }
	TextureFormat TextureFormat::RGB16UI() { return { GL_RGB16UI, true, false, false, true }; }
	TextureFormat TextureFormat::RGB32UI() { return { GL_RGB32UI, true, false, false, true }; }
	TextureFormat TextureFormat::RGB8I() { return { GL_RGB8I, true, false, false, true }; }
	TextureFormat TextureFormat::RGB16I() { return { GL_RGB16I, true, false, false, true }; }
	TextureFormat TextureFormat::RGB32I() { return { GL_RGB32I, true, false, false, true }; }
	TextureFormat TextureFormat::RGB16F() { return { GL_RGB16F, true, false, false, true }; }
	TextureFormat TextureFormat::RGB32F() { return { GL_RGB32F, true, false, false, true }; }

	TextureFormat TextureFormat::RG8() { return { GL_RG8, true, false, false, true }; }
	TextureFormat TextureFormat::RG16() { return { GL_RG16, true, false, false, true }; }
	TextureFormat TextureFormat::RG8S() { return { GL_RG8_SNORM, true, false, false, true }; }
	TextureFormat TextureFormat::RG16S() { return { GL_RG16_SNORM, true, false, false, true }; }
	TextureFormat TextureFormat::RG8UI() { return { GL_RG8UI, true, false, false, true }; }
	TextureFormat TextureFormat::RG16UI() { return { GL_RG16UI, true, false, false, true }; }
	TextureFormat TextureFormat::RG32UI() { return { GL_RG32UI, true, false, false, true }; }
	TextureFormat TextureFormat::RG8I() { return { GL_RG8I, true, false, false, true }; }
	TextureFormat TextureFormat::RG16I() { return { GL_RG16I, true, false, false, true }; }
	TextureFormat TextureFormat::RG32I() { return { GL_RG32I, true, false, false, true }; }
	TextureFormat TextureFormat::RG16F() { return { GL_RG16F, true, false, false, true }; }
	TextureFormat TextureFormat::RG32F() { return { GL_RG32F, true, false, false, true }; }

	TextureFormat TextureFormat::R8() { return { GL_R8, true, false, false, true }; }
	TextureFormat TextureFormat::R16() { return { GL_R16, true, false, false, true }; }
	TextureFormat TextureFormat::R8S() { return { GL_R8_SNORM, true, false, false, true }; }
	TextureFormat TextureFormat::R16S() { return { GL_R16_SNORM, true, false, false, true }; }
	TextureFormat TextureFormat::R8UI() { return { GL_R8UI, true, false, false, true }; }
	TextureFormat TextureFormat::R16UI() { return { GL_R16UI, true, false, false, true }; }
	TextureFormat TextureFormat::R32UI() { return { GL_R32UI, true, false, false, true }; }
	TextureFormat TextureFormat::R8I() { return { GL_R8I, true, false, false, true }; }
	TextureFormat TextureFormat::R16I() { return { GL_R16I, true, false, false, true }; }
	TextureFormat TextureFormat::R32I() { return { GL_R32I, true, false, false, true }; }
	TextureFormat TextureFormat::R16F() { return { GL_R16F, true, false, false, true }; }
	TextureFormat TextureFormat::R32F() { return { GL_R32F, true, false, false, true }; }

	TextureFormat TextureFormat::R3G3B2() { return { GL_R3_G3_B2, true, false, false, true }; }
	TextureFormat TextureFormat::RGB5A1() { return { GL_RGB5_A1, true, false, false, true }; }
	TextureFormat TextureFormat::RGB10A2() { return { GL_RGB10_A2, true, false, false, true }; }
	TextureFormat TextureFormat::RGB10A2UI() { return { GL_RGB10_A2UI, true, false, false, true }; }
	TextureFormat TextureFormat::RG11B10F() { return { GL_R11F_G11F_B10F, true, false, false, true }; }
	TextureFormat TextureFormat::RGB9E5() { return { GL_RGB9_E5, false, false, false, true }; }
	TextureFormat TextureFormat::RGB565() { return { GL_RGB565, true, false, false, true }; }

	TextureFormat TextureFormat::Depth16() { return { GL_DEPTH_COMPONENT16, false, true, false, true }; }
	TextureFormat TextureFormat::Depth24() { return { GL_DEPTH_COMPONENT24, false, true, false, true }; }
	TextureFormat TextureFormat::Depth32() { return { GL_DEPTH_COMPONENT32, false, true, false, true }; }
	TextureFormat TextureFormat::Depth32F() { return { GL_DEPTH_COMPONENT32F, false, true, false, true }; }
	TextureFormat TextureFormat::Depth24Stencil8() { return { GL_DEPTH24_STENCIL8, false, true, true, true }; }
	TextureFormat TextureFormat::Depth32FStencil8() { return { GL_DEPTH32F_STENCIL8, false, true, true, true }; }
	TextureFormat TextureFormat::Stencil1() { return { GL_STENCIL_INDEX1, false, false, true, true }; }
	TextureFormat TextureFormat::Stencil4() { return { GL_STENCIL_INDEX4, false, false, true, true }; }
	TextureFormat TextureFormat::Stencil8() { return { GL_STENCIL_INDEX8, false, false, true, true }; }
	TextureFormat TextureFormat::Stencil16() { return { GL_STENCIL_INDEX16, false, false, true, true }; }

	TextureFormat TextureFormat::Stencil() { return { GL_STENCIL, false, false, true, false }; }
	TextureFormat TextureFormat::Depth() { return { GL_DEPTH, false, true, false, false }; }
	TextureFormat TextureFormat::DepthStencil() { return { GL_DEPTH_STENCIL, false, true, true, false }; }
	TextureFormat TextureFormat::Red() { return { GL_RED, true, false, false, false }; }
	TextureFormat TextureFormat::Green() { return { GL_GREEN, false, false, false, false }; }
	TextureFormat TextureFormat::Blue() { return { GL_BLUE, false, false, false, false }; }
	TextureFormat TextureFormat::RG() { return { GL_RG, true, false, false, false }; }
	TextureFormat TextureFormat::RGB() { return { GL_RGB, true, false, false, false }; }
	TextureFormat TextureFormat::RGBA() { return { GL_RGBA, true, false, false, false }; }
	TextureFormat TextureFormat::BGR() { return { GL_BGR, false, false, false, false }; }
	TextureFormat TextureFormat::BGRA() { return { GL_BGRA, false, false, false, false }; }
	TextureFormat TextureFormat::RedI() { return { GL_RED_INTEGER, false, false, false, false }; }
	TextureFormat TextureFormat::GreenI() { return { GL_GREEN_INTEGER, false, false, false, false }; }
	TextureFormat TextureFormat::BlueI() { return { GL_BLUE_INTEGER, false, false, false, false }; }
	TextureFormat TextureFormat::RGI() { return { GL_RG_INTEGER, false, false, false, false }; }
	TextureFormat TextureFormat::RGBI() { return { GL_RGB_INTEGER, false, false, false, false }; }
	TextureFormat TextureFormat::RGBAI() { return { GL_RGBA_INTEGER, false, false, false, false }; }
	TextureFormat TextureFormat::BGRI() { return { GL_BGR_INTEGER, false, false, false, false }; }
	TextureFormat TextureFormat::BGRAI() { return { GL_BGRA_INTEGER, false, false, false, false }; }
#pragma endregion
#pragma region BufferBit
	BufferBit BufferBit::Color()		noexcept { return GL_COLOR_BUFFER_BIT;		}
	BufferBit BufferBit::Depth()		noexcept { return GL_DEPTH_BUFFER_BIT;		}
	BufferBit BufferBit::Stencil()		noexcept { return GL_STENCIL_BUFFER_BIT;	}
#pragma endregion
}