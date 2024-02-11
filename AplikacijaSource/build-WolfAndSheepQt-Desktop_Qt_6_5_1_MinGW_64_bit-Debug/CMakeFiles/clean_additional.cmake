# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WolfAndSheepQt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WolfAndSheepQt_autogen.dir\\ParseCache.txt"
  "WolfAndSheepQt_autogen"
  )
endif()
