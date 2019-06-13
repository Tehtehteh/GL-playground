#include "LuaScriptEngine.h"

LuaScriptEngine::LuaScriptEngine(std::string name) {
    this->lua_state = luaL_newstate();
    this->opened = true;
    this->name = std::move(name);
}

LuaScriptEngine::~LuaScriptEngine() {
    lua_close(this->lua_state);
    this->opened = false;
}

int LuaScriptEngine::execute_string(std::string script){
    if (!this->opened) {
        return -1;
    }
    int r = luaL_dostring(this->lua_state, script.c_str());
    return r;
}

int LuaScriptEngine::execute_file(std::string file_name){
    if (!utils::file_exists(file_name)) {
        return -1;
    }
    return 1;
}
