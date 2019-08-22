cmake_minimum_required(VERSION 2.8.3)
project(hkcamera_bridge)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  sensor_msgs
  roscpp
  geometry_msgs
  genmsg
  message_generation
)

#find_package(hirop_vision REQUIRED)
set(HKcamera_root /home/de/data/MVS-1.0.0_x86_64/MVS/Samples/64/test/Trigger_Image_lib)

add_service_files(
  FILES
  # detection.srv
  # listDetector.srv
  #listObject.srv
  #train.srv
  getImageData.srv
  HkCameraData.srv
)

add_message_files(
  FILES
  #Image_data.msg
  #ObjectInfo.msg
  #ObjectArray.msg
)

generate_messages(DEPENDENCIES geometry_msgs)

#generate_messages(DEPENDENCIES genmsg)

catkin_package(
  CATKIN_DEPENDS roscpp cv_bridge
)

add_definitions(-D__LINUX__)

include_directories(
  ${HKcamera_root}
  include/HkCamera
  include
  # ${hirop_vision_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)
link_directories(hkcamera_bridge /home/de/data/MVS-1.0.0_x86_64/MVS/Samples/64/test/build)
add_executable(hkcamera_bridge src/main.cpp src/hkcamera_bridge.cpp)

## 当工程以来与工程内自身的消息或服务时，需添加以下内容
add_dependencies(hkcamera_bridge ${hkcamera_bridge_EXPORTED_TARGETS})

target_link_libraries(hkcamera_bridge
   #${hirop_vision_LIBRARIES}
   ${catkin_LIBRARIES}
   HkCameraHandler
 )
