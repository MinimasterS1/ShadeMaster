#include "SM_DynamicAllocator.h"

DynamicAllocator::DynamicAllocator()
{

}

DynamicAllocator::~DynamicAllocator()
{

}

DynamicAllocator::DynamicAllocator(size_t initialSize, size_t maxSize)
    : max_size(maxSize)
{
    allocateBlock(initialSize);
}

void* DynamicAllocator::allocate(size_t size, size_t alignment)
{

    size = align(size, alignment);

    auto it = free_blocks.lower_bound(size);
    if (it != free_blocks.end()) {
        void* ptr = it->second.back();
        it->second.pop_back();
        if (it->second.empty()) {
            free_blocks.erase(it);
        }

        Log.Info("Memory Use", size);


        return ptr;
    }

    if (total_size + size <= max_size) {
        allocateBlock(size);
        auto last = --free_blocks.lower_bound(size);
        void* ptr = last->second.back();
        last->second.pop_back();
        if (last->second.empty()) {
            free_blocks.erase(last);
        }
        return ptr;
    }

    return nullptr;

}

void DynamicAllocator::deallocate(void* ptr, size_t size, size_t alignment)
{

    size = align(size, alignment);
    free_blocks[size].push_back(ptr);

    Log.Info("Memory Free", size);

}

void DynamicAllocator::free(void* ptr)
{
    auto it = std::find_if(free_blocks.begin(), free_blocks.end(), [ptr](const auto& pair) {
        return std::find(pair.second.begin(), pair.second.end(), ptr) != pair.second.end();
        });

    if (it != free_blocks.end()) {
        size_t blockSize = it->first;
        it->second.erase(std::remove(it->second.begin(), it->second.end(), ptr), it->second.end());

        if (it->second.empty()) {
            free_blocks.erase(it);
        }

        Log.Info("Memory Free", blockSize);
    }
    else {
        Log.Error("Memory Free Error: Invalid Pointer", 0.0f, __FILE__, __LINE__);
    }
}

size_t DynamicAllocator::align(size_t size, size_t alignment)
{

    return (size + alignment - 1) & ~(alignment - 1);

}

void DynamicAllocator::allocateBlock(size_t size)
{

    std::vector<char> new_block(size);
    blocks.push_back(std::move(new_block));
    free_blocks[size].push_back(blocks.back().data());
    total_size += size;

}
