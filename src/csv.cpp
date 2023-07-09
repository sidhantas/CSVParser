#include <string>
#include <vector>
#include <fstream>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <optional>
#include <limits>
#include "csv.h"

#define ROW_READ_SIZE 20

std::vector<std::string> CSVReader::split_row(std::string str)
{
    size_t slice_start{};
    const char delimiter = ',';
    bool escaped = false;
    std::vector<std::string> slices{};

    for (int i = 0; i <= str.length(); i++)
    {
        if (str[i] == '"')
        {
            escaped = !escaped;
        }
        else if (str[i] == delimiter && !escaped)
        {
            slices.push_back(str.substr(slice_start, i - slice_start));
            slice_start = i + 1;
        }
        else if (i == str.length() && str[i - 1] != ',')
        {
            slices.push_back(str.substr(slice_start, i - slice_start));
            slice_start = i + 1;
        }
    }
    return slices;
}

CSVReader CSVReader::open(std::string filename)
{
    CSVReader csv = CSVReader();
    csv.csv_file = std::ifstream(filename);
    if (!csv.csv_file)
    {
        return CSVReader();
    }
    csv.filename = filename;
    return csv;
}

std::optional<std::vector<std::string>> CSVReader::get_row()
{
    std::string line{};
    if (!getline(csv_file, line))
    {
        return std::nullopt;
    };
    std::unordered_map<std::string, std::string> mapped_row{};
    std::vector<std::string> row = split_row(line);
    rows_read++;
    return row;
}

CSVReader::CSVReader()
{
    rows_read = 0;
}

CSVReader::operator bool()
{
    return filename.size();
}