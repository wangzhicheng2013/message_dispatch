#pragma once
#include <iostream>
#include "message_register.hpp"
class message_log : public message_processor {
public:
private:
    const char* str = "hello";
public:
    message_log(const char* s) : str(s) {
    }
    virtual bool process() override {
        std::cout << "message log:" << str << std::endl;
        return true;
    }
};
REGISTER_MESSAGE_PROCESSOR(message_log, "message_log", "hello world...!");