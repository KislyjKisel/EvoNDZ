#include "../../include/EvoNDZ/content/content.h"

namespace evo::content
{
	StorageManager::StorageManager(
		std::unordered_map<std::type_index, std::unique_ptr<LoaderBase>>&& loaders, std::vector<std::string>&& names
	) : m_names(names) 
	{
		for (auto& [k, v] : loaders) {
			m_storages.push_back(v->store());
		}
	}

	void LoadingManager::resolve_pointers() {
		for (auto& [ti, l] : m_loaderMap) {
			l->resolve_pointers(*this);
		}
	}

	void LoadingManager::load_archive(std::string_view archiveName, std::span<const std::byte> archive) {
		archiveName = decl_name(archiveName);
		auto it = evo::archive::EntryIterator::Begin(archive.data());
		auto end = evo::archive::EntryIterator::End();
		for (; it != end; ++it) {
			m_loaderMap.at(m_typeMap.at(it->type))->load(
				*this,
				{ archiveName, decl_name({ (const char*)( archive.data() + it->nameOffset ), it->nameSize }) },
				{ archive.data() + it->dataOffset, it->dataSize }
			);
		}
	}

	std::string_view LoadingManager::decl_name(std::string_view n) {
		auto it = std::find(m_names.begin(), m_names.end(), n);
		return it == m_names.end() ? m_names.emplace_back(n) : *it;
	}
}