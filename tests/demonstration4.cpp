#include <fstream>
#include <streambuf>
#include <string>
#include <iostream>
#include <luacppinterface.h>

int main()
{
  std::ifstream file("config.lua");
  std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  Lua lua;
  lua.RunScript(script);
  int width = lua.GetGlobalEnvironment().Get<int>("width");    // get the width
  int height = lua.GetGlobalEnvironment().Get<int>("height");  // get the height
  std::string windowTitle = lua.GetGlobalEnvironment().Get<std::string>("windowTitle");

  return width != 640 || height != 480 || windowTitle.compare("Lua Rocks");
}
