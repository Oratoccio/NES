#ifndef NES_CPU_INSTRUCTION_OP_BVS_HPP
#define NES_CPU_INSTRUCTION_OP_BVS_HPP

#include "cpu_instruction_base.hpp"

namespace nes
{
	class CPU;

	/**
	 * Branch overflow set
	 */
	class CpuInstructionOpBVS : public CpuInstructionBase
	{
	public:
		/**
		 * Create a new BVS instruction
		 * @param	cpuRef				Reference to the CPU object
		 * @param	addressingMode		Addressing mode used for this instruction
		 */
		CpuInstructionOpBVS(CPU& cpuRef, AddressingMode addressingMode);

	protected:
		/**
		 * Perform branch if overflow set
		 */
		void ExecuteImpl() final override;
	};
}

#endif //! NES_CPU_INSTRUCTION_OP_BVS_HPP
