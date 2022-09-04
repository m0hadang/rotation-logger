#include <rotation-logger.hh>
#include <iostream>

int main() {

  rotation_logger::RotLogger logger(5, 4);

  logger.init();

  for (int i = 0; i < 100000; ++i) {
    logger.add("new line");
  }

  logger.close();

  rotation_logger::Hello();
  std::cout << rotation_logger::Add(1, 2) << std::endl;
  return 0;
}