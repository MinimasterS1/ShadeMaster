#pragma once

#define CORE_API_EXPORTS

#ifndef Memory_H
#define Memory_H

#include "SM_CoreExport.hpp"

#include "SM_DynamicAllocator.h"

class CORE_API Memory {
public:
    static void* Allocate(size_t size, size_t alignment = alignof(std::max_align_t));

    static void Deallocate(void* ptr, size_t size, size_t alignment = alignof(std::max_align_t));
    static void Free(void* ptr);


private:
    static DynamicAllocator allocator;
};

#endif //Memory_H