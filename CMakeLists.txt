# CMakeList.txt: proyecto de CMake para FlyBird, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.10)

include(FetchContent)
FetchContent_Declare(
	raylib_static 
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
	GIT_TAG        c1ab645ca298a2801097931d1079b10ff7eb9df8
)

FetchContent_MakeAvailable(raylib_static)


# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("FlyBird")

# Agregue un origen al ejecutable de este proyecto.
add_executable (FlyBird "FlyBird.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FlyBird PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(FlyBird PRIVATE raylib_static)


