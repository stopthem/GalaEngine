#include "Game/Game.h"
/*#include <sol/sol.hpp>
#include <Windows.h>
#include <iostream>*/

//int nativeCppCubeFunction(int n)
//{
//	return n * n * n;
//}
//
//void TestLua()
//{
//	sol::state lua;
//
//	lua.open_libraries(sol::lib::base);
//
//	// This is how we expose and bind a native c++ function to be used by a Lua script.
//	lua["cube"] = nativeCppCubeFunction;
//
//	lua.script_file("./assets/scripts/myscript.lua");
//
//	// This is how we get a value from Lua script in c++.
//
//	const int someVar = lua["some_variable"];
//	std::cout << someVar << " this is a variable from a Lua script!" << std::endl;
//
//	// This is how we get values from a Lua table from c++.
//
//	bool isFullScreen = lua["config"]["fullscreen"];
//
//	sol::table config = lua["config"];
//	const int width = config["resolution"]["width"];
//	std::cout << width << std::endl;
//
//	// This is how we invoke a Lua function inside c++.
//
//	const sol::function factorialFunction = lua["factorial"];
//	const int functionResult = factorialFunction(5);
//
//	std::cout << "The Lua script calculated 5! as " << functionResult << std::endl;
//}

int main(int argc, char* argv[])
{
	gala::Game game;

	game.Initialize();
	game.Run();
	game.Destroy();

	//TestLua();

	//Sleep(50000);
	return 0;
}
