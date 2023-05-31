#pragma once

#include <exception>
#include <string>
#include <utility>

class tape_exception : public std::exception {
    std::string _msg;
public:
    explicit tape_exception(std::string msg) : _msg(std::move(msg)) {}
};
