#include "cpu_instruction_op_adc.hpp"
#include "cpu/cpu.hpp"

#include <iostream>

nes::CpuInstructionOpADC::CpuInstructionOpADC(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ADC")
{}

void nes::CpuInstructionOpADC::ExecuteImpl()  
{
	std::uint8_t value = CpuRef.ReadRamValueAtAddress(CpuRef.GetTargetAddress(InstructionAddressingMode));
	std::uint8_t result = CpuRef.A + value + (CpuRef.P << static_cast<std::uint8_t>(StatusFlags::Carry));

	// Overflow detected
	if (result < CpuRef.A)
	{
		CpuRef.SetStatusFlag(StatusFlags::Overflow);
		CpuRef.SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Overflow);
		CpuRef.ClearStatusFlag(StatusFlags::Carry);
	}

	CpuRef.A = result;

	CpuRef.UpdateNegativeStatusFlag(CpuRef.A);
	CpuRef.UpdateZeroStatusFlag(CpuRef.A);

	if (InstructionAddressingMode == AddressingMode::Immediate)
	{
		CycleCount = 2;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPage)
	{
		CycleCount = 3;
	}
	else if (InstructionAddressingMode == AddressingMode::ZeroPageX)
	{
		CycleCount = 4;
	}
	else if (InstructionAddressingMode == AddressingMode::Absolute)
	{
		CycleCount = 4;
	}
	else if (InstructionAddressingMode == AddressingMode::AbsoluteX || InstructionAddressingMode == AddressingMode::AbsoluteY)
	{
		std::uint16_t initialPC = CpuRef.PC;
		std::uint16_t currentPC = initialPC += 3;
		CycleCount = 4;

		if (CpuRef.DidProgramCounterCrossPageBoundary(initialPC, currentPC))
		{
			++CycleCount;
		}
	}
	else if (InstructionAddressingMode == AddressingMode::IndirectX)
	{
		CycleCount = 6;
	}
	else if (InstructionAddressingMode == AddressingMode::IndirectY)
	{
		std::uint16_t initialPC = CpuRef.PC;
		std::uint16_t currentPC = initialPC += 2;
		CycleCount = 5;

		if (CpuRef.DidProgramCounterCrossPageBoundary(initialPC, currentPC))
		{
			++CycleCount;
		}
	}
	else
	{
		std::cerr << "ADC - Unknown addressing mode.\n";
	}
}
