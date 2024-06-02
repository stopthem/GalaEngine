#include "GalaConsole.h"

gala::GalaConsole::GalaConsole()
    : ImGuiConsole(std::make_unique<class ImGuiConsole>())
{
}

void gala::GalaConsole::Update()
{
    ImGuiConsole->Draw();
}
