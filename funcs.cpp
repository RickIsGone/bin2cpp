#include <fstream>

#include "funcs.hpp"
namespace fs = std::filesystem;

void imgToHpp(const fs::path& img) {
   std::ifstream image{img, std::ios::binary | std::ios::ate};
   std::ofstream header{img.string().substr(0, img.string().find_last_of('.')) + ".hpp"};
   size_t length = image.tellg();
   image.seekg(0);

   header << "#pragma once\n\n"
          << "/**\n"
          << " * file generated with img2cpp\n"
          << " * Copyright (C) 2024\n"
          << " * Riccardo Tedeschi\n"
          << " * https://github.com/rickisgone/img2cpp\n"
          << " */\n\n";

   header << "constexpr unsigned char " + img.string().substr(0, img.string().find_last_of('.')) + "[0x" << std::hex << length + 1 << "] = {\n\t ";

   unsigned char pixel;
   while (image.read(reinterpret_cast<char*>(&pixel), sizeof(unsigned char))) {
      header << "0x" << std::hex << int(pixel) << (image.tellg() != length ? ", " : ", 0x00");
   }
   header << "};\n";
}