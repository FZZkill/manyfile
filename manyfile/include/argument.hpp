#include <algorithm>
#include <exception>
#include <filesystem>
#include <format>
#include <functional>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <string_view>
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
    std::string re_s;
    std::regex re;
    std::string_view application;
  };

  const option doption = {{false, std::filesystem::current_path().string()},
                          {true},
                          {false},
                          std::regex_constants::syntax_option_type::_S_basic,
                          "",
                          std::regex(".*", std::regex_constants::_S_basic)};
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
      const std::string_view catch_name;
      const std::string_view abbreviation;
      const bool continue_catch; // NOTE: Capture only one sub-ginseng.
      const std::function<bool(opttype &, std::string)> &callback; // TODO:
                                                                   // More
                                                                   // arguments
      // const std::function<void(opttype option)> callback;
      // const std::function<void()> help;
    };

    template <typename opttype> class CommandOption
    {
    private:
      std::queue<std::string_view> arguments;

      std::unordered_map<std::string_view, CommandArgument<opttype>> catch_list;
      opttype option;
      const std::string application;

    public:
      CommandOption(int argc, char *argv[], const opttype &defaultopt)
          : application(argv[0]), option(defaultopt)
      {
        for (int i = 1; i < argc; i++)
          this->arguments.push(argv[i]);
      }
      CommandOption &registerArg(CommandArgument<opttype> &&arg)
      {
        this->catch_list.emplace(arg.catch_name, arg);
        this->catch_list.emplace(arg.abbreviation, arg);
        return *this;
      }

      CommandOption &
      registerArg(const std::function<void(opttype &, const std::string_view &)>
                      &callback)
      {
        callback(this->option, this->application);
        return *this;
      }
      CommandOption &registerArg(std::string_view command)
      {
        if (this->arguments.empty())
          this->arguments.push(command); // TODO:
        return *this;
      }

      opttype run()
      {
        std::string_view l;
        std::string t;
        while (!this->arguments.empty())
        {
          l = this->arguments.front();
          this->arguments.pop();

          auto it = this->catch_list.find(l);
          if (it == this->catch_list.end())
          {
            std::cerr << std::format("Error: Unknown argument {}", l) << "\n";
            break;
          }
          auto var = it->second;

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
          if (!var.callback(this->option, t))
            std::cerr << std::format("Error: Unknown subparameter: {}", t)
                      << "\n";
        }
        return this->option;
      }
    };

  } // namespace argument
};  // namespace manyfile
#endif
