#include <fstream>
#include <iostream>

#include "funcs.hpp"

#define RED   "\x1B[91m"
#define RESET "\x1B[0m"

void binToHeader(const fs::path& filePath, const fs::path& outputDir) {
   std::ifstream binaryFile{filePath, std::ios::binary | std::ios::ate};
   std::ofstream header{outputDir / (filePath.string().substr(0, filePath.string().find_last_of('.')) + ".hpp")};
   size_t length = binaryFile.tellg();
   binaryFile.seekg(0);

   header << "#pragma once\n\n"
          << "/**\n"
          << " * file generated with bin2cpp\n"
          << " * Copyright (C) 2024\n"
          << " * Riccardo Tedeschi\n"
          << " * https://github.com/rickisgone/bin2cpp\n"
          << " */\n\n";

   // looking for / and \ in the path and setting an offset so the variable wont have illegal chars in the name
   size_t offset = filePath.string().find_last_of('\\') == std::string::npos ? 0 : filePath.string().find_last_of('\\') + 1;
   if (offset == 0) offset = filePath.string().find_last_of('/') == std::string::npos ? offset : filePath.string().find_last_of('/') + 1;

   header << "constexpr unsigned char " + filePath.string().substr(offset, filePath.string().find_first_of('.') - offset) + "[0x" << std::hex << std::uppercase << length + 1 << "]{\n\t";

   unsigned char pixel;
   size_t position = 0;
   while (binaryFile.read(reinterpret_cast<char*>(&pixel), sizeof(unsigned char))) { // same as doing sizeof(char)
      header << "0x" << std::hex << std::uppercase << static_cast<int>(pixel) << (++position != length ? ", " : ", 0x00");
   }
   header << "};\n";
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