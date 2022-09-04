#include <rotation-logger.hh>
#include <iostream>

int main() {

  rotation_logger::RotLogger logger(
    "test_sandbox/logger", 5, 4);
  logger.init();
  for (int i = 0; i < 100; ++i) {
    std::stringstream stm;
    stm << "line : " << i << std::endl;
    logger.log(stm.str());
  }

  logger.close();
  
  return 0;
}