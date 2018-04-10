#ifndef COMMON_H_
#define COMMON_H_

#include "VmaUsage.h"

#define MATHFU_COMPILE_WITHOUT_SIMD_SUPPORT
#include <mathfu/glsl_mappings.h>
#include <mathfu/constants.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <array>
#include <type_traits>
#include <utility>
#include <chrono>
#include <string>

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <SDL.h>


typedef std::chrono::high_resolution_clock::time_point time_point;
typedef std::chrono::high_resolution_clock::duration duration;

#define ERR_GUARD_VULKAN(Expr) do { VkResult res__ = (Expr); if (res__ < 0) assert(0); } while(0)

extern VkPhysicalDevice g_hPhysicalDevice;
extern VkDevice g_hDevice;
extern VmaAllocator g_hAllocator;
extern bool g_MemoryAliasingWarningEnabled;

inline float ToFloatSeconds(duration d)
{
    return std::chrono::duration_cast<std::chrono::duration<float> >(d).count();
}

template <typename T>
inline T ceil_div(T x, T y)
{
	return (x+y-1) / y;
}

template <typename T>
static inline T align_up(T val, T align)
{
	return (val + align - 1) / align * align;
}

#endif
