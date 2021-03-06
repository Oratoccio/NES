#ifndef NES_EDITOR_HPP
#define NES_EDITOR_HPP

#include "io/rom_file.hpp"

#include "ui/ui_cpu_controller.hpp"
#include "ui/ui_ram_visualizer.hpp"
#include "ui/ui_rom_browser.hpp"

#include <string>

// SFML forward declarations
namespace sf
{
    class Event;
    class RenderWindow;
    class Time;
}

namespace nes
{
    class CPU;
    class RAM;

    class Editor
    {
    public:
        /**
         * Create a new editor instance
         * @param   window  SFML window to render the UI to
         * @param   cpu     Reference to the emulator's CPU object
         * @param   ram     Reference to the emulator's RAM object
         */
        Editor(sf::RenderWindow& window, CPU& cpu, RAM& ram);

        /*
         * Initialize the NES editor
         */
        void Initialize();

        /**
         * Update NES editor state
         * @param   deltaTime   Time between main loop ticks
         */
        void Update(const sf::Time deltaTime);

        /**
         * SFML input, allows the editor to respond to the user
         * @param   event   SFML event object
         */
        void ProcessEvent(const sf::Event event) const;

        /**
         * Render all UI
         */
        void DrawUI() const;

        /**
         * Clean up all editor resources
         */
        void Destroy();

    private:
        /**
         * Style the UI
         */
        void ApplyStyle();

        /**
         * Load a ROM into memory
         */
        void LoadROM(const std::string& romPath);

    private:
        sf::RenderWindow& WindowRef;

        CPU& CpuRef;
        RAM& RamRef;

        RomFile ActiveRom;

        UICpuController CpuControllerUI;
        UIRamVisualizer RamVisualizerUI;
        UIRomBrowser RomBrowserUI;
    };
}

#endif //! NES_EDITOR_HPP
