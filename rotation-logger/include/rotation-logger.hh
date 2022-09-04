#ifndef _ROT_LOGGER_H_
#define _ROT_LOGGER_H_

#include <util.hh>
#include <iostream>
#include <fstream>
#include <sstream>

namespace rotation_logger {

class RotLogger {

private:
  const std::string log_filename_;
  const std::string log_dirpath_;
  const size_t max_fileline_;
  const size_t backup_filecount_;
  std::ofstream log_file_;
  size_t last_line_number_;
  const std::string filepath_;
  const std::string tag_;
  const std::string fileext_;
  const FileNameInfo file_name_info_;
public:
  RotLogger(
    std::string log_dir_path, 
    size_t max_file_line,
    size_t backup_file_count) 
    : log_dirpath_(log_dir_path), 
      max_fileline_(max_file_line),
      backup_filecount_(backup_file_count),
      last_line_number_(0),
      tag_("log-file"),
      fileext_("log"),
      log_filename_("log-file.log"),
      filepath_(path_combine(log_dirpath_, log_filename_)),
      file_name_info_({tag_, fileext_})      
  {
  }
  virtual ~RotLogger() {
    close();  
  }

  bool init() {

    last_line_number_ = get_last_line_number();
    
    if (last_line_number_ > max_fileline_) {
      last_line_number_ = 0;
    }

    if (std::filesystem::exists(log_dirpath_) == false) {
      if (std::filesystem::create_directories(log_dirpath_) == false) {
        return false;
      }
    }

    log_file_.open(
      filepath_,
      std::fstream::out | std::fstream::app);
    if (log_file_.is_open() == false) {
      return false;
    }

    return true;
  }

  void log(const std::string &log_line) {
    if (last_line_number_ >= max_fileline_) {
      log_file_.close();
      push_log_file();
      init();
    }
    append_log_line(log_line);
    ++last_line_number_;
  }
  void close() {
    log_file_.close();
  }

private:
  size_t get_last_line_number() { 
    std::ifstream fin(filepath_);
    size_t count = 0;
    for(std::string line; getline(fin, line); ) {
      count++;
    }
    return count;
  }

  void push_log_file() noexcept {
    std::string src;
    std::string dst;
    for(size_t i = find_last_file_index(); i > 0; i--) {
      if(i == backup_filecount_) {
        continue; 
      }

      src = get_index_filepath(log_dirpath_, file_name_info_, i);
      dst = get_index_filepath(log_dirpath_, file_name_info_, i + 1);
      std::remove(dst.c_str());
      std::rename(src.c_str(), dst.c_str());
    }

    dst = get_index_filepath(log_dirpath_, file_name_info_, 1);
    std::remove(dst.c_str());
    std::rename(filepath_.c_str(), dst.c_str());
    last_line_number_ = 0;
  }
  void append_log_line(const std::string& log_line) {
    log_file_ << log_line;
  }
  size_t find_last_file_index() {
    size_t idx = 0;
    for (const auto &entry : std::filesystem::directory_iterator(log_dirpath_)) {
      std::string target_file_name = entry.path().filename();
      if (target_file_name.find(tag_) == std::string::npos || 
          target_file_name == log_filename_) {
        continue;
      }
      idx = get_index_from_filename(target_file_name, file_name_info_);
    }

    return idx;
  }
};

} // namespace rotation_logger

#endif