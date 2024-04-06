#include "vector"
#include <iostream>
#include <string>
#include <sstream>

double compute_maxseq(std::vector<double> input){

  int len_input = input.size();
  double S1 = input[0];
  double S2 = input[0];
  int event;
  for (int i=1; i<len_input; i++){
    if (input[i-1] > 0 &&  input[i] > 0){
      S2 += input[i];
    }
    else if (input[i-1] > 0 &&  input[i] < 0){
      if (S2 > S1)
	S1 = S2;
      S2 += input[i];
    }
    else if (input[i-1] < 0 &&  input[i] < 0){
      S2 += input[i];
    }
    else if (input[i-1] < 0 &&  input[i] > 0){
      if (S2<0.)
	S2 = 0.;
      S2 += input[i];
    }
    
  }

  if (S2 > S1) S1 = S2;
  return S1;
}

int main(int argc, char* argv[]) {
    // Check if there are enough arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <value1> <value2> ... <valueN>\n";
        return 1; // return an error code
    }

    // Vector to store the input values
    std::vector<double> inputValues;

    // Parse command-line arguments and convert to double
    for (int i = 1; i < argc; ++i) {
        std::istringstream iss(argv[i]);
        double value;
        if (!(iss >> value)) {
            std::cerr << "Invalid input: " << argv[i] << std::endl;
            return 1;
        }
        inputValues.push_back(value);
    }

  double max = compute_maxseq(inputValues);
  std::cout << "Max sum: " << max << std::endl;;

  
}
