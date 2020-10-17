# C++ NES emulator
Hi and welcome to the homepage of my C++ NES emulator.
The goal of this project is to provide a solid C++ reference for a NES emulator.
Most emulators you will find online are complex and lack proper documentation.

This project shows a possible implementation of a NES emulator using modern C++ (11/14/17).

It is very much a work in progress right now, but be sure to star this repository to stay up-to-date on any new developments.

If time allows, I will write a detailed tutorial that covers everything from the absolute basics all the way to getting an image on screen. Almost none of the tutorials out there do so, and those that do are either outdated or incomplete.

# Project structure
| Folder                                    | Description                                               |
| ----------------------------------------- | --------------------------------------------------------- |
| [./](/)                                   | Root folder of this project.                              |
| [./_deps](/_deps)                         | Third-party libraries.                                    |
| [./cpu](/cpu)                             | Main CPU emulator class.                                  |
| [./cpu/flags](/cpu/flags)                 | Various enums used to emulate the flags of a 6502 CPU.    |
| [./cpu/instructions](cpu/instructions)    | CPU opcode implementations.                               |
| [./editor](/editor)                       | Main editor class.                                        |
| [./editor/ui](/editor/ui)                 | Editor UI components that makes up the complete editor.   |
| [./io](/io)                               | iNES file format implementation and rom loading.          |
| [./ram](/ram)                             | Representation of the NES' RAM.                           |
| [./utility](/utility)                     | Useful functions and miscellaneous helpers.               |
