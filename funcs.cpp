#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <WinSock.h>
#elif defined(__linux__)
#include <arpa/inet.h>
#endif // defined(_WIN32)

#include "funcs.hpp"

#define RED   "\x1B[91m"
#define RESET "\x1B[0m"

// TODO: add jpg support
std::string getImageSize(std::ifstream& image) {
   size_t width, height;

   image.seekg(16);
   image.read(reinterpret_cast<char*>(&width), 4);
   image.read(reinterpret_cast<char*>(&height), 4);

   width = ntohl(width);
   height = ntohl(height);
   return std::to_string(width) + "x" + std::to_string(height);
}

void binToHeader(const fs::path& filePath, const fs::path& outputDir) {
   std::ifstream binaryFile{filePath, std::ios::binary | std::ios::ate};
   std::ofstream header{outputDir / (filePath.stem().string() + ".hpp")};
   size_t length = binaryFile.tellg();
   std::string extension = filePath.extension().string();

   header << "#pragma once\n\n"
          << "/**\n"
          << " * file generated with bin2cpp\n"
          << " * https://github.com/rickisgone/bin2cpp\n"
          << " *\n"
          << " * file extension: " << (filePath.has_extension() ? extension.substr(1) : "none") << '\n'
          << (extension == ".png" ? " * img size: " + getImageSize(binaryFile) + '\n' : "") //  (|| extension == ".jpg" || extension == ".jpeg")
          << " */\n\n";

   binaryFile.seekg(0);

   // changing every - to _ in the file name so it can be used as a variable name
   std::string fileName = filePath.filename().string();
   for (size_t i = 0; i < filePath.string().find_first_of('.'); ++i) {
      if (fileName[i] == '-')
         fileName[i] = '_';
   }
   header << "constexpr unsigned char " + fileName.substr(0, fileName.find_first_of('.')) + "[0x" << std::hex << std::uppercase << length << "]{\n\t";

   std::vector<unsigned char> pixels(length);
   binaryFile.read(reinterpret_cast<char*>(pixels.data()), sizeof(unsigned char) * length); // same as doing sizeof(char) * length
   for (size_t i = 0; unsigned char pixel : pixels) {
      header << "0x" << std::hex << std::uppercase << static_cast<int>(pixel) << (i++ != pixels.size() - 1 ? ", " : "};\n");
   }
}

void error(std::string_view err) {
   std::cerr << RED "error: " RESET << err << '\n';
   exit(EXIT_FAILURE);
}

void help() {
   std::cout << "Usage: bin2cpp <file> [options]\n"
             << "Options:\n"
             << "\t-o <dir>    output directory\n"
             << "\t-h, --help  display usage\n\n";

   exit(EXIT_SUCCESS);
}