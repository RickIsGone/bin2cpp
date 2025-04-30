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

   header << "constexpr unsigned char " + filePath.stem().string() + "[0x" << std::hex << std::uppercase << length + 1 << "]{\n\t";
   std::vector<unsigned char> pixels(length);
   binaryFile.read(reinterpret_cast<char*>(pixels.data()), sizeof(unsigned char) * length); // same as doing sizeof(char) * length
   for (unsigned char pixel : pixels) {
      header << "0x" << std::hex << std::uppercase << static_cast<int>(pixel) << ", ";
   }
   header << "0x00};\n";
}

void error(std::string_view err) {
   std::cerr << RED "error: " RESET << err << '\n';
   exit(EXIT_FAILURE);
}

void help() {
   std::cout << "Usage: bin2cpp [options] <file>\n"
             << "Options:\n"
             << "\t-o <dir>    output directory\n"
             << "\t-h, --help  display usage\n\n";

   exit(EXIT_SUCCESS);
}