#include <cctype>
#include <iostream>
#include <getopt.h>
#include <string>

const struct option long_options[] = {
    {"file", required_argument, nullptr, 'f'},
    {"result", required_argument, nullptr, 'r'},
    {"password", required_argument, nullptr, 'p'},
    {"mode", required_argument, nullptr, 'm'},
    {"help", no_argument, nullptr, 'h'},
    {0, 0, 0, 0}
};

void toLower(std::string& mode)
{
    for (auto& ch : mode)
    {
        ch = std::tolower(ch);
    }
}

void print_help()
{
    std::cout << "Использование: ./cipher [опции]\n\n"
              << "Описание:\n"
              << "  Утилита для шифрования и дешифрования файлов.\n\n"
              << "Аргументы:\n"
              << "  -f, --file <path>       Путь к исходному файлу для загрузки.\n"
              << "  -r, --result <path>     Путь к файлу, куда сохранить результат.\n"
              << "  -p, --password <pass>   Пароль для работы с шифрованием.\n"
              << "  -m, --mode <type>       Режим работы. Допустимые значения: {Encrypt, Decrypt}\n\n"
              << "  -h, --help              Показать справку.\n"
              << "Пример использования:\n"
              << "  ./cipher -f input.txt -p password --mode Encrypt -r output.txt\n"
              << std::endl;
}

bool parse(
    int argc, char* argv[],
    std::string& path_input, std::string& path_output,
    std::string& password, std::string& mode
)
{
    if (argc == 1)
    {
        print_help();
        return 1;
    }
    int opt;
    while ((opt = getopt_long(argc, argv, "hf:r:p:m:", long_options, nullptr)) != -1)
    {
        switch (opt)
        {
        case 'f':
            path_input = optarg;
            break;
        case 'r':
            path_output = optarg;
            break;
        case 'p':
            password = optarg;
            break;
        case 'm':
            mode = optarg;
            toLower(mode);
            break;
        case 'h':
            print_help();
            break;
        case '?':
            std::cerr << "Введена неизвестная опция!\n"
            << "Пропишите -h(--help) для вывода справки\n";
            break;
        }
    }
    return true;
}
