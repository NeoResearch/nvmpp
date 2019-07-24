#ifndef NEOPT_NVM_EXECUTIONCONTEXT_HPP
#define NEOPT_NVM_EXECUTIONCONTEXT_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/Dictionary.hpp>
#include <system/printable.h>
#include <system/vhelper.hpp>

#include "RandomAccessStack.hpp"
#include "Script.hpp"
#include "StackItem.h"

using namespace std; // TODO: remove

namespace neopt {
namespace nvm {

class ExecutionContext
{
public: // (internal?)
        /// <summary>
   /// Number of items to be returned
   /// </summary>
   int RVCount; // get?

public:
   /// <summary>
   /// Script
   /// </summary>
   Script Script; // get?

   /// <summary>
   /// Evaluation stack
   /// </summary>
   RandomAccessStack<StackItem> EvaluationStack; // get?

   /// <summary>
   /// Alternative stack
   /// </summary>
   RandomAccessStack<StackItem> AltStack; // get?

   /// <summary>
   /// Instruction pointer
   /// </summary>
   int InstructionPointer; // get set ?

   Instruction CurrentInstruction()
   {
      return GetInstruction(InstructionPointer);
   }

   /// <summary>
   /// Next instruction
   /// </summary>
   Instruction NextInstruction()
   {
      return GetInstruction(InstructionPointer + CurrentInstruction().Size());
   }

   nvm::Script* CallingScript; // get?

   /// <summary>
   /// Constructor
   /// </summary>
   /// <param name="script">Script</param>
   /// <param name="callingScript">The calling script</param>
   /// <param name="rvcount">Number of items to be returned</param>
public: // (internal?)
   ExecutionContext(nvm::Script script, nvm::Script* callingScript, int rvcount)
     : ExecutionContext(script, callingScript, rvcount, RandomAccessStack<StackItem>(), RandomAccessStack<StackItem>())
   {
   }

private:
   // copy based stack (TODO: improve or change this)
   ExecutionContext(nvm::Script script, nvm::Script* callingScript, int rvcount, RandomAccessStack<StackItem> stack, RandomAccessStack<StackItem> alt)
   {
      this->RVCount = rvcount;
      this->Script = script;
      this->EvaluationStack = stack;
      this->AltStack = alt;
      this->CallingScript = callingScript;
   }

public: // (internal?)
   ExecutionContext* Clone()
   {
      return new ExecutionContext(Script, new nvm::Script(Script), 0, EvaluationStack, AltStack);
   }

private:
   Instruction GetInstruction(int ip)
   {
      return Script.GetInstruction(ip);
   }

public: // (internal?)
   bool MoveNext()
   {
      InstructionPointer += CurrentInstruction().Size();
      return InstructionPointer < Script.Length;
   }
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_EXECUTIONCONTEXT_HPP