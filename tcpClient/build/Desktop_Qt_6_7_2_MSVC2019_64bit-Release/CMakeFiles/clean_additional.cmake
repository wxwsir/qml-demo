# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\apptcpClient_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\apptcpClient_autogen.dir\\ParseCache.txt"
  "apptcpClient_autogen"
  )
endif()
