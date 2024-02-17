#include <filesystem>
#include <regex>
#include <string>

#ifndef manyfile_argument_hpp
#define manyfile_argument_hpp
namespace manyfile
{
  namespace options
  {
    struct source
    {
      bool STDIN;
      std::string path; // If the source from stdin, ths path is source of stdin
    };
    struct outcome
    {
      bool STDOUT;
      std::string path;
    };
    struct fuzzy_search
    {
      bool FUZZY;
      std::string object;
    };
    // TODO: I'll do it when I find a concise JSON library
    // struct option_info
    // {
    //   const bool fromJSON;
    //   const bool toJSON;
    //   const std::string path;
    // };
  } // namespace options

  struct option
  {
    options::source source;
    options::outcome outcome;
    options::fuzzy_search fuzzy_search;
    // options::option_info option_info;
    std::regex_constants::syntax_option_type match_type;
    std::string re;
    std::string application;
  };
  const option doption = {{false, std::filesystem::current_path().string()},
                          {true},
                          {false},
                          std::regex_constants::syntax_option_type::_S_basic,
                          ".*"};

  option argument(int argc, char *argv[]);

}; // namespace manyfile
#endif
