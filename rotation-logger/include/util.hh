#include <filesystem>
#include <vector>
#include <string.h>

#include <iostream>

namespace rotation_logger {

inline std::string path_combine(
  const std::string& dir_path, 
  const std::string& file_name) {
  std::filesystem::path dir(dir_path);
  std::filesystem::path file(file_name);
  std::filesystem::path full_path = dir / file;
  return full_path;
}

struct FileNameInfo {
  std::string tag;
  std::string fileext;  
};

inline std::string get_index_filename(
  const FileNameInfo& file_name_info,
  size_t idx) noexcept {
  std::stringstream stm;
  stm << 
    file_name_info.tag << 
    idx << 
    "." << 
    file_name_info.fileext;

  return stm.str();
}

inline std::string get_index_filepath(
  const std::string& log_dir_path,
  const FileNameInfo& file_name_info,
  size_t idx) noexcept {
  return path_combine(
    log_dir_path, 
    get_index_filename(file_name_info, idx));
}

inline int32_t get_index_from_filename(
  const std::string& filename,
  const FileNameInfo& file_name_info) noexcept {
  int32_t idx = -1;
  std::string idx_str = 
    filename.substr(file_name_info.tag.size());
  
  idx_str = 
    idx_str.substr(0, idx_str.size() - file_name_info.fileext.size() - 1);

  try {
    int temp = std::stoi(idx_str);
    if (idx < temp) {
      idx = temp;
    }
  } catch (const std::exception &e) {
    idx = -1;
  }
  return idx;
}

}