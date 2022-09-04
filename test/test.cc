#include <fstream>
#include <gtest/gtest.h>
#include <util.hh>

TEST(SANDBOX_TEST, write_file) {
  // write File
  std::ofstream file;
  file.open("test_sandbox/test_log_file.log");
  if (file.is_open()) {
    file << "111111111!\n";
    file << "This is C++ File Contents.\n";
    file.close();
  }

  file.open("test_sandbox/test_log_file2.log",
            std::fstream::out | std::fstream::app);
  if (file.is_open()) {
    file << "2222222!\n";
    file.close();
  }

  EXPECT_TRUE(true);
}

TEST(SANDBOX_TEST, create_directory) {
  std::filesystem::create_directories("./test_sandbox/1/2/");
  EXPECT_TRUE(true);
}

TEST(SANDBOX_TEST, directory_listing) {
  std::string path = ".";
  for (const auto &entry : std::filesystem::directory_iterator(path)) {
    // std::cout << entry.path() << std::endl;
    std::cout << entry.path().filename() << std::endl;
  }
  EXPECT_TRUE(true);
}

TEST(UTIL_TEST, path_combine) {
#ifdef _WIN32
  std::string file_path =
      rotation_logger::path_combine("\\home\\user\\test", "file.txt");
  EXPECT_EQ(file_path, "\\home\\user\\test\\file.txt");
#elseif
  std::string file_path =
      rotation_logger::path_combine("/home/user/test", "file.txt");
  EXPECT_EQ(file_path, "/home/user/test/file.txt");
#endif
}

TEST(UTIL_TEST, get_index_filename) {

  rotation_logger::FileNameInfo file_name_info{"tag", "txt"};

  EXPECT_EQ(rotation_logger::get_index_filename(file_name_info, 0), "tag0.txt");
  EXPECT_EQ(rotation_logger::get_index_filename(file_name_info, 1), "tag1.txt");
  EXPECT_EQ(rotation_logger::get_index_filename(file_name_info, 12), "tag12.txt");
}

TEST(UTIL_TEST, get_index_filepath) {

  std::string dir_path = "C://workspace/test";
  rotation_logger::FileNameInfo file_name_info{"tag", "txt"};
  EXPECT_EQ(
    rotation_logger::get_index_filepath(dir_path, file_name_info, 0), 
    "C://workspace/test/tag0.txt");
  EXPECT_EQ(
    rotation_logger::get_index_filepath(dir_path, file_name_info, 1), 
    "C://workspace/test/tag1.txt");
  EXPECT_EQ(
    rotation_logger::get_index_filepath(dir_path, file_name_info, 12), 
    "C://workspace/test/tag12.txt");
}

TEST(UTIL_TEST, get_index_from_filename) {

  rotation_logger::FileNameInfo file_name_info{"tag", "txt"};
  EXPECT_EQ(
    get_index_from_filename("tag0.txt", file_name_info), 0);
  EXPECT_EQ(
    get_index_from_filename("tag1.txt", file_name_info), 1);
  EXPECT_EQ(
    get_index_from_filename("tag12.txt", file_name_info), 12);
}