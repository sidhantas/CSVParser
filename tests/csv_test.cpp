#include "csv.h"
#include <optional>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <gtest/gtest.h>

/*
test1.csv:
a, b, c, d, e, f

nonexistantfile:
*this file should not exist in the tests directory*
*/

class CSVTest : public ::testing::Test
{
protected:
    CSVReader csv = CSVReader::open("test1.csv");
    CSVReader badcsv = CSVReader::open("nonexistantfile.csv");
};

TEST_F(CSVTest, OpenCSVFile)
{
    EXPECT_TRUE(bool(csv)) << "Error Opening CSV File";
}

TEST_F(CSVTest, CSVGetRow)
{
    auto row = csv.get_row();
    EXPECT_TRUE(bool(row)) << "Error getting row from CSV";
}

TEST_F(CSVTest, CSVSplitRow)
{
    auto row = csv.get_row();
    EXPECT_EQ(row.value().size(), 6) << "Incorrect number of columns in first row";
}

TEST_F(CSVTest, NoFile)
{
    EXPECT_FALSE(bool(badcsv)) << "Opened a file that doesn't or should not exist";
}

TEST_F(CSVTest, ErrorOnNoMoreLines)
{
    // After only row is fetched get_row should return std::nullopt
    // which implicitly converts to false
    csv.get_row();
    EXPECT_FALSE(bool(csv.get_row()))
        << "Got a row when there shouldn't be anymore rows left";
}