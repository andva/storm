//#ifndef HSCORE_ALLOCATOR_H
//#define HSCORE_ALLOCATOR_H
//
//#include <EABase/eabase.h>
//#include <stddef.h>
//#include <new>
//
//#include <hscore/log.h>
//
//#pragma once
//
/////////////////////////////////////////////////////////////////////////////////
//// throw specification wrappers, which allow for portability.
/////////////////////////////////////////////////////////////////////////////////
//
//#if defined(EA_COMPILER_NO_EXCEPTIONS) && (!defined(__MWERKS__) || defined(_MSL_NO_THROW_SPECS)) && !defined(EA_COMPILER_RVCT)
//#define THROW_SPEC_0    // Throw 0 arguments
//#define THROW_SPEC_1(x) // Throw 1 argument
//#else
//#define THROW_SPEC_0    throw()
//#define THROW_SPEC_1(x) throw(x)
//#endif
//
//#pragma warning(push, 0)
//#pragma warning(disable: 4290)
//
/////////////////////////////////////////////////////////////////////////////////
//// operator new used by EASTL
/////////////////////////////////////////////////////////////////////////////////
////
//void* operator new[](size_t size, const char* /*name*/, int /*flags*/,
//  unsigned /*debugFlags*/, const char* /*file*/, int /*line*/) THROW_SPEC_1(std::bad_alloc);
////
//void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* /*name*/,
//  int flags, unsigned /*debugFlags*/, const char* /*file*/, int /*line*/) THROW_SPEC_1(std::bad_alloc);
////
//
/////////////////////////////////////////////////////////////////////////////////
//// Other operator new as typically required by applications.
/////////////////////////////////////////////////////////////////////////////////
//
////void* operator new(size_t size) THROW_SPEC_1(std::bad_alloc);
////
////
////void* operator new[](size_t size) THROW_SPEC_1(std::bad_alloc);
////
////
///////////////////////////////////////////////////////////////////////////////////
////// Operator delete, which is shared between operator new implementations.
///////////////////////////////////////////////////////////////////////////////////
////
////void operator delete(void* p) THROW_SPEC_0;
////
////
////void operator delete[](void* p) THROW_SPEC_0;
//
//#pragma warning(pop)
//
//#define EASTL_USER_DEFINED_ALLOCATOR // Must declare this to avoid new[]/delete[] prototypes in allocator.h
//#undef EASTL_ALLOCATOR_DEFAULT_NAME
//#define EASTL_ALLOCATOR_DEFAULT_NAME "SimpleAlloc"
//#undef EASTLAllocatorType
//#define EASTLAllocatorType CustomAllocator::allocator
//#undef EASTLAllocatorDefault
//#define EASTLAllocatorDefault CustomAllocator::GetDefaultAllocator
//#undef EASTL_ALLOCATOR_EXPLICIT_ENABLED
//#define EASTL_ALLOCATOR_EXPLICIT_ENABLED 1
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <EABase/eabase.h>
//#include <EASTL/allocator.h>
//#include <EASTL/internal/config.h>
//#include <EABase/nullptr.h>
//#include <errno.h>
//
//#ifdef WIN32
//#ifdef _WIN32
//static int check_align(size_t align)
//{
//  for (size_t i = sizeof(void *); i != 0; i *= 2)
//    if (align == i)
//      return 0;
//  return EINVAL;
//}
//
//int posix_memalign(void **ptr, size_t align, size_t size)
//{
//  if (check_align(align))
//    return EINVAL;
//
//  int saved_errno = errno;
//  void *p = _aligned_malloc(size, align);
//  if (p == NULL)
//  {
//    errno = saved_errno;
//    return ENOMEM;
//  }
//
//  *ptr = p;
//  return 0;
//}
//#endif
//#endif
//
//namespace CustomAllocator
//{
//
//  // Define our allocator class and implement it
//  class allocator
//  {
//  public:
//
//    // Constructors
//    explicit allocator(const char* pName = EASTL_ALLOCATOR_DEFAULT_NAME)
//    {
//#if EASTL_NAME_ENABLED
//      mpName = pName;
//#endif
//    }
//    inline allocator(const allocator& alloc)
//    {
//#if EASTL_NAME_ENABLED
//      mpName = alloc.mpName;
//#endif
//    }
//    inline allocator(const allocator&, const char* name)
//    {
//#if EASTL_NAME_ENABLED
//      mpName = name ? name : EASTL_ALLOCATOR_DEFAULT_NAME;
//#endif
//    }
//
//    // Assignment
//    inline allocator& operator=(const allocator& alloc)
//    {
//#if EASTL_NAME_ENABLED
//      mpName = alloc.mpName;
//#endif
//      return *this; // All considered equal since they're global malloc/free
//    }
//
//    // Allocation & Deallocation
//    inline void* allocate(size_t n, int flags = 0)
//    {
//#if defined(EA_DEBUG)
//      printf("malloc %lu bytes\n", n);
//#endif
//      return ::malloc(n);
//    }
//    inline void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0)
//    {
//      void* mem = NULL;
//
//#if defined(EA_DEBUG)
//      printf("malloc %lu bytes\n", n);
//#endif
//
//      posix_memalign(&mem, alignment, n);
//      return mem;
//    }
//
//    inline void deallocate(void* p, size_t n)
//    {
//#if defined(EA_DEBUG)
//      printf("Freeing %lu bytes\n", n);
//#endif
//      ::free(p);
//    }
//
//    // Name info
//    inline const char* get_name() const
//    {
//#if EASTL_NAME_ENABLED
//      return mpName;
//#else
//      return EASTL_ALLOCATOR_DEFAULT_NAME;
//#endif
//    }
//    inline void set_name(const char* name)
//    {
//#if EASTL_NAME_ENABLED
//      mpName = name;
//#endif
//    }
//
//
//  private:
//#if EASTL_NAME_ENABLED
//    const char* mpName;
//#endif
//  };
//
//  // EASTL expects us to define these operators (allocator.h L103)
//  bool operator==(const allocator& a, const allocator& b)
//  {
//    return true; // All are considered equal since they are global malloc/free
//  }
//  bool operator!=(const allocator& a, const allocator& b)
//  {
//    return false; // All are considered equal since they are global malloc/free
//  }
//
//  // Defines the EASTL API glue, so we can set our allocator as the global default allocator
//  allocator  gDefaultAllocator;
//  allocator* gpDefaultAllocator = &gDefaultAllocator;
//
//  allocator* GetDefaultAllocator()
//  {
//    return gpDefaultAllocator;
//  }
//
//  allocator* SetDefaultAllocator(allocator* pNewAlloc)
//  {
//    allocator* pOldAlloc = gpDefaultAllocator;
//    gpDefaultAllocator = pNewAlloc;
//    return pOldAlloc;
//  }
//};
//
//
//// EASTL also wants us to define this (see string.h line 197)
//int Vsnprintf8(char8_t* pDestination, size_t n, const char8_t* pFormat, va_list arguments)
//{
//#ifdef _MSC_VER
//  return _vsnprintf(pDestination, n, pFormat, arguments);
//#else
//  return vsnprintf(pDestination, n, pFormat, arguments);
//#endif
//}
//
//#endif