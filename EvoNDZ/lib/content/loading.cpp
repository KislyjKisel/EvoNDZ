//#include <fstream>
//#include <vector>
//#include <algorithm>
//#include "loading.h"
//#include "content_storage.h"
//#include "compression.h"
//#include "../platform/platform.h"
//
//#include "default_format.h"
//#include "texture2d.h"
//#include "shader.h"
//#include "mesh.h"
//#include "../opengl/technique.h"
//#include "../opengl/texture2d.h"
//#include "../opengl/mesh.h"
//
//namespace evo::data {
//	struct Loading::UnprocessedData {
//		unsigned char* data;
//		size_t size;
//		std::string name;
//		uint16_t typeID;
//		uint8_t loadingPosition;
//
//		UnprocessedData(std::string name_, uint16_t typeID_, size_t size_) : 
//			size(size_), typeID(typeID_), loadingPosition(LoadingPosition[typeID_]), 
//			data(new unsigned char[size_]), name(name_) { }
//
//		bool operator < (const Loading::UnprocessedData& other) const
//		{
//			return loadingPosition < other.loadingPosition;
//		}
//
//		static inline std::vector<UnprocessedData> container;
//	};
//
//
//	void Loading::LoadFile(std::filesystem::path path) {
//		std::ifstream fs(path, std::ios::binary | std::ios::ate);
//		auto size = (uint64_t)fs.tellg() - 1ui64;
//		fs.seekg(0, std::ios::beg);
//		auto buffer = new std::vector<unsigned char>(size); // ._.
//		unsigned char bitFillSize = 0;
//		fs.read(reinterpret_cast<char*>(&bitFillSize), 1);
//		fs.read(reinterpret_cast<char*>(buffer->data()), size);
//
//		evo::Bitvector<uint64_t> compressedData = evo::Bitvector<uint64_t>(*buffer);
//		compressedData.resize(compressedData.size() - bitFillSize);
//
//		std::vector<uint8_t> decompressedData = HuffmanDecode(compressedData);
//		delete buffer; // ._.
//
//		uint16_t count = 0;
//		auto entries = GetArchiveEntries(decompressedData.data(), count);
//		for (uint16_t i = 0; i < count; ++i) {
//			UnprocessedData::container.push_back(UnprocessedData(entries[i].name, entries[i].type, entries[i].dataLength));
//			std::copy(
//				decompressedData.data() + entries[i].dataStart,
//				decompressedData.data() + entries[i].dataStart + entries[i].dataLength, 
//				UnprocessedData::container[UnprocessedData::container.size() - 1].data
//			);
//		}
//	}
//
//	void Loading::LoadDirectory(std::filesystem::path path) {
//		for (const auto& entry : std::filesystem::directory_iterator(path)) {
//			if (entry.is_regular_file()) {
//				LoadFile(entry.path());
//			}
//			else if (entry.is_directory()) {
//				LoadDirectory(entry.path());
//			}
//		}
//	}
//
//	void Loading::LoadContent() {
//		// evo::GetExecutableFilePath(); minus exe and file name - getexedir func in platform
//		std::wstring path = L"content\\"; 
//		LoadDirectory(path);
//		std::sort(UnprocessedData::container.begin(), UnprocessedData::container.end());
//		ProcessData();
//	}
//
//	void Loading::LoadSingle(const UnprocessedData& data) {
//		m_loadFunctions[data.typeID](data.name, data.data, data.size);
//	}
//
//	void Loading::CreateDefaultContentStorages() {
//		CreateFileContentStorage<Texture2D>(Typeid_Texture2D, Texture2D::Load);
//		CreateFileContentStorage<Shader>(Typeid_Shader, Shader::Load);
//		CreateFileContentStorage<Mesh>(Typeid_Mesh, Mesh::Load);
//		CreateFileContentStorage<evo::ogl::Technique>(Typeid_Technique, evo::ogl::Technique::Load);
//	}
//
//	void Loading::ProcessData() {
//		for (size_t i = 0; i < UnprocessedData::container.size(); ++i) {
//			Loading::LoadSingle(UnprocessedData::container[i]);
//			delete[] UnprocessedData::container[i].data;
//		}
//	}
//
//	void Loading::TransferToGpuTexture2D(size_t& indexResult, const std::string& textureName) {
//		ContentStorage<evo::ogl::Texture2D>::Store(
//			textureName, 
//			evo::ogl::Texture2D(ContentStorage<evo::data::Texture2D>::GetByName(textureName)),
//			indexResult
//		);
//	}
//	void Loading::TransferToGpuMesh(size_t& indexResult, const std::string& meshName) {
//		ContentStorage<evo::ogl::Mesh>::Store(
//			meshName,
//			evo::ogl::Mesh(ContentStorage<evo::data::Mesh>::GetByName(meshName)),
//			indexResult
//		);
//	}
//}