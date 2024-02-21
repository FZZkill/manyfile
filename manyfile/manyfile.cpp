#include "argument.hpp"
#include "files.hpp"
#include "full.hpp"
#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>

#define l(obj, reg)                                                            \
  if (str == obj)                                                              \
  {                                                                            \
    opt.match_type = std::regex_constants::reg;                                \
    return true;                                                               \
  }
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

  o.registerArg({"path", "p", true,
                 [](manyfile::option &opt, std::string str) {
                   opt.source.path = str;
                   return true;
                 }})
      .registerArg({"regex", "r", true,
                    [](manyfile::option &opt, std::string str) {
                      l("icase", _S_icase);
                      l("nosubs", _S_nosubs);
                      l("optimize", _S_optimize);
                      l("collate", _S_collate);
                      l("ECMAScript", _S_ECMAScript);
                      l("basic", _S_basic);
                      l("extended", _S_extended);
                      l("awk", _S_awk);
                      l("grep", _S_grep);
                      l("egrep", _S_egrep);
                      l("polynomial", _S_polynomial);
                      l("multiline", _S_multiline);
                      return false;
                    }})
      .registerArg({"expression", "e", true,
                    [](manyfile::option &opt, std::string str) {
                      opt.re_s = str;
                      return true;
                    }})
      .registerArg({"input", "i", false,
                    [](manyfile::option &opt, std::string str) {
                      opt.source.STDIN = true;
                      return true;
                    }})
      .registerArg({"output", "o", true,
                    [](manyfile::option &opt, std::string str) {
                      opt.outcome.STDOUT = false;
                      opt.outcome.path = str;
                      return true;
                    }})
      .registerArg(
          {"help", "h", false,
           [](manyfile::option &opt, std::string str) {
             // clang-format off
    std::cout << "Manyfile [arguments...] " << "\n";
    std::cout << " " << "\n";
    std::cout << "arguments: " << "\n";
    std::cout << "    path [directory Path] p -- " << "\n";
    std::cout << "        default path is: './' " << "\n";
    std::cout << "    regex [regex]  r -- " << "\n";
    std::cout << "        All supported regular grammars are as follows: " << "\n";
    std::cout << "            icase " << "\n";
    std::cout << "            nosubs " << "\n";
    std::cout << "            optimize " << "\n";
    std::cout << "            collate " << "\n";
    std::cout << "            ECMAScript " << "\n";
    std::cout << "            basic " << "\n";
    std::cout << "            extended " << "\n";
    std::cout << "            awk " << "\n";
    std::cout << "            grep " << "\n";
    std::cout << "            egrep " << "\n";
    std::cout << "            polynomial " << "\n";
    std::cout << "            multiline " << "\n";
    std::cout << "        The default regular grammar is: basic " << "\n";
    std::cout << "    expression [regex expression] e -- " << "\n";
    std::cout << "        A regular expression that satisfies the condition " << "\n";
    std::cout << "        The default expression is: searching all files " << "\n";
    std::cout << "    input i -- " << "\n";
    std::cout << "        The data from the STDIN " << "\n";
    std::cout << "    output [path] o " << "\n";
    std::cout << "        Store the results in a file " << "\n";
    std::cout << "    help h -- list this " << "\n";
    std::cout << "For example: " << "\n";
    std::cout << "    Manyfile path \"./\" regex ECMAScript expression \".*\" " << "\n";
    std::cout << "    Manyfile p \"./\" r ECMAScript e \".*\" " << "\n";
             // clang-format on
             return true;
           }})
      // .registerArg("help")
      .registerArg([](manyfile::option &opt, std::string_view str) {
        opt.application = str;
      });

      manyfile::call(o.run());

  return EXIT_SUCCESS;
}
