#include "argument.hpp"
#include "files.hpp"
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
  manyfile::argument::CommandOption<manyfile::option> o(argc, argv,
                                                        manyfile::doption);

  // TODO: Register all argument
  o.registerArg({"T", "t", true,
                 [](manyfile::option &opt, std::string_view) {
                   std::cout << "Done" << std::endl;
                 },
                 []() {}})
      .run([](const manyfile::option &l, const manyfile::option &d) {
        std::cout << "OK" << std::endl;
        return manyfile::doption;
      });

  // manyfile::Files *f;
  // if (argc == 1)
  // {
  //   f = new manyfile::Files("", std::regex(".*")); // FIXME: This application
  //                                                  // will cause abrt if it
  //                                                  run
  //                                                  // this line.
  // }
  // if (argc == 2)
  // {
  //   f = new manyfile::Files(argv[1], std::regex(".*"));
  // }
  // else
  // {
  //   f = new manyfile::Files(argv[1], std::regex(argv[2]));
  // }
  // p(f->getFiles());
  // delete f;

  return EXIT_SUCCESS;
}
