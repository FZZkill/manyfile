#include <filesystem>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
#ifndef Manyfile_files_hpp
#define Manyfile_files_hpp
namespace manyfile
{
  class Files
  {
  private:
    unsigned int manyFiles = 0;
    std::vector<std::string> vfiles;
    std::regex re;
    const std::string DIRECTORY;
    const std::filesystem::directory_entry ENTRY;

    void manyfile(std::filesystem::directory_entry entry);
    void getfiles(std::string dire, const std::regex &re);
    void buildall();

  public:
    Files(std::string directory, std::regex re);
    Files(std::filesystem::directory_entry entry, std::regex re);
    ~Files() = default;

    std::vector<std::string> getFiles() const { return this->vfiles; };
    unsigned int getManyFiles() const { return this->manyFiles; };
  };
} // namespace manyline
#endif // !manylineline_hpp
