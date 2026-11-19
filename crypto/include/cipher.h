#pragma once
#include <string>

int Encrypt(const std::string& path_input, const std::string& path_output, const std::string& password);
int Decrypt(const std::string& path_input, const std::string& path_output, const std::string& password);