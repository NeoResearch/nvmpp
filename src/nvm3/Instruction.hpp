#ifndef NEOPT_NVM_INSTRUCTION_HPP
#define NEOPT_NVM_INSTRUCTION_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/BitConverter.hpp>
#include <system/printable.h>
#include <system/vhelper.hpp>

#include "OpCode.h"

using namespace std; // TODO: remove

namespace neopt {
namespace nvm {

class Instruction
{
public:
   static Instruction RET()
   {
      return Instruction(nvm::OpCode::OP_RET);
   }

   OpCode OpCode;
   vbyte Operand;

private:
   Instruction(nvm::OpCode opcode)
   {
      this->OpCode = opcode;
   }

private:
   // TODO: constexpr
   static int* OperandSizePrefixTable; // = new int[256];
   static int* OperandSizeTable;       // = new int[256];

public:
   // TODO: constexpr
   int Size()
   {
      int prefixSize = OperandSizePrefixTable[(int)OpCode];
      return prefixSize > 0
               ? 1 + prefixSize + Operand.size()
               : 1 + OperandSizeTable[(int)OpCode];
   }

   short TokenI16()
   {
      return BitConverter::ToInt16(Operand, 0);
   }

   string TokenString()
   {
      return ""; //Encoding.ASCII.GetString(Operand);
   }

   uint TokenU32()
   {
      return BitConverter::ToUInt32(Operand, 0);
   }

   /*
       // using C++17 or not?
      // https://stackoverflow.com/questions/13313980/populate-an-array-using-constexpr-at-compile-time
      private: 
        static ::std::array<OpCode, 256> PopulateInstruction()
        {
            OperandSizePrefixTable[(int)OpCode.PUSHDATA1] = 1;
            OperandSizePrefixTable[(int)OpCode.PUSHDATA2] = 2;
            OperandSizePrefixTable[(int)OpCode.PUSHDATA4] = 4;
            for (int i = (int)OpCode.PUSHBYTES1; i <= (int)OpCode.PUSHBYTES75; i++)
                OperandSizeTable[i] = i;
            OperandSizeTable[(int)OpCode.JMP] = 2;
            OperandSizeTable[(int)OpCode.JMPIF] = 2;
            OperandSizeTable[(int)OpCode.JMPIFNOT] = 2;
            OperandSizeTable[(int)OpCode.CALL] = 2;
            OperandSizeTable[(int)OpCode.SYSCALL] = 4;
        }
        */

   // TODO: internal?
public:
   Instruction(vbyte script, int ip)
   {
      this->OpCode = (nvm::OpCode)script[ip++];
      int operandSizePrefix = OperandSizePrefixTable[(int)OpCode];
      int operandSize = 0;
      switch (operandSizePrefix) {
         case 0:
            operandSize = OperandSizeTable[(int)OpCode];
            break;
         case 1:
            operandSize = script[ip];
            break;
         case 2:
            operandSize = BitConverter::ToUInt16(script, ip);
            break;
         case 4:
            operandSize = BitConverter::ToInt32(script, ip);
            break;
      }
      if (operandSize > 0) {
         ip += operandSizePrefix;
         this->Operand = vbyte(operandSize);
         if (ip + operandSize > script.size()) {
            //throw new InvalidOperationException();
            NEOPT_EXCEPTION("InvalidOperationException");
         }

         //Unsafe.MemoryCopy(script, ip, Operand, 0, operandSize);
         NEOPT_EXCEPTION("TODO: memory copy on Instruction");
      }
   }
};

int* Instruction::OperandSizePrefixTable = new int[256];

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_INSTRUCTION_HPP