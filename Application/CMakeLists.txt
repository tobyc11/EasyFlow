file(GLOB_RECURSE _ALL_SOURCEFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.c *.h *.hpp *.cxx)
add_executable(EasyFlow ${_ALL_SOURCEFILES})

target_link_libraries(EasyFlow PRIVATE debug wxWidgetsD)
target_link_libraries(EasyFlow PRIVATE optimized wxWidgets)
set_target_properties(EasyFlow PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
