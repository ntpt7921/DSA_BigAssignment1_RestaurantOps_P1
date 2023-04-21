#include "main.h"

void simulate(string filename, restaurant *r);

int main(int argc, char *argv[]) {

  restaurant *r = new restaurant();

  try {
    for (int i = 1; i < argc; i++) {
      std::string fileName(argv[i]);
      simulate(fileName, r);
    }
  } catch (const char *message) {
    std::cout << message << std::endl;
  }

  delete r;

  return 0;
}
