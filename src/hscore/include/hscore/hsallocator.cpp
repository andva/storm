//#include "hsallocator.h"
//#include "EASTL/allocator.h"
////
////#include <hscore/assert.h>
////
////#ifndef posix_memalign
////#define posix_memalign(p, a, s) (((*(p)) = _aligned_malloc((s), (a))), *(p) ?0 :errno)
////#endif
////
//#pragma warning(disable: 4290)
//
//void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* name,
//  int flags, unsigned debugFlags, const char* file, int line) THROW_SPEC_1(std::bad_alloc)
//{
//  return CustomAllocator::gpDefaultAllocator->allocate(size, alignment, alignmentOffset, flags);
//}
////
//
//void* operator new[](size_t size, const char* name, int flags,
//  unsigned debugFlags, const char* file, int line) THROW_SPEC_1(std::bad_alloc)
//{
//  return CustomAllocator::gpDefaultAllocator->allocate(size, flags);
//}
////
///*void* operator new(size_t size) THROW_SPEC_1(std::bad_alloc)
//{
//  
//}
//
//void* operator new[](size_t size) THROW_SPEC_1(std::bad_alloc)
//{
//  
//}
//
//void operator delete(void* p) THROW_SPEC_0
//{
//  if (p) // The standard specifies that 'delete NULL' is a valid operation.
//    free(p);
//}
//
//void operator delete[](void* p) THROW_SPEC_0
//{
//  if (p)
//    free(p);
//}*/