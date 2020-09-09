#include "location_command_parser.hpp"
int main() {
    std::string type = "location.command.parser";
    auto parser = command_parser_maker::make_unique_ptr(type);
    if (nullptr == parser) {
        std::cerr << type << " not be registed...!";
        return -1;
    }
    std::string str = "hello command parser.";
    parser->parse(str);
    
    return 0;
}