//
//  bxallocator.hpp
//  EnhancedForest
//
//  Created by Admin on 06.08.2021.
//

#pragma once

namespace bx {
struct AllocatorI;
}

namespace entry {
bx::AllocatorI *getAllocator();
} // namespace entry
