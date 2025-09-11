#include "../configParser.cpp"

int main() {
    ConfigParser parser;
    if (parser.parseFile("./configs/config.txt")) {
        const auto& cfg = parser.getConfig();
	parser.printConfig();
        // for (const auto& [container, vars] : cfg) {
        //     std::cout << "[" << container << "]\n";
        //     for (const auto& [key, value] : vars) {
        //         std::cout << "  " << key << " = " << value << "\n";
        //     }
        // }
    }
}
