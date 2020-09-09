#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include "command_parser.hpp"
class command_parser_maker {
public:
	static command_parser *make(const std::string &parser_type) {
		auto it = map_.find(parser_type);
		if (end(map_) == it) {
			return nullptr;
		}
		return it->second();
	}
	static std::unique_ptr<command_parser>make_unique_ptr(const std::string &parser_type) {
		return std::unique_ptr<command_parser>(make(parser_type));
	}
	static std::shared_ptr<command_parser>make_shared_ptr(const std::string &parser_type) {
		return std::shared_ptr<command_parser>(make(parser_type));
	}
public:
	template<class T>
	struct register_t {
		register_t(const std::string &key){
			command_parser_maker::get().map_.emplace(key, [] { return new T(); });
		}
		template<typename... Args>
		register_t(const std::string &key, Args... args){
			command_parser_maker::get().map_.emplace(key, [=] { return new T(args...); });
		}
	};
private:
	command_parser_maker() = default;
	command_parser_maker(const command_parser_maker &) = delete;
	command_parser_maker & operator = (const command_parser_maker &) = delete;
	command_parser_maker(command_parser_maker &&) = delete;
	~command_parser_maker() = default;
private:
	inline static command_parser_maker &get() {
		static command_parser_maker maker;
		return maker;
	}
private:
	static std::unordered_map<std::string, std::function<command_parser *()>>map_;
};
std::unordered_map<std::string, std::function<command_parser *()>>command_parser_maker::map_;

#define REGISTER_COMMAND_PARSER_ENTITY_VNAME(T) reg_entity_##T##_
#define REGISTER_COMMAND_PARSER_ENTITY(T, key, ...) static command_parser_maker::register_t<T> REGISTER_COMMAND_PARSER_ENTITY_VNAME(T)(key, ##__VA_ARGS__);
