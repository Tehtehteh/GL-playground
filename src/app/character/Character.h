#pragma once
#ifndef GLEW_STUFF_CHARACTER_H
#define GLEW_STUFF_CHARACTER_H
#include "ICharacter.h"
#include "DirectionalAsset.h"
#include "IMovable.h"
#include <map>
#include <string>
#include <GLFW/glfw3.h>

using CharacterState = struct {
    Direction direction;
};

using Assets = std::map<Direction, std::string>;

class Character: public ICharacter, DirectionalAsset {
public:
    explicit Character(const std::string& name, const std::string& file_name);
    explicit Character(CharacterState);
    explicit Character(CharacterState, const Assets&);
    ~Character() override ;
    Assets assets;
    void load_and_buffer_asset(const std::string&) override ;
    GLuint texture_id{};
    std::string character_name;
    void render() override;
    std::map<GLuint, Direction> directions;
    void setup_directions(GLFWwindow*);
};


#endif //GLEW_STUFF_CHARACTER_H
