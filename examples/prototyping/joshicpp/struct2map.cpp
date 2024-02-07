#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <any>

class COptionBase {
private:
  std::string value;
public:
  virtual ~COptionBase() = default;

  const std::string& GetValue() const {return value;}

  virtual std::string SetValue(const std::string& val) {
    value = val;
    return "";
  }
  virtual void SetDefault() = 0;

};





template<typename Scalar>
class COptionScalar : public COptionBase {
protected:
  Scalar& field; // Reference to the fieldname
  const Scalar def; // Default value
  const std::string name; // identifier for the option
  const std::string typeName; // name for the scalar type

public:
  COptionScalar() = delete;

  COptionScalar(const std::string& type_name,
                const std::string& option_field_name,
                Scalar& option_field,
                Scalar default_value) :
    field(option_field),
    def(default_value),
    name(option_field_name),
    typeName(type_name) {
  }

  std::string SetValue(const std::string& option_value) override {
    COptionBase::SetValue(option_value);

    std::istringstream is(option_value.front());
    is >> field;

  }

  void SetDefault() final {
    field = def;
  }
};


template <typename Real>
struct Coptions {

  int a;
  Real b;
  std::map<std::string, COptionBase*> variables_map;

  void Init(){
    std::string ax = "a";
    std::string bx = "b";
    add_variable(ax, a, 1);
    add_variable(bx, b, 0.);

}
  template<typename T>
  void add_variable(const std::string& name, T& var, T deft ){
    var = deft;
    COptionBase * opt = &COptionScalar<T>(var);  
    variables_map.insert(std::pair<std::string, COptionBase *>(name, val));
    //variables_map[name] = var;
  }

  // void convert(int& var, std::string sval){
  //   int val = std::stoi(sval);
  //   var = val;
  // }
  // void convert(Real& var, std::string sval){
  //   int val = std::stod(sval);
  //   var = val;
  // }
  
  void run(){
    //convert(variables_map["a"], "5");
    //convert(variables_map["b"], "6.5");
    variables_map["a"]->SetValue("5")
    variables_map["b"]->SetValue("6.5")
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
  }
};

int main() {

  Coptions<double> args = Coptions<double>();
  args.Init();
  args.run();
  
  return 0;
}
