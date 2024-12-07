#include <fstream>
#include <iostream>
#include <format>

#include "funcs.hpp"

#define RED    "\x1B[91m"
#define RESET  "\x1B[0m"

void imgToHeader(const fs::path& img) {
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
   size_t position = 0;
   while (image.read(reinterpret_cast<char*>(&pixel), sizeof(unsigned char))) { // same as doing sizeof(char)
      header << "0x" << std::hex << int(pixel) << (++position != length ? ", " : ", 0x00");
   }
   header << "};\n";
}

void error(std::string_view err) {
   std::cerr << RED "error: " RESET << err << '\n';
}