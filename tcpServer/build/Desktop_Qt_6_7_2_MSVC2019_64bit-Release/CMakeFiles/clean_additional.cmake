# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\apptcpServer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\apptcpServer_autogen.dir\\ParseCache.txt"
  "apptcpServer_autogen"
  )
endif()
