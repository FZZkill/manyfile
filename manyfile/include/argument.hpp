#include <algorithm>
#include <exception>
#include <filesystem>
#include <format>
#include <functional>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <vector>

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
  namespace argument
  {

    class ArgumentException : std::exception
    {
    public:
      ArgumentException(std::string error) { std::cerr << error << std::endl; };
      ArgumentException() = default;
    };

    template <typename opttype> struct CommandArgument
    {
      const std::string catch_name;
      const std::string abbreviation;
      const bool continue_catch; // NOTE: Capture only one sub-ginseng.
      const std::function<void(opttype &, std::string)> callback; // TODO:
                                                                  // More
                                                                  // arguments
      // const std::function<void(opttype option)> callback;
      const std::function<void()> help;
    };

    template <typename opttype> class CommandOption
    {
    private:
      std::queue<std::string> arguments;
      std::vector<CommandArgument<opttype>> catch_list;
      opttype option;
      const opttype defaultopt;
      const std::string application;

    public:
      CommandOption(int argc, char *argv[], const opttype &defaultopt)
          : application(argv[0]), defaultopt(defaultopt)
      {
        for (int i = 1; i < argc; i++)
          this->arguments.push(argv[i]);
      }
      CommandOption &registerArg(CommandArgument<opttype> arg)
      {
        this->catch_list.emplace_back(arg);
        return *this;
      }

      opttype run(std::function<opttype(const opttype &, const opttype &)> fe)
      {
        std::string l, t;
        while (!this->arguments.empty())
        {
          l = this->arguments.front();
          this->arguments.pop();
          for (auto var : this->catch_list)
          {
            if (l == var.catch_name || l == var.abbreviation)
            {
              if (var.continue_catch)
              {
                if (this->arguments.empty())
                  throw ArgumentException(std::format(
                      "Error: Too few argument in after {}", var.catch_name));
                else
                {
                  t = this->arguments.front();
                  this->arguments.pop();
                }
              }
              var.callback(this->option, t);
            }
          }
        }
        return fe(this->option, this->defaultopt);
      }
    };

  } // namespace argument
};  // namespace manyfile
#endif
