project(InfoConfigExample CXX)

add_executable(egxfg main.cpp)

add_custom_command(TARGET egxfg POST_BUILD
                   COMMENT "Copying configuration file"
                   COMMAND cmake -E copy ${PROJECT_SOURCE_DIR}/example.xfg ${PROJECT_BINARY_DIR}/)

add_custom_command(TARGET egxfg POST_BUILD
                   COMMENT "Copying dynamic libs"
                   COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/libxfg.dll ${PROJECT_BINARY_DIR}/
                   COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/libs/xerces/xerces-c-3.2.2/src/libxerces-c.dll ${PROJECT_BINARY_DIR}/
                   )

get_target_property(XFG_INCLUDE_DIR xfg INCLUDE_DIRECTORIES)

target_include_directories(egxfg PRIVATE ${XFG_INCLUDE_DIR})
target_link_libraries(egxfg xfg)
