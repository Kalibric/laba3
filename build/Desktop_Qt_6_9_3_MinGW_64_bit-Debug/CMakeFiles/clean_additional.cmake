# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\laba3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\laba3_autogen.dir\\ParseCache.txt"
  "laba3_autogen"
  )
endif()
