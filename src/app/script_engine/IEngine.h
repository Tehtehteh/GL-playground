#pragma once
#ifndef GLEW_STUFF_IENGINE_H
#define GLEW_STUFF_IENGINE_H

#endif //GLEW_STUFF_IENGINE_H
#include "string"

class IScriptEngine {
public:
    virtual ~IScriptEngine() = default;
    virtual int execute_string(std::string) = 0;
    virtual int execute_file(std::string) = 0;
};

