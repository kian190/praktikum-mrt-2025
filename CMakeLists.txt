
cmake_minimum_required(VERSION 3.0.2)
project(my_first_project)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  nav_msgs
  volksbot
  tf
)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(odo_nodeGNU src/odo_nodeGNU.cpp)
target_link_libraries(odo_nodeGNU ${catkin_LIBRARIES})

add_library(gio_path src/gio_path.cpp)
target_link_libraries(gio_path ${catkin_LIBRARIES})

add_executable(gio_node src/gio_node.cpp)
target_link_libraries(gio_node gio_path ${catkin_LIBRARIES})

add_executable(amcl_nodeGNU src/amcl_nodeGNU.cpp)
target_link_libraries(amcl_nodeGNU ${catkin_LIBRARIES})

