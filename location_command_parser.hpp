#pragma once
#include <iostream>
#include "command_parser_maker.hpp"
class location_command_parser : public command_parser {
public:
	virtual bool parse(const std::string &str) override {
        std::cout << "location command parser for:" << str << std::endl;
		return true;
	}
};
REGISTER_COMMAND_PARSER_ENTITY(location_command_parser, "location.command.parser");