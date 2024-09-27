#include <map>
#include <string>

using namespace std;


/*!
 * \class ParseInput
 * \brief Parses and input file and groups inputs into a map
 */
class ParseInput {

  // Function to trim spaces from the beginning and end of a string
  std::string trim(const std::string &str);
  public:
  std::map<string, string> map_vars;
  std::map<string, std::map<string, string>> map_containers;
  
  void read_file(string file_name);
  
};

class Config {
public:
  
  virtual void SetContainers(std::map<string, std::map<string, string>> map) =0;
  virtual void SetValues(std::map<std::string, std::string> map_vars) = 0;
  virtual void Serialise(std::map<char, std::string> map) = 0;
  virtual ~Config() = default;
};

class Config1: public Config {
public:

  std::map<string, string> map_vars;
  Cmc1* ct1 = nullptr;

  Config1(std::map<string, std::map<string, string>> map,
          std::map<std::string, std::string> map_vars);

  Config1(std::map<string, std::map<string, string>> map);
  
  virtual void SetContainers(std::map<string, std::map<string, string>> map) override;
  
  virtual void SetValues(std::map<std::string, std::string> mapvars) override;
  
  virtual void Serialise(std::map<char, std::string> map) override;
  ~Config1();
};

Config1 buildConfig(std::string input);

