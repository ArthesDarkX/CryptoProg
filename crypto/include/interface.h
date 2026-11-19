#pragma once
#include <getopt.h>
#include <string>

extern const struct option long_options[];

void help();

bool parse(
    int argc, char* argv[],
    std::string& path_input, std::string& path_output,
    std::string& password, std::string& mode
);