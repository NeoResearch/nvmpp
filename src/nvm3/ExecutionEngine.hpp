#ifndef NEOPT_NVM_EXECUTIONENGINE_HPP
#define NEOPT_NVM_EXECUTIONENGINE_HPP

// c++ standard part
#include <vector>
#include <queue>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/Dictionary.hpp>
#include <system/printable.h>
#include <system/vhelper.hpp>

#include "ExecutionEngineLimits.h"
#include "ExecutionContext.hpp"
#include "RandomAccessStack.hpp"
#include "Script.hpp"
#include "StackItem.h"
#include "VMState.h"
#include "Types/Array.hpp"
#include "Types/Boolean.hpp"
#include "Types/ByteArray.hpp"
#include "Types/Integer.hpp"
#include "Types/InteropInterface.hpp"
#include "Types/Map.hpp"
#include "Types/Struct.hpp"

using namespace std; // TODO: remove

namespace neopt {
namespace nvm {

class ExecutionEngine
{
public:

        //#region Limits Variables
        ExecutionEngineLimits Limits; // TODO: allow inheritance rewritting (ref or pointer)
        //#endregion

private:
        static vbyte EmptyBytes;

        int stackitem_count = 0;
        bool is_stackitem_count_strict = true;

public:
        RandomAccessStack<ExecutionContext> InvocationStack; // get?
        RandomAccessStack<StackItem> ResultStack; // get?

        ExecutionContext* CurrentContext() {
           return InvocationStack.Count() > 0 ? InvocationStack.Peek() : nullptr;
        }

        ExecutionContext* EntryContext()
        {
           return InvocationStack.Count() > 0 ? InvocationStack.Peek(InvocationStack.Count - 1) : nullptr;
        } 

        //VMState getState(){ //{ get; internal protected set; } = VMState.BREAK;
        // return VMState::VMS_BREAK; // TODO: protected set
        //} 

        VMState State = VMState::VMS_BREAK;

        bool StateHasFlag(VMState flag) // TODO: C# does this automatically
        {
           return false; // TODO
        }

         // TODO: manage events
        //#region Events
        //public event EventHandler<ExecutionContext> ContextLoaded;
        //public event EventHandler<ExecutionContext> ContextUnloaded;
        //#endregion

private:
         /// <summary>
        /// Check if the is possible to overflow the MaxStackSize
        /// </summary>
        /// <param name="strict">Is stack count strict?</param>
        /// <param name="count">Stack item count</param>
        /// <returns></returns>
        bool CheckStackSize(bool strict, int count = 1)
        {
            is_stackitem_count_strict &= strict;
            stackitem_count += count;

            if (stackitem_count < 0) stackitem_count = int.MaxValue;
            if (stackitem_count <= Limits.MaxStackSize()) return true;
            if (is_stackitem_count_strict) return false;

            // Deep inspect

            // TODO: MAKE DEEP INSPECTION!
            /// stackitem_count = GetItemCount(InvocationStack.Select(p => p.EvaluationStack).Distinct().Concat(InvocationStack.Select(p => p.AltStack).Distinct()).SelectMany(p => p));
            if (stackitem_count > Limits.MaxStackSize()) return false;
            is_stackitem_count_strict = true;

            return true;
        }

        

        /// <summary>
        /// Get item count
        /// </summary>
        /// <param name="items">Items</param>
        /// <returns>Return the number of items</returns>
        static int GetItemCount(std::vector<StackItem> items) // IEnumerable<StackItem> items
        {
            std::queue<StackItem*> queue; //= new Queue<StackItem>(items);
            std::vector<StackItem*> counted; //= new List<StackItem>();
            int count = 0;
            while (queue.size() > 0)
            {
                StackItem* item = queue.front(); // Dequeue
                queue.pop(); // delete?
                count++;
                switch (item->type)
                {
                   // TODO: verify this part... see better portability option
                    case SIT_Array:
                        {
                           nvm::Array& array = (nvm::Array&)*item;
                            if (counted.Any(p => ReferenceEquals(p, array)))
                                continue;
                            counted.Add(array);
                            foreach (StackItem subitem in array)
                                queue.Enqueue(subitem);
                            break;
                        }
                    case SIT_Map:
                        {
                           nvm::Map& map = (nvm::Map&)*item;
                            if (counted.Any(p => ReferenceEquals(p, map)))
                                continue;
                            counted.Add(map);
                            count += map.Count; // Count key items
                            foreach (StackItem subitem in map.Values)
                                queue.Enqueue(subitem);
                            break;
                        }
                }
            }
            return count;
        }

        
public:
        //public virtual void Dispose()
        //{
        //    InvocationStack.Clear();
        //}
        
        virtual ~ExecutionEngine()
        {
           // TODO: so much more to deallocate here...
           InvocationStack.Clear();
        }

        nvm::VMState Execute()
        {
            State &= ~VMState::VMS_BREAK;
            while (!StateHasFlag(VMState::VMS_HALT) && !StateHasFlag(VMState::VMS_FAULT))
                ExecuteNext();
            return State;
        }

protected: // (internal?)
        void ExecuteNext()
        {
            if (InvocationStack.Count == 0)
            {
                State = VMState::VMS_HALT;
            }
            else
            {
                //try
                //{
                    Instruction instruction = CurrentContext()->CurrentInstruction;
                    if (!PreExecuteInstruction() || !ExecuteInstruction() || !PostExecuteInstruction(instruction))
                        State = VMState::VMS_FAULT;
                //}
                //catch
                //{
                //    State = VMState::VMS_FAULT;
                //}

                // TODO: alternative to exception handling here? Or is it absolutely necessary?
            }
        }

private:
        bool ExecuteInstruction()
        {
            ExecutionContext& context = *CurrentContext(); // TODO: verify pointer?
            Instruction instruction = context.CurrentInstruction;
            if (instruction.OpCode >= OpCode::OP_PUSHBYTES1 && instruction.OpCode <= OpCode::OP_PUSHDATA4)
            {
                if (!Limits.CheckMaxItemSize(instruction.Operand.size())) return false;
                context.EvaluationStack.Push(new ByteArray(instruction.Operand));
                if (!CheckStackSize(true)) return false;
            }
            else switch (instruction.OpCode)
                {
                    // Push value
                    case OpCode::OP_PUSH0:
                        {
                            context.EvaluationStack.Push(new ByteArray(EmptyBytes));
                            if (!CheckStackSize(true)) return false;
                            break;
                        }
                    case OpCode::OP_PUSHM1:
                    case OpCode::OP_PUSH1:
                    case OpCode::OP_PUSH2:
                    case OpCode::OP_PUSH3:
                    case OpCode::OP_PUSH4:
                    case OpCode::OP_PUSH5:
                    case OpCode::OP_PUSH6:
                    case OpCode::OP_PUSH7:
                    case OpCode::OP_PUSH8:
                    case OpCode::OP_PUSH9:
                    case OpCode::OP_PUSH10:
                    case OpCode::OP_PUSH11:
                    case OpCode::OP_PUSH12:
                    case OpCode::OP_PUSH13:
                    case OpCode::OP_PUSH14:
                    case OpCode::OP_PUSH15:
                    case OpCode::OP_PUSH16:
                        {
                            context.EvaluationStack.Push(new nvm::Integer((int)instruction.OpCode - (int)OpCode::OP_PUSH1 + 1));
                            if (!CheckStackSize(true)) return false;
                            break;
                        }

                    // Control
                    case OpCode::OP_NOP: break;
                    case OpCode::OP_JMP:
                    case OpCode::OP_JMPIF:
                    case OpCode::OP_JMPIFNOT:
                        {
                            int offset = context.InstructionPointer + instruction.TokenI16;
                            if (offset < 0 || offset > context.Script.Length) return false;
                            bool fValue = true;
                            if (instruction.OpCode > OpCode::OP_JMP)
                            {
                                CheckStackSize(false, -1);
                                fValue = context.EvaluationStack.Pop()->GetBoolean();

                                if (instruction.OpCode == OpCode::OP_JMPIFNOT)
                                    fValue = !fValue;
                            }
                            if (fValue)
                                context.InstructionPointer = offset;
                            else
                                context.InstructionPointer += 3;
                            return true;
                        }
                    case OpCode::OP_CALL:
                        {
                            ExecutionContext& context_call = *context.Clone(); // verify pointer?
                            context_call.InstructionPointer = context.InstructionPointer + instruction.TokenI16;
                            if (context_call.InstructionPointer < 0 || context_call.InstructionPointer > context_call.Script.Length) return false;
                            LoadContext(context_call);
                            break;
                        }
                    case OpCode::OP_RET:
                        {
                            ExecutionContext& context_pop = *InvocationStack.Pop(); // verify pointer
                            int rvcount = context_pop.RVCount;
                            if (rvcount == -1) rvcount = context_pop.EvaluationStack.Count;
                            if (rvcount > 0)
                            {
                                if (context_pop.EvaluationStack.Count < rvcount) return false;
                                RandomAccessStack<StackItem> stack_eval;
                                if (InvocationStack.Count == 0)
                                    stack_eval = ResultStack;
                                else
                                    stack_eval = CurrentContext()->EvaluationStack; // verify pointer?
                                context_pop.EvaluationStack.CopyTo(stack_eval, rvcount);
                            }
                            if (context_pop.RVCount == -1 && InvocationStack.Count > 0)
                            {
                                context_pop.AltStack.CopyTo(CurrentContext()->AltStack); // verify pointer?
                            }
                            CheckStackSize(false, 0);

                           // TODO: implement event (callback?)
                            //ContextUnloaded?.Invoke(this, context_pop);

                            if (InvocationStack.Count == 0)
                            {
                                State = VMState::VMS_HALT;
                            }
                            return true;
                        }
                    case OpCode::OP_SYSCALL:
                        {
                            if (!OnSysCall(instruction.TokenU32) || !CheckStackSize(false, int.MaxValue))
                                return false;
                            break;
                        }

                    // Stack ops
                    case OpCode::OP_DUPFROMALTSTACKBOTTOM:
                        {
                            auto item = context.AltStack.Peek(context.AltStack.Count - 1);
                            context.EvaluationStack.Push(item);
                            if (!CheckStackSize(true)) return false;
                            break;
                        }
                    case OpCode::OP_DUPFROMALTSTACK:
                        {
                            context.EvaluationStack.Push(context.AltStack.Peek());
                            if (!CheckStackSize(true)) return false;
                            break;
                        }
                    case OpCode::OP_TOALTSTACK:
                        {
                            context.AltStack.Push(context.EvaluationStack.Pop());
                            break;
                        }
                    case OpCode::OP_FROMALTSTACK:
                        {
                            context.EvaluationStack.Push(context.AltStack.Pop());
                            break;
                        }
                    case OpCode::OP_XDROP:
                        {
                            int n = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            if (n < 0) return false;
                            context.EvaluationStack.Remove(n);
                            CheckStackSize(false, -2);
                            break;
                        }
                    case OpCode::OP_XSWAP:
                        {
                            int n = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            if (n < 0) return false;
                            CheckStackSize(true, -1);
                            if (n == 0) break;
                            StackItem* xn = context.EvaluationStack.Peek(n);
                            context.EvaluationStack.Set(n, context.EvaluationStack.Peek());
                            context.EvaluationStack.Set(0, xn);
                            break;
                        }
                    case OpCode::OP_XTUCK:
                        {
                            int n = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            if (n <= 0) return false;
                            context.EvaluationStack.Insert(n, context.EvaluationStack.Peek());
                            break;
                        }
                    case OpCode::OP_DEPTH:
                        {
                            context.EvaluationStack.Push(context.EvaluationStack.Count);
                            if (!CheckStackSize(true)) return false;
                            break;
                        }
                    case OpCode::OP_DROP:
                        {
                            context.EvaluationStack.Pop();
                            CheckStackSize(false, -1);
                            break;
                        }
                    case OpCode::OP_DUP:
                        {
                            context.EvaluationStack.Push(context.EvaluationStack.Peek());
                            if (!CheckStackSize(true)) return false;
                            break;
                        }
                    case OpCode::OP_NIP:
                        {
                            context.EvaluationStack.Remove(1);
                            CheckStackSize(false, -1);
                            break;
                        }
                    case OpCode::OP_OVER:
                        {
                            context.EvaluationStack.Push(context.EvaluationStack.Peek(1));
                            if (!CheckStackSize(true)) return false;
                            break;
                        }
                    case OpCode::OP_PICK:
                        {
                            int n = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            if (n < 0) return false;
                            context.EvaluationStack.Push(context.EvaluationStack.Peek(n));
                            break;
                        }
                    case OpCode::OP_ROLL:
                        {
                            int n = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            if (n < 0) return false;
                            CheckStackSize(true, -1);
                            if (n == 0) break;
                            context.EvaluationStack.Push(context.EvaluationStack.Remove(n));
                            break;
                        }
                    case OpCode::OP_ROT:
                        {
                            context.EvaluationStack.Push(context.EvaluationStack.Remove(2));
                            break;
                        }
                    case OpCode::OP_SWAP:
                        {
                            context.EvaluationStack.Push(context.EvaluationStack.Remove(1));
                            break;
                        }
                    case OpCode::OP_TUCK:
                        {
                            context.EvaluationStack.Insert(2, context.EvaluationStack.Peek());
                            if (!CheckStackSize(true)) return false;
                            break;
                        }
                    case OpCode::OP_CAT:
                        {
                            vbyte x2 = context.EvaluationStack.Pop()->GetByteArray();
                            vbyte x1 = context.EvaluationStack.Pop()->GetByteArray();
                            vbyte result;
                            if (x1.size() == 0)
                            {
                                result = x2;
                            }
                            else if (x2.size() == 0)
                            {
                                result = x1;
                            }
                            else
                            {
                                int length = x1.size() + x2.size();
                                if (!Limits.CheckMaxItemSize(length)) return false;
                                result = vbyte(length);

                              // TODO: perform memory copies
                                //Unsafe.MemoryCopy(x1, 0, result, 0, x1.Length);
                                //Unsafe.MemoryCopy(x2, 0, result, x1.Length, x2.Length);
                            }
                            context.EvaluationStack.Push(new ByteArray(result));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_SUBSTR:
                        {
                            int count = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            if (count < 0) return false;
                            int index = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            if (index < 0) return false;
                            vbyte x = context.EvaluationStack.Pop()->GetByteArray();
                            if (index > x.size()) return false;
                            if (index + count > x.size()) count = x.size() - index;
                            vbyte buffer = vbyte(count);
                            // TODO: memory copy
                            //Unsafe.MemoryCopy(x, index, buffer, 0, count);
                            context.EvaluationStack.Push(new ByteArray(buffer));
                            CheckStackSize(true, -2);
                            break;
                        }
                    case OpCode::OP_LEFT:
                        {
                            int count = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            if (count < 0) return false;
                            vbyte x = context.EvaluationStack.Pop()->GetByteArray();
                            vbyte buffer;
                            if (count >= x.size())
                            {
                                buffer = x;
                            }
                            else
                            {
                                buffer = vbyte(count);
                                // TODO: memory copy
                                //Unsafe.MemoryCopy(x, 0, buffer, 0, count);
                            }
                            context.EvaluationStack.Push(new ByteArray(buffer));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_RIGHT:
                        {
                            int count = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            if (count < 0) return false;
                            vbyte x = context.EvaluationStack.Pop()->GetByteArray();
                            if (count > x.size()) return false;
                            vbyte buffer;
                            if (count == x.size())
                            {
                                buffer = x;
                            }
                            else
                            {
                                buffer = vbyte(count);
                                // TODO: memory copy
                                //Unsafe.MemoryCopy(x, x.Length - count, buffer, 0, count);
                            }
                            context.EvaluationStack.Push(new ByteArray(buffer));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_SIZE:
                        {
                            StackItem* x = context.EvaluationStack.Pop();
                            context.EvaluationStack.Push(new nvm::Integer(x->GetByteLength()));
                            break;
                        }

                    // Bitwise logic
                    case OpCode::OP_INVERT:
                        {
                            BigInteger x = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x)) return false;
                            context.EvaluationStack.Push(new Integer(~x));
                            break;
                        }
                    case OpCode::OP_AND:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Integer(x1 & x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_OR:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Integer(x1 | x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_XOR:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Integer(x1 ^ x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_EQUAL:
                        {
                            StackItem* x2 = context.EvaluationStack.Pop();
                            StackItem* x1 = context.EvaluationStack.Pop();
                            context.EvaluationStack.Push(new Boolean(x1->Equals(x2)));
                            CheckStackSize(false, -1);
                            break;
                        }

                    // Numeric
                    case OpCode::OP_INC:
                        {
                            BigInteger x = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x)) return false;
                            x += 1;
                            if (!Limits.CheckBigInteger(x)) return false;
                            context.EvaluationStack.Push(new Integer(x));
                            break;
                        }
                    case OpCode::OP_DEC:
                        {
                            BigInteger x = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x)) return false;
                            x -= 1;
                            if (!Limits.CheckBigInteger(x)) return false;
                            context.EvaluationStack.Push(new Integer(x));
                            break;
                        }
                    case OpCode::OP_SIGN:
                        {
                            BigInteger x = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x)) return false;
                            context.EvaluationStack.Push(new Integer(x.Sign()));
                            break;
                        }
                    case OpCode::OP_NEGATE:
                        {
                            BigInteger x = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x)) return false;
                            context.EvaluationStack.Push(new Integer(-x));
                            break;
                        }
                    case OpCode::OP_ABS:
                        {
                            BigInteger x = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x)) return false;
                            context.EvaluationStack.Push(new Integer(BigInteger::Abs(x)));
                            break;
                        }
                    case OpCode::OP_NOT:
                        {
                            bool x = context.EvaluationStack.Pop()->GetBoolean();
                            context.EvaluationStack.Push(new Boolean(!x));
                            CheckStackSize(false, 0);
                            break;
                        }
                    case OpCode::OP_NZ:
                        {
                            BigInteger x = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x)) return false;
                            context.EvaluationStack.Push(!x.IsZero);
                            break;
                        }
                    case OpCode::OP_ADD:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            BigInteger result = x1 + x2;
                            if (!Limits.CheckBigInteger(result)) return false;
                            context.EvaluationStack.Push(new Integer(result));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_SUB:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            BigInteger result = x1 - x2;
                            if (!Limits.CheckBigInteger(result)) return false;
                            context.EvaluationStack.Push(new Integer(result));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_MUL:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            BigInteger result = x1 * x2;
                            if (!Limits.CheckBigInteger(result)) return false;
                            context.EvaluationStack.Push(new Integer(result));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_DIV:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Integer(x1 / x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_MOD:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Integer(x1 % x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_SHL:
                        {
                            int shift = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            CheckStackSize(true, -1);
                            if (!Limits.CheckShift(shift)) return false;
                            if (shift == 0) break;
                            BigInteger x = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x)) return false;
                            x <<= shift;
                            if (!Limits.CheckBigInteger(x)) return false;
                            context.EvaluationStack.Push(new Integer(x));
                            break;
                        }
                    case OpCode::OP_SHR:
                        {
                            int shift = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            CheckStackSize(true, -1);
                            if (!Limits.CheckShift(shift)) return false;
                            if (shift == 0) break;
                            BigInteger x = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x)) return false;
                            x >>= shift;
                            if (!Limits.CheckBigInteger(x)) return false;
                            context.EvaluationStack.Push(new Integer(x));
                            break;
                        }
                    case OpCode::OP_BOOLAND:
                        {
                            bool x2 = context.EvaluationStack.Pop()->GetBoolean();
                            bool x1 = context.EvaluationStack.Pop()->GetBoolean();
                            context.EvaluationStack.Push(new Boolean(x1 && x2));
                            CheckStackSize(false, -1);
                            break;
                        }
                    case OpCode::OP_BOOLOR:
                        {
                            bool x2 = context.EvaluationStack.Pop()->GetBoolean();
                            bool x1 = context.EvaluationStack.Pop()->GetBoolean();
                            context.EvaluationStack.Push(new Boolean(x1 || x2));
                            CheckStackSize(false, -1);
                            break;
                        }
                    case OpCode::OP_NUMEQUAL:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Boolean(x1 == x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_NUMNOTEQUAL:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Boolean(x1 != x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_LT:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Boolean(x1 < x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_GT:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Boolean(x1 > x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_LTE:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Boolean(x1 <= x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_GTE:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Integer(x1 >= x2));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_MIN:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Integer(BigInteger::Min(x1, x2)));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_MAX:
                        {
                            BigInteger x2 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x2)) return false;
                            BigInteger x1 = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x1)) return false;
                            context.EvaluationStack.Push(new Integer(BigInteger::Max(x1, x2)));
                            CheckStackSize(true, -1);
                            break;
                        }
                    case OpCode::OP_WITHIN:
                        {
                            BigInteger b = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(b)) return false;
                            BigInteger a = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(a)) return false;
                            BigInteger x = context.EvaluationStack.Pop()->GetBigInteger();
                            if (!Limits.CheckBigInteger(x)) return false;
                            context.EvaluationStack.Push(new Boolean(a <= x && x < b));
                            CheckStackSize(true, -2);
                            break;
                        }

                    // Array
                    case OpCode::OP_ARRAYSIZE:
                        {
                            StackItem* item = context.EvaluationStack.Pop();
                            // TODO: which stack items are Collections? Array? Struct? Map?
                            if (item->type == SIT_Array) // is ICollection collection)
                            {
                                 // TODO: discuss this first
                                //context.EvaluationStack.Push(collection.Count);
                                CheckStackSize(false, 0);
                            }
                            else
                            {
                                context.EvaluationStack.Push(new Integer(item->GetByteLength()));
                                CheckStackSize(true, 0);
                            }
                            break;
                        }
                    case OpCode::OP_PACK:
                        {
                            int size = (int)context.EvaluationStack.Pop()->GetBigInteger().toInt();
                            if (size < 0 || size > context.EvaluationStack.Count || !Limits.CheckArraySize(size))
                                return false;
                            vector<StackItem*> items;
                            for (int i = 0; i < size; i++)
                                items.push_back(context.EvaluationStack.Pop());
                            context.EvaluationStack.Push(items);
                            break;
                        }
                    case OpCode::OP_UNPACK:
                        {
                           StackItem* item = context.EvaluationStack.Pop();
                            if (!(item->type == SIT_Array))
                                return false;
                           nvm::Array& array = (Array&)*item;
                            for (int i = array.Count() - 1; i >= 0; i--)
                                context.EvaluationStack.Push(&array[i]); // pushing pointer here, beware!
                            context.EvaluationStack.Push(new Integer(array.Count()));
                            if (!CheckStackSize(false, array.Count)) return false;
                            break;
                        }
                    case OpCode::OP_PICKITEM:
                        {
                            StackItem* key = context.EvaluationStack.Pop();
                            if (key->IsCollection()) return false;
                            StackItem* item = context.EvaluationStack.Pop();
                            switch (item->type)
                            {
                                case SIT_Array:
                                    {
                                       nvm::Array& array = (Array&)*item;
                                        int index = (int)key->GetBigInteger().toInt();
                                        if (index < 0 || index >= array.Count) return false;
                                        context.EvaluationStack.Push(&array[index]); // pushing pointer here, beware!
                                        CheckStackSize(false, -1);
                                        break;
                                    }
                                case SIT_Map:
                                    {
                                       nvm::Map& map = (Map&)*item;
                                       StackItem* value = map.TryGetValue(*key);
                                        if (!value) return false;
                                        context.EvaluationStack.Push(value);
                                        CheckStackSize(false, -1);
                                        break;
                                    }
                                default:
                                    {
                                        vbyte byteArray = item->GetByteArray();
                                        int index = (int)key->GetBigInteger().toInt();
                                        if (index < 0 || index >= byteArray.size()) return false;
                                        context.EvaluationStack.Push(new Integer((int)byteArray[index]));
                                        CheckStackSize(true, -1);
                                        break;
                                    }
                            }
                            break;
                        }
                    case OpCode::OP_SETITEM:
                        {
                            StackItem* value = context.EvaluationStack.Pop();
                            if (value->type == SIT_Struct)
                            { 
                               nvm::Struct& s = (Struct&)*value;
                               value = s.Clone();
                            }
                            StackItem* key = context.EvaluationStack.Pop();
                            if (key->IsCollection()) return false;
                            StackItem* item = context.EvaluationStack.Pop();
                            switch (item->type)
                            {
                                case SIT_Array:
                                    {
                                       nvm::Array& array = (Array&)*item;
                                        int index = (int)key->GetBigInteger().toInt();
                                        if (index < 0 || index >= array.Count) return false;
                                        array[index] = *value;
                                        break;
                                    }
                                case SIT_Map:
                                    {
                                       nvm::Map& map = (Map&)*item;
                                        if (!map.ContainsKey(*key) && !Limits.CheckArraySize(map.Count + 1))
                                            return false;
                                        map[*key] = *value;
                                        break;
                                    }
                                default:
                                    return false;
                            }

                            if (!CheckStackSize(false, int.MaxValue))
                                return false;

                            break;
                        }
                    case OpCode::OP_NEWARRAY:
                    case OpCode::OP_NEWSTRUCT:
                        {
                            StackItem* item = context.EvaluationStack.Pop();

                            if (item->type == SIT_Array)
                            {
                               nvm::Array& array = (Array&)*item;
                                // Allow to convert between array and struct

                                nvm::Array* result = nullptr;

                                if (array is Struct) // TODO: improve this
                                {
                                    if (instruction.OpCode == OpCode::OP_NEWSTRUCT)
                                        result = array;
                                }
                                else
                                {
                                    if (instruction.OpCode == OpCode::OP_NEWARRAY)
                                        result = array;
                                }

                                if (result == nullptr)
                                    result = instruction.OpCode == OpCode::OP_NEWARRAY
                                        ? new nvm::Array(array)
                                        : new nvm::Struct(array);

                                context.EvaluationStack.Push(result);
                            }
                            else
                            {
                                int count = (int)item->GetBigInteger().toInt();

                                if (count < 0 || !Limits.CheckArraySize(count)) return false;

                                vector<StackItem*> items(count);

                                for (auto i = 0; i < count; i++)
                                {
                                    items.push_back(new Boolean(false));
                                }

                                nvm::Array* result = instruction.OpCode == OpCode::OP_NEWARRAY
                                    ? new nvm::Array(items)
                                    : new nvm::Struct(items);

                                context.EvaluationStack.Push(result);

                                if (!CheckStackSize(true, count)) return false;
                            }
                            break;
                        }
                    case OpCode::OP_NEWMAP:
                        {
                            context.EvaluationStack.Push(new nvm::Map());
                            if (!CheckStackSize(true)) return false;
                            break;
                        }
                    case OpCode::OP_APPEND:
                        {
                            StackItem* newItem = context.EvaluationStack.Pop();
                            if (newItem->type == SIT_Struct)
                            {
                               nvm::Struct& s = (Struct&)*newItem;
                               newItem = s.Clone();
                            } 
                            StackItem* arrItem = context.EvaluationStack.Pop();
                            if (!(arrItem->type == SIT_Array)) return false;
                            nvm::Array& array = (Array&)*arrItem;
                            if (!Limits.CheckArraySize(array.Count() + 1)) return false;
                            array.Add(newItem);
                            if (!CheckStackSize(false, int.MaxValue)) return false;
                            break;
                        }
                    case OpCode::OP_REVERSE:
                        {
                            StackItem* arrItem = context.EvaluationStack.Pop();
                            CheckStackSize(false, -1);
                            if (!(arrItem->type == SIT_Array)) return false;
                            nvm::Array& array = (Array&)*arrItem;
                            array.Reverse();
                            break;
                        }
                    case OpCode::OP_REMOVE:
                        {
                            StackItem* key = context.EvaluationStack.Pop();
                            if (key->IsCollection()) return false;
                            StackItem* value = context.EvaluationStack.Pop();
                            CheckStackSize(false, -2);
                            switch (value->type)
                            {
                                case SIT_Array:
                                    nvm::Array& array = (Array&)*value;
                                    int index = (int)key->GetBigInteger().toInt();
                                    if (index < 0 || index >= array.Count) return false;
                                    array.RemoveAt(index);
                                    CheckStackSize(false, -1);
                                    break;
                                case SIT_Map:
                                    nvm::Map& map = (Map&)*value;
                                    if (map.Remove(*key))
                                        CheckStackSize(false, -2);
                                    break;
                                default:
                                    return false;
                            }
                            break;
                        }
                    case OpCode::OP_HASKEY:
                        {
                            StackItem* key = context.EvaluationStack.Pop();
                            if (key->IsCollection()) return false;
                            StackItem* item = context.EvaluationStack.Pop();
                            switch (item->type)
                            {
                                case SIT_Array:
                                    nvm::Array& array = (Array&)*item;
                                    int index = (int)key->GetBigInteger().toInt();
                                    if (index < 0) return false;
                                    context.EvaluationStack.Push(new Boolean(index < array.Count));
                                    break;
                                case SIT_Map:
                                nvm::Map& map = (Map&)*item;
                                    context.EvaluationStack.Push(new Boolean(map.ContainsKey(*key)));
                                    break;
                                default:
                                    return false;
                            }
                            CheckStackSize(false, -1);
                            break;
                        }
                    case OpCode::OP_KEYS:
                        {
                           StackItem* item = context.EvaluationStack.Pop();
                            if (!(item->type == SIT_Map)) return false;
                            nvm::Map& map = (Map&)*item;
                            context.EvaluationStack.Push(new nvm::Array(map.Keys)); // TODO: keys?
                            if (!CheckStackSize(false, map.Count)) return false;
                            break;
                        }
                    case OpCode::OP_VALUES:
                        {
                            //ICollection<StackItem> values;
                            std::vector<StackItem*> values;
                            StackItem* item = context.EvaluationStack.Pop();
                            switch (item->type)
                            {
                                case SIT_Array:
                                    nvm::Array& array = (Array&)*item;
                                    values = array;
                                    break;
                                case SIT_Map:
                                    nvm::Map& map = (Map&)*item;
                                    values = map.Values; // values?? TODO
                                    break;
                                default:
                                    return false;
                            }
                            vector<StackItem*> newArray(values.size());
                            foreach (StackItem item in values)
                                if (item is Struct s)
                                    newArray.Add(s.Clone());
                                else
                                    newArray.Add(item);
                            context.EvaluationStack.Push(new VMArray(newArray));
                            if (!CheckStackSize(false, int.MaxValue)) return false;
                            break;
                        }

                    // Exceptions
                    case OpCode::OP_THROW:
                        {
                            return false;
                        }
                    case OpCode::OP_THROWIFNOT:
                        {
                            if (!context.EvaluationStack.Pop()->GetBoolean())
                                return false;
                            CheckStackSize(false, -1);
                            break;
                        }
                    default:
                        return false;
                }
            context.MoveNext();
            return true;
        }

private:
        void LoadContext(ExecutionContext& context)
        {
            if (InvocationStack.Count >= Limits.MaxInvocationStackSize)
            {
                //throw new InvalidOperationException();
                NEOPT_EXCEPTION("InvalidOperationException");
            }
            InvocationStack.Push(&context); // TODO: beware pushing pointers

            // TODO: events... (callback?)
            //ContextLoaded?.Invoke(this, context);
        }
public:
        ExecutionContext& LoadScript(vbyte script, int rvcount = -1)
        {
            ExecutionContext* context;
            nvm::Script* calling = CurrentContext() ? new nvm::Script(CurrentContext()->Script) : nullptr;
            context = new ExecutionContext(Script(script), calling, rvcount);
            LoadContext(*context);
            return *context;
        }

protected:
        virtual bool OnSysCall(uint method)
        {
           return false;
        }

        virtual bool PostExecuteInstruction(Instruction instruction)
        {
           return true;
        }

        virtual bool PreExecuteInstruction()
        {
           return true;
        }
    
};

// static assignment (TODO: rethink)

vbyte ExecutionEngine::EmptyBytes = vbyte(0);

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_EXECUTIONENGINE_HPP