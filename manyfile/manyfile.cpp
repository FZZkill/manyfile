#include "include/line.hpp"
#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>

void p(const std::vector<std::string> &v)
{
  using namespace std;
  for (auto &var : v)
  {
    cout << var << "\n";
  }
  cout << endl;
}

int main(int argc, char *argv[])
{
  manyfile::mfiles *f;
  if (argc == 1)
  {
    f = new manyfile::mfiles("", std::regex(".*"));  // FIXME: This application
                                                     // will cause abrt if it run this
                                                     // line.
  }
  if(argc == 2) {
    f = new manyfile::mfiles(argv[1], std::regex(".*"));
  }
  else {
    f = new manyfile::mfiles(argv[1], std::regex(argv[2]));
  }
  p(f->getFiles());
  delete f;

  return EXIT_SUCCESS;
}
