#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::string result;    

    CryptoPP::SHA256 hash;

    CryptoPP::FileSource source(
        "test.txt",
        true,
        new CryptoPP::HashFilter(
            hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(result)
            )
        )
    );

    std::cout << result << '\n';
    return 0;
}