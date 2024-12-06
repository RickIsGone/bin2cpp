#include <iostream>

#include "funcs.hpp"

int main(int argc, char** argv) {
   if (argc >= 2) {
      for (int i = 1; i < argc; ++i) {
         if (std::filesystem::exists(argv[i]))
            imgToHpp(argv[i]);
         else
            std::cout << "\x1B[91merror:\x1B[0m " << argv[i] << "does not exist";
      }
   }

   return EXIT_SUCCESS;
}