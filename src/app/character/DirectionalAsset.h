//
// Created by tehtehteh on 2019-06-04.
//

#ifndef GLEW_STUFF_DIRECTIONALASSET_H
#define GLEW_STUFF_DIRECTIONALASSET_H

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class DirectionalAsset {
public:
    Direction direction;
    void change_direction(Direction new_direction);
};


#endif //GLEW_STUFF_DIRECTIONALASSET_H
