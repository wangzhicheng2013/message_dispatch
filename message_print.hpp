#pragma once
#include <iostream>
#include "message_register.hpp"
class message_print : public message_processor {
private:
    int num = 0;
public:
    message_print(int n) : num(n) {
    }
    virtual bool process() override {
        std::cout << "message print:" << num << std::endl;
        return true;
    }
};
REGISTER_MESSAGE_PROCESSOR(message_print, "message_print", 123);