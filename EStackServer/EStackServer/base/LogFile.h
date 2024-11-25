// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_LOGFILE_H
#define MUDUO_BASE_LOGFILE_H

#include "Mutex.h"
#include "Types.h"

#include <memory>

namespace muduo
{

namespace FileUtil
{
class AppendFile;
}

class LogFile : noncopyable
{
 public:
  LogFile(const string& basename,
          off_t rollSize,
          bool threadSafe = true,
          int flushInterval = 3,
          int checkEveryN = 1024);
  ~LogFile();

  void append(const char* logline, int len);
  void flush();
  bool rollFile();

 private:
  void append_unlocked(const char* logline, int len);

  static string getLogFileName(const string& basename, time_t* now);

  const string basename_;       //日志名
  const off_t rollSize_;        //偏移大小
  const int flushInterval_;     //刷新间隔
  const int checkEveryN_;       //检查间隔

  int count_;                   //计数

  std::unique_ptr<MutexLock> mutex_; //互斥锁
  time_t startOfPeriod_;             //开始周期
  time_t lastRoll_;                  //最后一次移动
  time_t lastFlush_;                 //最后一次刷新
  std::unique_ptr<FileUtil::AppendFile> file_; //文件指针

  const static int kRollPerSeconds_ = 60*60*24;
};

}  // namespace muduo
#endif  // MUDUO_BASE_LOGFILE_H
