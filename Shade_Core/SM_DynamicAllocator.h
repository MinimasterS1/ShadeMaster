#pragma once

#ifndef Dynamic_Allocator_H
#define Dynamic_Allocator_H

#include "SM_CoreExport.hpp"


class CORE_API DynamicAllocator {
public:

    DynamicAllocator();
    ~DynamicAllocator();
    DynamicAllocator(size_t initialSize, size_t maxSize);

    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t));

    void deallocate(void* ptr, size_t size, size_t alignment = alignof(std::max_align_t));

    void free(void* ptr);

private:

    size_t align(size_t size, size_t alignment);

    void allocateBlock(size_t size);

    size_t max_size;
    size_t total_size = 0;
    std::map<size_t, std::vector<void*>> free_blocks;
    std::vector<std::vector<char>> blocks;
};

#endif //Dynamic_Allocator_H

