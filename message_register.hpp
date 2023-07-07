#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "message_processor.hpp"
class message_register {
private:
    std::unordered_map<const char*, message_processor*>message_map_;  // key -- message key
public:
    static message_register& get_instance() {
        static message_register instance;
        return instance;
    }
    message_processor* find_processor(const char* key) {
        auto it = message_map_.find(key);
        if (message_map_.end() == it) {
            return nullptr;
        }
        return it->second;
    }
    template <class T>
    struct register_processor {
        template <typename... Args>
        register_processor(const char* key, Args...args) {
            get_instance().message_map_.emplace(key, new T(args...));
        }
    };
private:
    message_register() = default;
    virtual ~message_register() {
        for (auto& e : message_map_) {
            if (e.second != nullptr) {
                delete e.second;
                e.second = nullptr;
            }
        }
    }
};
#define ENTITY_VNAME(T) entity_##T##_
#define REGISTER_MESSAGE_PROCESSOR(T, key, ...) static message_register::register_processor<T> ENTITY_VNAME(T)(key, __VA_ARGS__);
#define FIND_MESSAGE_PROCESSOR(key) message_register::get_instance().find_processor(key)