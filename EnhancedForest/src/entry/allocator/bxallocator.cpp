//
//  bxallocator.cpp
//  EnhancedForest
//
//  Created by Admin on 06.08.2021.
//

#include <bx/allocator.h>

#include "bxallocator.hpp"

namespace entry {

bx::AllocatorI *getDefaultAllocator();

bx::AllocatorI *g_allocator = getDefaultAllocator();

bx::AllocatorI *getDefaultAllocator() {
    BX_PRAGMA_DIAGNOSTIC_PUSH();
    BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 's_allocator' hides global declaration
    BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");
    static bx::DefaultAllocator s_allocator;
    return &s_allocator;
    BX_PRAGMA_DIAGNOSTIC_POP();
}

bx::AllocatorI *getAllocator() {
    if (NULL == g_allocator) {
        g_allocator = getDefaultAllocator();
    }

    return g_allocator;
}

} // namespace entry
