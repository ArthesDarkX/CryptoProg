#include <cryptopp/aes.h>
#include <cryptopp/sha.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/cryptlib.h>
#include <iostream>
#include <string>
#include <fstream>

int Encrypt(const std::string& path_input, const std::string& path_output, const std::string& password)
{
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::SecByteBlock salt(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH);
    
    CryptoPP::AutoSeededRandomPool rng;

    rng.GenerateBlock(iv, iv.size());
    rng.GenerateBlock(salt, salt.size());
    CryptoPP::PKCS12_PBKDF<CryptoPP::SHA256> obj;

    obj.DeriveKey(
        key,
        key.size(),
        0,
        reinterpret_cast<const CryptoPP::byte*> (password.data()),
        password.size(),
        salt.data(),
        salt.size(),
        200000,
        0
    );

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encrypt;

    encrypt.SetKeyWithIV(
        key.data(),
        key.size(),
        iv.data()
    );

    std::ofstream file(path_output, std::ios_base::binary | std::ios_base::trunc);
    if (!file.is_open())
    {
        std::cerr << "Произошла ошибка при открытии файла!\n";
        return 1;
    }

    file.write(
        reinterpret_cast<const char*>(salt.data()),
        static_cast<std::streamsize>(salt.size())
    );

    file.write(
        reinterpret_cast<const char*>(iv.data()),
        static_cast<std::streamsize>(iv.size())
    );

    CryptoPP::FileSource source(
        path_input.c_str(),
        true,
        new CryptoPP::StreamTransformationFilter(
            encrypt,
            new CryptoPP::FileSink(file)
        )
    );

    file.close();
    return 0;
}

int Decrypt(const std::string& path_input, const std::string& path_output, const std::string& password)
{
    std::ifstream file(path_input, std::ios_base::binary);
    if (!file.is_open())
    {
        std::cerr << "Произошла ошибка при чтении файла!\n";
        return 1;
    }
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::SecByteBlock salt(CryptoPP::AES::BLOCKSIZE);
    CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH);

    file.read(reinterpret_cast<char*>(salt.data()), salt.size());
    file.read(reinterpret_cast<char*>(iv.data()), iv.size());

    if (file.fail())
    {
        std::cerr << "Произошла ошибка при чтении данных!\n";
        return 1;
    }

    CryptoPP::PKCS12_PBKDF<CryptoPP::SHA256> obj;

    obj.DeriveKey(
        reinterpret_cast<CryptoPP::byte*>(key.data()),
        key.size(),
        0,
        reinterpret_cast<const CryptoPP::byte*>(password.data()),
        password.size(),
        reinterpret_cast<const CryptoPP::byte*>(salt.data()),
        salt.size(),
        200000,
        0        
    );

    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decrypt;

    decrypt.SetKeyWithIV(
        key.data(),
        key.size(),
        reinterpret_cast<const CryptoPP::byte*>(iv.data())
    );

    CryptoPP::FileSource source(
        file,
        true,
        new CryptoPP::StreamTransformationFilter(
            decrypt,
            new CryptoPP::FileSink(path_output.c_str())
        )
    );
    file.close();
    return 0;
}