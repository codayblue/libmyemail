cmake_minimum_required(VERSION 3.1.3 FATAL_ERROR)

project(myemail)

# Set the standard
set(CMAKE_CXX_STANDARD 11)

add_library(myemail SHARED myemail.cc)

# MySQL header
target_link_libraries(myemail mysqlclient)

# MySQL Deps
target_link_libraries(myemail pthread)
target_link_libraries(myemail z)
target_link_libraries(myemail m)
target_link_libraries(myemail ssl)
target_link_libraries(myemail crypto)
target_link_libraries(myemail dl)

# For make install
install(TARGETS myemail DESTINATION ${MYSQL_PLUGIN_DIR})
