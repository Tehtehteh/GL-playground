#pragma once
#ifndef GLEW_STUFF_ICHARACTER_H
#define GLEW_STUFF_ICHARACTER_H
#include <string>
#include <GLFW/glfw3.h>
#include "IMovable.h"


class ICharacter : public IMovable {
public:
    const std::string character_name;
    virtual ~ICharacter() = default;
    virtual void render() = 0;
    GLuint texture_id={};
    virtual void load_and_buffer_asset(const std::string&) = 0;
};

#endif //GLEW_STUFF_ICHARACTER_H