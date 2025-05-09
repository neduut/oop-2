cmake_minimum_required(VERSION 3.25)
project(Objektinis)

# Nustatome konsolinę programą Windows sistemai
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-mconsole")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Atsisiunčiame ir konfigūruojame Catch2
include(FetchContent)
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(catch2)

# Pagrindinės bibliotekos šaltiniai
set(LIB_SOURCES
    src/functions.cpp
    src/student.cpp
    src/timeMeasurement.cpp
    src/utils.cpp
)

add_library(Objektinis_lib STATIC ${LIB_SOURCES})

# Pagrindinė programa
add_executable(Objektinis src/main.cpp)
target_link_libraries(Objektinis PRIVATE Objektinis_lib)

# Testų programa
add_executable(tests src/catchTest.cpp)
target_link_libraries(tests PRIVATE 
    Objektinis_lib 
    Catch2::Catch2WithMain  # Naudojame Catch2WithMain, kad automatiškai sugeneruotų main()
)

# Papildomi linkerio flag'ai Windows
if(WIN32)
    set_target_properties(tests PROPERTIES LINK_FLAGS "-mconsole")
    set_target_properties(Objektinis PROPERTIES LINK_FLAGS "-mconsole")
endif()