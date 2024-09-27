#include <map>
#include <string>

struct Container {

  virtual void SetValues(std::map<std::string, std::string> map) = 0;
  virtual ~Container() = default;
  Container(std::map<std::string, std::string> container_map) {
    SetValues(container_map);
  }
  
  void writeValue(std::map<std::string, std::string> map,
		  std::string name,
		  int &value);
  void writeValue(std::map<std::string, std::string> map,
		  std::string name,
		  double &value);
  void writeValue(std::map<std::string, std::string> map,
		  std::string name,
		  std::string &value);
  void writeValue(std::map<std::string, std::string> map,
		  std::string name,
		  unsigned long &value);
};

struct Cmc1: Container {

  
  double mu;
  double strike;
  double spot; 
  double vol; 
  double rate;
  double period;
  unsigned long numPaths;
  unsigned long numSteps;

  void SetValues(std::map<std::string, std::string> map) override {
    writeValue(map, "mu", mu);    
    writeValue(map, "strike", strike);
    writeValue(map, "spot", spot);
    writeValue(map, "vol", vol);
    writeValue(map, "rate", rate);
    writeValue(map, "period", period);
    writeValue(map, "numPaths", numPaths);
    writeValue(map, "numSteps", numSteps);    
  }
  
};
