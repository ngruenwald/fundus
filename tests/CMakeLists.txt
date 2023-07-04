set(target unit_tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(
  ${target}
  main.cpp
  arguments_tests.cpp
  enum_tests.cpp
  format_tests.cpp
  guard_tests.cpp
  log_tests.cpp
  result_tests.cpp
)

target_include_directories(
  ${target}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(
  ${target}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
