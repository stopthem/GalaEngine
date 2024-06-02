#pragma once

#include <imgui_console/imgui_console.h>

namespace gala
{
    /*
     * GalaConsole
     *
     * Class that handles editor console
     */
    class GalaConsole
    {
    public:
        GalaConsole();

#pragma region Singleton
        static GalaConsole& Get()
        {
            static GalaConsole galaConsole;

            return galaConsole;
        }

        GalaConsole(GalaConsole const&) = delete;
        void operator =(GalaConsole const&) = delete;
#pragma endregion

    public:
        [[nodiscard]] const std::unique_ptr<ImGuiConsole>& GetConsole() const
        {
            return ImGuiConsole;
        }

    private:
        std::unique_ptr<ImGuiConsole> ImGuiConsole;

    public:
        void Update();
    };
}
