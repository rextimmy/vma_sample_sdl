cmake_minimum_required(VERSION 3.2)
project(VmaSample)

#main dir
set(VMASAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#cmake module path
list(APPEND CMAKE_MODULE_PATH "${VMASAMPLE_DIR}/cmake-modules")

find_package(Vulkan REQUIRED)

#external libs
#SDL Lib
SET(SDL_STATIC ON CACHE BOOL "" FORCE)
SET(SDL_SHARED OFF CACHE BOOL "" FORCE)
add_subdirectory("${VMASAMPLE_DIR}/external/sdl2" EXCLUDE_FROM_ALL)

#Source code
file(GLOB VMASAMPLE_SRC "${VMASAMPLE_DIR}/src/*.cpp" "${VMASAMPLE_DIR}/src/*.h")

#includes
set(VMASAMPLE_INCLUDES
   ${VMASAMPLE_DIR}/src
   ${VMASAMPLE_DIR}/external/sdl2/include
   ${VMASAMPLE_DIR}/external/VulkanMemoryAllocator
   ${VMASAMPLE_DIR}/external/mathfu-1.1.0/include
   ${VULKAN_INCLUDE_DIR}
)

#Libs
set (VMASAMPLE_LIBS	SDL2main SDL2-static ${VULKAN_LIBRARY} )

#Libs - apple
if(APPLE)
	set(VMASAMPLE_LIBS ${VMASAMPLE_LIBS}
		"-framework Cocoa"
		"-framework IOKit"
		"-framework CoreVideo"
		"-framework QuartzCore"
		"-framework Metal"
   )
endif()

#Executable
if(APPLE)
	add_executable(VmaSample MACOSX_BUNDLE ${VMASAMPLE_SRC})
elseif(WIN32)
	add_executable(VmaSample WIN32 ${VMASAMPLE_SRC})
else()
	add_executable(VmaSample ${VMASAMPLE_SRC})
endif()

target_link_libraries(VmaSample ${VMASAMPLE_LIBS})
target_include_directories(VmaSample PRIVATE ${VMASAMPLE_INCLUDES})

#Target properties
#single config
set_target_properties(VmaSample PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${VMASAMPLE_DIR}/bin")
#multi-config
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
	string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
	set_target_properties(VmaSample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${VMASAMPLE_DIR}/bin")
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set_target_properties(VmaSample PROPERTIES DEBUG_POSTFIX "_debug")

if(WIN32)
	target_compile_definitions(VmaSample PRIVATE VK_USE_PLATFORM_WIN32_KHR)
elseif(APPLE)
	target_compile_definitions(VmaSample PRIVATE VK_USE_PLATFORM_MACOS_MVK)
elseif(UNIX)
	target_compile_definitions(VmaSample PRIVATE VK_USE_PLATFORM_XLIB_KHR)
endif()

#Project solution folders
source_group("Source" REGULAR_EXPRESSION ${VMASAMPLE_DIR}/src/.*)

# Set Visual Studio startup project(cmake 3.6+)
if((${CMAKE_VERSION} VERSION_EQUAL 3.6.0) OR (${CMAKE_VERSION} VERSION_GREATER 3.6.0) AND MSVC)
	set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT VmaSample )
endif()
