#include "SM_Memory.h"

DynamicAllocator Memory::allocator;

void* Memory::Allocate(size_t size, size_t alignment)
{
    return allocator.allocate(size, alignment);
}

void Memory::Deallocate(void* ptr, size_t size, size_t alignment)
{
    allocator.deallocate(ptr, size, alignment);
}

void Memory::Free(void* ptr)
{
    allocator.free(ptr);
}
