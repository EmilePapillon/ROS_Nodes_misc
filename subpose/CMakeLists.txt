cmake_minimum_required(VERSION 2.8.3)
project(subpose)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)


find_package(catkin REQUIRED)
find_package(catkin REQUIRED COMPONENTS roscpp turtlesim)


catkin_package()


include_directories(
# include
${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node subpose.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)