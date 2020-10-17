#ifndef NES_CPU_HPP
#define NES_CPU_HPP

#include "cpu_logger.hpp"
#include "flags/cpu_status_flags.hpp"
#include "instructions/cpu_instruction_addressing_mode.hpp"

#include <cstdint>
#include <string_view>

namespace nes
{
    class RAM;

    /**
     * Emulates a MOS Technology 6502 microprocessor as seen in the NES
     */
    class CPU
    {
    public:
        /**
         * All available registers
         */
        enum class RegisterType
        {
            A,  // A register
            X,  // X register
            Y,  // Y register
            P,  // P register (flags)
            SP  // Stack pointer
        };

    public:
        /**
         * Create a new CPU object
         * @param   ramRef  Reference to the RAM
         */
        CPU(RAM& ramRef);

        /**
         * Reset the vector back to the default memory address
         * This address is given by the reset vector at 0xFFFD and 0xFFFC
         */
        void SetProgramCounterToResetVector();

        /**
         * Manually move the program counter to a specific address in memory
         * @param   address     Address to set the program counter to
         */
        void SetProgramCounterToAddress(std::uint16_t address);

        /**
         * Fetch the opcode at the program counter and attempt to execute the
         * instruction
         */
        void ExecuteInstruction();

        /**
         * Manually move the program counter N number of bytes relative to its
         * current memory address
         * @param   offset  Number of bytes to move the program counter
         */
        void MoveProgramCounter(std::int32_t offset);

        /**
         * Returns the value of the byte in RAM at the specified address
         * @param   address     Address to read from
         * @return  Value of the byte in RAM
         */
        std::uint8_t ReadRamValueAtAddress(std::uint16_t address) const;

        /**
         * Get the current value of the program counter accounting for the offset
         * in RAM
         * @return  Current value of the program counter
         */
        std::uint16_t GetProgramCounter() const;

        /**
         * Get the current value of the stack pointer
         * @return  Current value of the stack pointer
         */
        std::uint16_t GetStackPointer() const;

        /**
         * Retrieve the value of a register
         * @param   type    Register to retrieve its value for
         * @return  Register's value
         */
        std::uint8_t GetRegister(RegisterType type) const;

        /**
         * Retrieve the current cycle index
         * @return  Current cycle
         */
        std::uint64_t GetCurrentCycle() const;

        /**
         * Reset the CPU to its default state
         */
        void SetDefaultState();

    private:
        /**
         * Execute the proper op-code
         * @param   opCode  Op-code to execute
         */
        void ProcessOpCode(std::uint8_t opCode);

        /**
         * Push a value to the stack
         * @param   value   Value to push to the stack
         */
        void PushStack(std::uint8_t value);

        /**
         * Pop a value from the stack
         * @return  Value popped from the stack
         */
        std::uint8_t PopStack();

        /**
         * Check if a 256-byte page boundary was crossed between two addresses
         * @param   before  Initial address
         * @param   after   Address to check against
         * @return  True when a page boundary was crossed, false when not
         */
        bool DidProgramCounterCrossPageBoundary(std::uint16_t before, std::uint16_t after) const;

        /**
         * Retrieve the target address of an instruction based on the addressing
         * mode specified
         * @param   mode    Addressing mode to use
         * @return  Target address of the instruction
         */
        std::uint16_t GetTargetAddress(AddressingMode mode) const;

        /**
         * Set a processor status flag
         * @param   flag    Flag to set
         */
        void SetStatusFlag(StatusFlags flag);

        /**
         * Clear a processor status flag
         * @param   flag    Flag to clear
         */
        void ClearStatusFlag(StatusFlags flag);

        /**
         * Check if a status flag has been set
         * @param   flag    Flag to check
         * @return  True when the flag is set, false when clear
         */
        bool IsStatusFlagSet(StatusFlags flag) const;

        /**
         * Check if a status flag has been cleared
		 * @param   flag    Flag to check
		 * @return  True when the flag is clear, false when set
         */
        bool IsStatusFlagClear(StatusFlags flag) const;

        /**
         * Check if bit N has been set
         * @param   byte    Byte to check
         * @param   n       Bit to check
         * @return  True when the flag is set, false when clear
         */
		bool IsNthBitSet(std::uint8_t byte, std::uint8_t n) const;

        /**
         * Check if bit N has been cleared
         * @param   byte    Byte to check
         * @param   n       Bit to check
         * @return  True when the flag is clear, false when set
         */
        bool IsNthBitClear(std::uint8_t byte, std::uint8_t n) const;

        /**
         * Set a bit when the input bit is set, clear a bit when the input bit is
         * clear. This is useful when matching bits at specific indices.
         * @param   target  Byte whose bits will be updated
         * @param   source  Byte whose bits will be compared against
         * @param   n       Bit index to compare
         */
        void MatchBitStateOfNthBit(std::uint8_t& target, std::uint8_t source, std::uint8_t n) const;

        /**
         * Set or clear the zero flag based on the value of the byte passed
         * @param   byte    Byte to check
         */
        void UpdateZeroStatusFlag(std::uint8_t byte);

        /**
         * Set or clear the negative flag based on the value of the byte passed
         * @param   byte    Byte to check
         */
        void UpdateNegativeStatusFlag(std::uint8_t byte);

    private:
        void ADC(AddressingMode mode);
        void AND(AddressingMode mode);
        void ASL(AddressingMode mode);
        void BCC(AddressingMode mode);
        void BCS(AddressingMode mode);
        void BEQ(AddressingMode mode);
        void BIT(AddressingMode mode);
        void BMI(AddressingMode mode);
        void BNE(AddressingMode mode);
        void BPL(AddressingMode mode);
        void BRK(AddressingMode mode);
        void BVC(AddressingMode mode);
        void BVS(AddressingMode mode);
        void CLC(AddressingMode mode);
        void CLD(AddressingMode mode);
        void CLI(AddressingMode mode);
        void CLV(AddressingMode mode);
        void CMP(AddressingMode mode);
        void CPX(AddressingMode mode);
        void CPY(AddressingMode mode);
        void DEC(AddressingMode mode);
        void DEX(AddressingMode mode);
        void DEY(AddressingMode mode);
        void EOR(AddressingMode mode);
        void INC(AddressingMode mode);
        void INX(AddressingMode mode);
        void INY(AddressingMode mode);
        void JMP(AddressingMode mode);
        void JSR(AddressingMode mode);
        void LDA(AddressingMode mode);
        void LDX(AddressingMode mode);
        void LDY(AddressingMode mode);
        void LSR(AddressingMode mode);
        void NOP(AddressingMode mode);
        void ORA(AddressingMode mode);
        void PHA(AddressingMode mode);
        void PHP(AddressingMode mode);
        void PLA(AddressingMode mode);
        void PLP(AddressingMode mode);
        void ROL(AddressingMode mode);
        void ROR(AddressingMode mode);
        void RTI(AddressingMode mode);
        void RTS(AddressingMode mode);
        void SBC(AddressingMode mode);
        void SEC(AddressingMode mode);
        void SED(AddressingMode mode);
        void SEI(AddressingMode mode);
        void STA(AddressingMode mode);
		void STX(AddressingMode mode);
		void STY(AddressingMode mode);
        void TAX(AddressingMode mode);
        void TAY(AddressingMode mode);
        void TSX(AddressingMode mode);
        void TXA(AddressingMode mode);
        void TXS(AddressingMode mode);
        void TYA(AddressingMode mode);

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
        std::uint8_t SP;

        // Program counter
        std::uint16_t PC;

        // RAM
        RAM& RamRef;

        // CPU logger
        CpuLogger Logger;

        // Keep track of the current CPU cycle to allow for synchronization
        std::uint64_t CurrentCycle;
    };
}

#endif //! NES_CPU_HPP
