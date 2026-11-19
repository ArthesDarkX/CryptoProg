#include <cctype>
#include <cryptopp/cryptlib.h>
#include <iostream>
#include <string>

#include "cipher.h"
#include "interface.h"

int main(int argc, char** argv)
{
    std::string path;
    std::string result;
    std::string password;
    std::string mode;
    parse(argc, argv, path, result, password, mode);
    for (auto& ch : mode)
    {
        ch = std::tolower(static_cast<unsigned char>(ch));
    }
    try
    {
        if (mode == "encrypt")
        {
            Encrypt(path, result, password);
        }
        if (mode == "decrypt")
        {
            Decrypt(path, result, password);
        }
    }
    catch (const CryptoPP::Exception& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << '\n';
        return 1;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << '\n';
        print_help();
    }
    return 0;
}