# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles/qt-smallboy_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/qt-smallboy_autogen.dir/ParseCache.txt"
  "qt-smallboy_autogen"
  )
endif()
