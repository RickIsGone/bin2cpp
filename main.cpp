#include <string_view>

#include "funcs.hpp"
using namespace std::string_view_literals;

int main(int argc, char** argv) {
   if (argc >= 2) {
      fs::path outputDir{fs::current_path()};
      fs::path filePath{};

      for (int i = 1; i < argc; ++i) {
         if (argv[i] == "-h"sv || argv[i] == "--help"sv) {
            help();

         } else if (argv[i] == "-o"sv) {
            if (argc < i + 2 || (!fs::is_directory(argv[i + 1]) && !fs::is_directory(outputDir / argv[i + 1])))
               error(argc < i + 2 ? "no output directory provided" : "expected an output directory but got a file");
            else if (fs::is_directory(argv[i + 1]))
               outputDir = argv[++i];
            else
               error("output directory does not exist");

         } else
            filePath = argv[i];
      }

      if (filePath.empty())
         error("no file provided");
      else if (fs::exists(filePath) && !fs::is_directory(filePath))
         binToHeader(filePath, outputDir);
      else
         error(filePath.string() + (fs::is_directory(filePath) ? " is a directory" : " does not exist"));

   } else
      error("no file provided");

   return EXIT_SUCCESS;
}
