#include "cpu_instruction_op_php.hpp"
#include "cpu/cpu.hpp"
#include "cpu/flags/cpu_b_flags.hpp"

nes::CpuInstructionOpPHP::CpuInstructionOpPHP(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "PHP")
{}

void nes::CpuInstructionOpPHP::ExecuteImpl()
{
	Byte newFlags;
	newFlags.value = (CpuRef.P.value | static_cast<std::uint8_t>(BFlag::Instruction));
	CpuRef.PushStack(newFlags);
	CycleCount = 3;
}
