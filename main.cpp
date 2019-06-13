#include <iostream>
#include "src/app/Application.h"
#include "src/app/script_engine/LuaScriptEngine.h"
#include "src/app/character/Character.h"

int main() {
    std::string name = "lua_instance";
    std::string my_name = "Jatinga";
    std::string my_asset = "assets/characters/wall.jpg";
    auto script_engine = new LuaScriptEngine(name);
    Application app = Application("BEST GAME EVER", 800, 600, script_engine);
    auto *me = new Character(my_name, my_asset);
    app.add_entity(me);
    app.loop();
    return 0;
}