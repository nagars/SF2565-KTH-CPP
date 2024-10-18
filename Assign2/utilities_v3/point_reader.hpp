// Author: Bjorn Wehlin

#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>

namespace sf
{
  /*
    Read point CSV file, with ' ' as delimiter. The file should contain two
    columns: x and y, with no header.

    -- Example file:
    1.012 2.254
    5.287 8.101
    7.111 3.142
    -- End of example file

    The user's PointT class must have .x and .y as public member variables,
    and PointTs should be both default-constructible as well as constructible
    with (x, y) as arguments.
  
    Usage:

    auto points = sf::readCsvPoints("swelakes.csv"); // auto type is std::vector<PointT>

  */

  template <typename PointT>
  inline std::vector<PointT>
    readCsvPoints(const std::string& filename)
  {
    std::vector<PointT> points;

    std::ifstream file(filename);
    if (!file.is_open() || !file.good())
    {
      throw std::runtime_error("Unable to read file");
    }

    std::string line;
    long numRecords = 0;
    PointT pt;

    while (std::getline(file, line))
    {
      auto delimPos = line.find(' ');
      if (delimPos == std::string::npos)
      {
        throw std::runtime_error("File format error on line " + std::to_string(numRecords + 1)
          + "! (each line should contain two floating-point numbers separated by a space)");
      }

      pt.x = std::stod(line.substr(0, delimPos));
      pt.y = std::stod(line.substr(delimPos));

      points.emplace_back(pt);

      if (numRecords > 0 && numRecords % 1000 == 0)
      {
        std::cout << "Read " << numRecords << "record(s)\n";
      }
      ++numRecords;
    }

    return points;
  }
}