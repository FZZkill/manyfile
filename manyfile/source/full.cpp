#include "full.hpp"
#include "files.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <regex>

void manyfile::call(manyfile::option opt)
{
  opt.re = std::regex(opt.re_s, opt.match_type);
  Files f(opt.source.path, opt.re);
  auto l = f.getFiles();
  if (opt.outcome.STDOUT)
  {
    for (auto &var : l)
    {
      std::cout << var << "\n";
    }
    std::cout << std::endl;
  } else
  {
    std::ofstream f(opt.outcome.path, std::ios::app | std::ios::out);
    for (auto &var : l)
    {
      f << var << "\n";
    }
    f << std::endl;
  }

}
