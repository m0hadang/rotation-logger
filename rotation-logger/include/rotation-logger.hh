#ifndef _ROT_LOGGER_H_
#define _ROT_LOGGER_H_

#include <iostream>

namespace rotation_logger {

class RotLogger {
private:
  size_t file_line_;
  size_t backup_file_count_;
public:
  RotLogger(
    size_t file_line, 
    size_t backup_file_count) :
    file_line_(file_line), 
    backup_file_count_(backup_file_count)
  {}

  void init() {

  }

  void add(const std::string& str) {

  }

  void close() {

  }
};

void Hello();
int Add(int a, int b);

}

#endif