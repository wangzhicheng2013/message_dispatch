#pragma once
#include <string>
class command_parser {
public:
	command_parser() = default;
	virtual ~command_parser() = default;
public:
	virtual bool parse(const std::string &) = 0;
};