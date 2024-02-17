#include "../include/line.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <utility>
#include <vector>

/*
 * @pargm dire : It must has exist.
 * @pargm re : Regular expression handles.
 * @return : Number of all compliant files.
 *
 * Note: This function is called recursively.
 * */
manyfile::Files::Files(std::string directory, std::regex re)
    : entry(std::filesystem::directory_entry(directory)), directory(directory),
      re(std::move(re))
{
  this->manyfile(this->entry);
}

manyfile::Files::Files(std::filesystem::directory_entry entry, std::regex re)
    : directory(entry.path().filename()), re(std::move(re)), entry(entry)
{
  this->manyfile(this->entry);
}

/*
 * @pargm dire : It must has exist.
 * @pargm re : Regular expression handles.
 * @return : Number of all compliant files.
 *
 * Note: This function is called recursively.
 * */
void manyfile::Files::manyfile(std::filesystem::directory_entry entry)
{
  using namespace std::filesystem;
  if (entry.status().type() == file_type::regular)
  {
    if (std::regex_match(entry.path().filename().string(), this->re))
    {
      this->manyFiles++;
      this->lfiles.emplace_back(entry.path().string());
    }
  }
  else if (entry.status().type() == file_type::directory)
  {
    directory_iterator iterator(entry);
    for (auto &var : iterator)
    {
      // if (var.status().type() == file_type::regular &&
      //     std::regex_match(var.path().filename().string(), this->re)) //
      //     Match!
      //   this->files++;
      // else if (var.status().type() == file_type::directory)
      this->manyfile(var);
    }
  }
}

unsigned int f(std::string filename)
{
  unsigned int ui = 0; std::string s;
  std::ifstream f(filename);
  while (getline(f, s)) {
    for(auto &var : s) {
      if (var != ' ' && var != '\n' && var != '\r'){
        ui++;
        continue;
      }
    }
  }
  f.close();
  return ui;
}
