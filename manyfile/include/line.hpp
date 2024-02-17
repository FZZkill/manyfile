#include <filesystem>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
#ifndef Manyfile_line_hpp
#define Manyfile_line_hpp
namespace manyfile
{
  class mfiles
  {
  private:
    unsigned int manyFiles = 0;
    std::vector<std::string> lfiles;
    std::regex re;
    const std::string directory;
    const std::filesystem::directory_entry entry;

    void manyfile(std::filesystem::directory_entry entry);
    void getfiles(std::string dire, const std::regex &re);
    void buildall();

  public:
    mfiles(std::string directory, std::regex re);
    mfiles(std::filesystem::directory_entry entry, std::regex re);
    ~mfiles() = default;

    std::vector<std::string> getFiles() const { return this->lfiles; };
    unsigned int getManyFiles() const { return this->manyFiles; };
  };
} // namespace manyline
#endif // !manylineline_hpp
