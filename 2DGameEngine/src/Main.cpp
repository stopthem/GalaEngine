#include <iostream>
#include <SDL.h>
#include <sol/sol.hpp>

int main(int argc, char* argv[])
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    SDL_Init(SDL_INIT_EVERYTHING);

    std::cout << "Hello, world!" << std::endl;

    return 0;
}
