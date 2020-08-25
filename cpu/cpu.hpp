#ifndef NES_CPU_HPP
#define NES_CPU_HPP

#include <cstdint>

namespace nes
{
    /**
     * Emulates a MOS Technology 6502 microprocessor as seen in the NES
     */
    class CPU
    {
    public:
        // DEBUG CODE, JUST NEED A WAY TO RUN THIS CODE FROM main.cpp
        void Entry();

    private:
        /**
         * All possible addressing modes
         */
        enum class AddressingMode
        {
            Accumulator,
            Immediate,
            ZeroPage,
            ZeroPageX,
            Absolute,
            AbsoluteX,
            AbsoluteY,
            IndirectX,
            IndirectY
        };

    private:
        // DEBUG CODE, READ WHATEVER BYTE IS AT THE PC
        char ReadAtPC();

        void ADC(AddressingMode mode);
        void AND(AddressingMode mode);
        void ASL(AddressingMode mode);

    private:
        // Accumulator
        std::uint8_t A;

        // Index registers
        std::uint8_t X;
        std::uint8_t Y;

        // Processor status flag bits
        // 0 - carry flag
        // 1 - zero flag
        // 2 - interrupt disable
        // 3 - decimal mode (enable BCD mode) does not affect the 2A03
        // 4 - break command
        // 5 - unused bit
        // 6 - overflow flag
        // 7 - negative flag
        std::uint8_t P;

        // Stack pointer
        // Lives in address 0x100 to 0x1FF
        // Wraps around when its capacity is exceeded
        std::uint8_t S;

        // Program counter
        std::uint16_t PC;

        //#DEBUG: RAM
        std::uint8_t* Memory;
    };
}

#endif //! NES_CPU_HPP