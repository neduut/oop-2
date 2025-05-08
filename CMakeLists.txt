cmake_minimum_required(VERSION 3.25)
project(Objektinis)

include_directories(include)

include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.9
)
FetchContent_MakeAvailable(catch2)

file(GLOB SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "src/catchTest.cpp")

add_executable(Objektinis ${SOURCES})

# add_executable(tests src/catchTest.cpp)

# target_link_libraries(tests Catch2::Catch2)

# target_include_directories(tests PRIVATE ${catch2_SOURCE_DIR}/single_include)
