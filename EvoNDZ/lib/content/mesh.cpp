#include "mesh.h"

#include "../util.h"

namespace evo::data {
	Mesh Mesh::Load(unsigned char* data, uint64_t length) {
		unsigned char format = data[0];
		size_t di = 1;
		size_t faceCount = ReadBytesMove<uint16_t>(data, di);
		size_t vertCount = ReadBytesMove<uint16_t>(data, di);
		Mesh mesh(format, faceCount, vertCount);
		for (size_t fi = 0; fi < faceCount; ++fi) {
			for (size_t pi = 0; pi < 3; ++pi) {
				mesh.m_faces[fi].p[pi] = ReadBytesMove<uint16_t>(data, di);
			}
		}
		for (size_t vi = 0; vi < vertCount; ++vi) {
			mesh.m_positions[vi] = ReadBytesMove<evo::math::Vector3>(data, di);
			if (mesh.m_hasNormals) mesh.m_normals[vi] = ReadBytesMove<evo::math::Vector3>(data, di);
			if (mesh.m_hasTexcoords) mesh.m_texcoords[vi] = ReadBytesMove<evo::math::Vector2>(data, di);
		}
		return mesh;
	}
}