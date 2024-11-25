# Install script for directory: /home/wangtao/easy_server/EStackServer/EStackServer/net

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/libmuduo_net.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/CMakeFiles/muduo_net.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/net" TYPE FILE FILES
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/Buffer.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/Callbacks.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/Channel.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/Endian.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/EventLoop.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/EventLoopThread.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/EventLoopThreadPool.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/InetAddress.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/TcpClient.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/TcpConnection.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/TcpServer.h"
    "/home/wangtao/easy_server/EStackServer/EStackServer/net/TimerId.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/http/cmake_install.cmake")
  include("/home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/inspect/cmake_install.cmake")
  include("/home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/tests/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
