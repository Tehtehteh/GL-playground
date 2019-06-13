#ifndef GLEW_STUFF_APPLICATION_H
#define GLEW_STUFF_APPLICATION_H

#include <string>
#include <GLFW/glfw3.h>
#include <vector>
#include "script_engine/IEngine.h"
#include "character/ICharacter.h"


class Application {

public:
    Application(std::string, int, int, IScriptEngine*);
    void loop();
    void set_width(int width);
    void set_height(int height);
    bool set_window(GLFWwindow*);
    void set_script_engine(IScriptEngine*);
    void update();
    void add_entity(ICharacter*);
    GLuint load_asset(const ICharacter&);
    ~Application();
    std::string window_title;
    bool initialized;
    bool running{};

    std::vector<ICharacter*> entities;
    int height{};
    int width{};
protected:
    GLFWwindow *window;
    IScriptEngine *script_engine{};

    void MoveEntity(GLFWwindow *w, int key, int scancode, int action, int mods);
};


#endif //GLEW_STUFF_APPLICATION_H
