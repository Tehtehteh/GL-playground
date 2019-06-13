#pragma once
#ifndef GLEW_STUFF_LUASCRIPTENGINE_H
#define GLEW_STUFF_LUASCRIPTENGINE_H
#include "IEngine.h"
#include "string"
#include "../utils/utils.h"
extern "C" {
    #include "lua/lualib.h"
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
}

class LuaScriptEngine : public IScriptEngine {
public:
    explicit LuaScriptEngine(std::string name);
    ~LuaScriptEngine() override;
    int execute_string(std:: string) override;
    int execute_file(std::string) override;

    std::string name;
    bool opened;
protected:
    lua_State *lua_state;
};


#endif //GLEW_STUFF_LUASCRIPTENGINE_H
