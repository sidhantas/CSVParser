#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <optional>

class CSVReader
{
    std::vector<std::string> split_row(std::string str);
    std::string filename;
    std::ifstream csv_file;
    CSVReader();

public:
    size_t rows_read;
    static CSVReader open(std::string filename);
    operator bool();
    std::optional<std::vector<std::string>> get_row();
    bool is_open();
};