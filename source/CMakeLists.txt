cmake_minimum_required(VERSION 3.1.3 FATAL_ERROR)

project(myemail)

# Variables
if (DEFINED INSTALL_DIR)
  set(MYSQL_PLUGIN_DIR ${INSTALL_DIR})
else (DEFINED INSTALL_DIR)
  set(MYSQL_PLUGIN_DIR /usr/lib/mysql/plugin)
endif (DEFINED INSTALL_DIR)

# Set the standard
set(CMAKE_CXX_STANDARD 11)

find_library(mysqlclientlib mysqlclient)
find_library(PocoNetlib PocoNet)
find_library(PocoNetlib PocoNetSSL)

add_library(myemail SHARED myemail.cc)

# MySQL header
target_link_libraries(${PROJECT_NAME} mysqlclient)

# MySQL Deps
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} z)
target_link_libraries(${PROJECT_NAME} m)
target_link_libraries(${PROJECT_NAME} ssl)
target_link_libraries(${PROJECT_NAME} crypto)
target_link_libraries(${PROJECT_NAME} dl)

# Poco libs
target_link_libraries(${PROJECT_NAME} PocoNetSSL)
target_link_libraries(${PROJECT_NAME} PocoNet)

# For make install
install(TARGETS ${PROJECT_NAME} DESTINATION ${MYSQL_PLUGIN_DIR})
