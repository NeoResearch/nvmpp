#ifndef NEOPT_NVM_SCRIPT_HPP
#define NEOPT_NVM_SCRIPT_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/Dictionary.hpp>
#include <system/printable.h>
#include <system/vhelper.hpp>

#include "Instruction.hpp"

using namespace std; // TODO: remove

namespace neopt {
namespace nvm {
class Script
{
private:
   vbyte _value;
   Dictionary<int, Instruction> _instructions;

public:
   /// <summary>
   /// Script length
   /// </summary>
   int Length()
   {
      return _value.size();
   }

   /// <summary>
   /// Get opcode
   /// </summary>
   /// <param name="index">Index</param>
   /// <returns>Returns the opcode</returns>
   nvm::OpCode operator[](int index)
   {
      return (nvm::OpCode)_value[index];
   }

   // default constructor
   Script()
   {
   }

   /// <summary>
   /// Constructor
   /// </summary>
   /// <param name="script">Script</param>
   Script(vbyte script)
   {
      _value = script;
   }

   nvm::Instruction GetInstruction(int ip)
   {
      if (ip >= Length())
         return Instruction::RET();

      nvm::Instruction* instruction = _instructions.TryGetValue(ip);
      if (!instruction) {
         Instruction instruction2(_value, ip);
         _instructions.Add(ip, instruction2);
         return instruction2;
      }
      // copy-based return
      return *instruction;
   }

   //public static implicit operator byte[](Script script) => script._value;
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_SCRIPT_HPP