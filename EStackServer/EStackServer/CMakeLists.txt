# CMakeList.txt: EdoyumIMServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
# //
cmake_minimum_required (VERSION 3.8)

project(EdoyunServer)

# #设置C++标准为C++17
# set(CMAKE_CXX_STANDARD 17)

#这个宏，会影响编译参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -O0 -Wno-unused-variable -pthread")

#设置库目录
link_directories(# 针对64位的
	${PROJECT_SOURCE_DIR}/lib
	/usr/lib64/mysql/
)

find_library(MYSQL_LIB libmysqlclient.so /usr/lib64/mysql/)
if (NOT MYSQL_LIB)#NOT 只能用大写
	message(FATAL_ERROR "not found mysqlclient.so at lib64")
endif(NOT MYSQL_LIB)#必须进行匹配，否则会报错

include_directories(. ./base ./net)

# set(MUDUO_SRCS,
# "base/Timestamp.cc"
# "base/Timestamp.h"
# )

set(MUDUO_SRCS 
"base/Timestamp.cc"
"base/CountDownLatch.cc"
"base/CurrentThread.cc"
"base/FileUtil.cc"
"base/Logging.cc"
"base/LogFile.cc"
"base/LogStream.cc"
"base/AsyncLogging.cc"
"base/Thread.cc"
"base/TimeZone.cc"
"base/Condition.cc"
"base/Date.cc"
"base/ProcessInfo.cc"
"net/Acceptor.cc"
"net/Buffer.cc"
"net/Channel.cc"
"net/Connector.cc"
"net/Poller.cc"
"net/EventLoop.cc"
"net/poller/DefaultPoller.cc"
"net/poller/EPollPoller.cc"
"net/poller/PollPoller.cc"
"net/InetAddress.cc"
"net/Socket.cc"
"net/SocketsOps.cc"
"net/Timer.cc"
"net/TimerQueue.cc"
"net/TcpConnection.cc"
"net/TcpServer.cc"
"net/TcpClient.cc"
"net/EventLoop.cc"
"net/EventLoopThread.cc"
"net/EventLoopThreadPool.cc"
)

set(MYSQL_SRCS
"mysqltool.cpp"
"Field.cpp"
"QueryResult.cpp"
"MySqlManager.cpp"
"UserManager.cpp"
"BinaryReader.cpp"
)

set(CHAR_SRCS
"EStackServer.cpp"
"IMServer.cpp"
"ClientSession.cpp"
)

set(FILE_SRCS
"EStackTestClient.cpp")

set(JSON_SRCS
"json/json_reader.cpp"
"json/json_value.cpp"
"json/json_writer.cpp"
)

# 将源代码添加到此项目的可执行文件。
add_executable (easyStackserver  ${MUDUO_SRCS} ${CHAR_SRCS} ${MYSQL_SRCS} ${JSON_SRCS})
#只是确认库存在或者设置库目录，是没有用的，需要链接进来才能起效果
target_link_libraries(easyStackserver mysqlclient)

# 将源代码添加到此项目的可执行文件。
add_executable (imfileserver  ${MUDUO_SRCS} ${FILE_SRCS})
#只是确认库存在或者设置库目录，是没有用的，需要链接进来才能起效果
target_link_libraries(imfileserver)
# TODO: 如有需要，请添加测试并安装目标。
