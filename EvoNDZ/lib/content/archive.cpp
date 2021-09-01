#include "../../include/EvoNDZ/content/archive.h"
#include "../../include/EvoNDZ/util/bytes.h"

namespace evo::archive {
    //format: C [ T Ns N..(Ns) Ds D..(Ds) ]..C

    Array<std::byte> create(EntryExternal* entries, entry_count_t entryCount) {
        data_size_t archiveTotalSize = sizeof(entry_count_t);
        for (entry_count_t i = 0; i < entryCount; i++) {
            archiveTotalSize += sizeof(type_index_t) + 
                                sizeof(name_size_t) + entries[i].nameSize + 
                                sizeof(data_size_t) + entries[i].dataSize;
        }
        Array<std::byte> archive(archiveTotalSize);
        std::byte* dest = archive.data();

        auto append = [&dest](auto value) { 
            evo::bytes::write(dest, value);
        };

        append(entryCount);

        for (entry_count_t i = 0; i < entryCount; i++) {
            append(entries[i].type);
            append(entries[i].nameSize);
            std::copy(entries[i].name, entries[i].name + entries[i].nameSize, dest);
            dest += entries[i].nameSize;
            append(entries[i].dataSize);
            std::copy(entries[i].data, entries[i].data + entries[i].dataSize, dest);
            dest += entries[i].dataSize;
        }

        return archive;
    }

    const std::byte* load_entry_internal(EntryInternal& entry, const std::byte* ptr, data_size_t offset = 0) {
        auto p = ptr;
        auto bp = p;
        entry.type = evo::bytes::read<type_index_t>(p);
        entry.nameSize = evo::bytes::read<name_size_t>(p);
        entry.nameOffset = ( p - bp ) + offset;
        p += entry.nameSize;
        entry.dataSize = evo::bytes::read<data_size_t>(p);
        entry.dataOffset = ( p - bp ) + offset;
        p += entry.dataSize;
        return p;
    }

    Array<EntryInternal> entries(const std::byte* data, [[maybe_unused]] data_size_t size) {
        auto begin = data;
        entry_count_t entryCount = evo::bytes::read<entry_count_t>(data);
        Array<EntryInternal> entries = Array<EntryInternal>(entryCount);

        for (size_t i = 0; i < entryCount; ++i) {
            data = load_entry_internal(entries[i], data);
        }

        return entries;
    }

    EntryIterator::EntryIterator(const std::byte* bp, entry_count_t r, data_size_t bo) 
        : m_pointer(bp), m_remaining(r), m_info{}
    {
        load_entry_internal(m_info, bp, bo);
    }

    EntryIterator EntryIterator::Begin(const std::byte* archive) {
        auto entryCount = evo::bytes::read<entry_count_t>(archive);
        return EntryIterator(archive, entryCount, sizeof(entry_count_t));
    }

    EntryIterator& EntryIterator::operator++() {
        if (m_remaining <= 1) {
            m_remaining = 0;
            m_pointer = nullptr;
        }
        else {
            --m_remaining;
            m_pointer += entry_size(m_info.nameSize, m_info.dataSize);
            load_entry_internal(m_info, m_pointer, m_info.dataOffset + m_info.dataSize);
        }
        return *this;
    }

    EntryIterator EntryIterator::operator++(int) {
        auto copy = *this;
        if (m_remaining <= 1) {
            m_remaining = 0;
            m_pointer = nullptr;
        }
        else {
            --m_remaining;
            m_pointer += entry_size(m_info.nameSize, m_info.dataSize);
            load_entry_internal(m_info, m_pointer, m_info.dataOffset + m_info.dataSize);  
        }
        return copy;
    }
}