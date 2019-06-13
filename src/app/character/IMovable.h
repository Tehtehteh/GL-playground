#pragma once

#ifndef GLEW_STUFF_IMOVABLE_H
#define GLEW_STUFF_IMOVABLE_H
#include <GLFW/glfw3.h>

typedef struct {
    GLfloat x;
    GLfloat y;
} Position;

class IMovable {
public:
    void move(Position);
    Position position{};
};


#endif //GLEW_STUFF_IMOVABLE_H
