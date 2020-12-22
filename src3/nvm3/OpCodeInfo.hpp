#ifndef NVM3_OPCODE_TEXT_HPP
#define NVM3_OPCODE_TEXT_HPP

// c++ standard part
#include <array>
#include <string>
// ..
#include "OpCode.hpp"

namespace nvm3 {
//
struct OpCodeInfo
{
   uint8_t code;                 // opcode code number
   std::string_view name;        // opcode name
   int opSize;                   // operand size
   int opPrefixSize;             // operand prefix size (real size may be variable)
   std::string_view description; // opcode description

   constexpr OpCodeInfo(uint8_t code,
                        const char* name,
                        int opSize,
                        int opPrefixSize,
                        const char* description)
     : code{ code }
     , name{ name }
     , opSize{ opSize }
     , opPrefixSize{ opPrefixSize }
     , description{ description }
   {}
};

struct OpCodeInfoGlobal
{
   constexpr static std::array<OpCodeInfo, 220> oplist = {
      //#region Constants
      OpCodeInfo{ 0x00, "PUSHINT8", 1, 0, "PUSH INT WITH 8 BITS" },
      OpCodeInfo{ 0x01, "PUSHINT16", 2, 0, "PUSH INT WITH 16 BITS" },
      OpCodeInfo{ 0x02, "PUSHINT32", 4, 0, "PUSH INT WITH 32 BITS" },
      OpCodeInfo{ 0x03, "PUSHINT64", 8, 0, "PUSH INT WITH 64 BITS" },
      OpCodeInfo{ 0x04, "PUSHINT128", 16, 0, "PUSH INT WITH 128 BITS" },
      OpCodeInfo{ 0x05, "PUSHINT256", 32, 0, "PUSH INT WITH 256 BITS" },
      OpCodeInfo{ 0x06, "0x06", 0, 0, "unused" },
      OpCodeInfo{ 0x07, "0x07", 0, 0, "unused" },
      OpCodeInfo{ 0x08, "0x08", 0, 0, "unused" },
      OpCodeInfo{ 0x09, "0x09", 0, 0, "unused" },
      OpCodeInfo{ 0x0a, "PUSHA", 4, 0, "Convert the next four bytes to an address, and push the address onto the stack." },
      OpCodeInfo{ 0x0b, "PUSHNULL", 0, 0, "The item null is pushed onto the stack." },
      OpCodeInfo{ 0x0c, "PUSHDATA1", 0, 1, "The item null is pushed onto the stack." },
      OpCodeInfo{ 0x0d, "PUSHDATA2", 0, 2, "The next two bytes contain the number of bytes to be pushed onto the stack." },
      OpCodeInfo{ 0x0e, "PUSHDATA4", 0, 4, "The next four bytes contain the number of bytes to be pushed onto the stack." },
      OpCodeInfo{ 0x0f, "PUSHM1", 0, 0, "The number -1 is pushed onto the stack." },
      OpCodeInfo{ 0x10, "PUSH0", 0, 0, "The number 0 is pushed onto the stack." },
      OpCodeInfo{ 0x11, "PUSH1", 0, 0, "The number 1 is pushed onto the stack." },
      OpCodeInfo{ 0x12, "PUSH2", 0, 0, "The number 2 is pushed onto the stack." },
      OpCodeInfo{ 0x13, "PUSH3", 0, 0, "The number 3 is pushed onto the stack." },
      OpCodeInfo{ 0x14, "PUSH4", 0, 0, "The number 4 is pushed onto the stack." },
      OpCodeInfo{ 0x15, "PUSH5", 0, 0, "The number 5 is pushed onto the stack." },
      OpCodeInfo{ 0x16, "PUSH6", 0, 0, "The number 6 is pushed onto the stack." },
      OpCodeInfo{ 0x17, "PUSH7", 0, 0, "The number 7 is pushed onto the stack." },
      OpCodeInfo{ 0x18, "PUSH8", 0, 0, "The number 8 is pushed onto the stack." },
      OpCodeInfo{ 0x19, "PUSH9", 0, 0, "The number 9 is pushed onto the stack." },
      OpCodeInfo{ 0x1a, "PUSH10", 0, 0, "The number 10 is pushed onto the stack." },
      OpCodeInfo{ 0x1b, "PUSH11", 0, 0, "The number 11 is pushed onto the stack." },
      OpCodeInfo{ 0x1c, "PUSH12", 0, 0, "The number 12 is pushed onto the stack." },
      OpCodeInfo{ 0x1d, "PUSH13", 0, 0, "The number 13 is pushed onto the stack." },
      OpCodeInfo{ 0x1e, "PUSH14", 0, 0, "The number 14 is pushed onto the stack." },
      OpCodeInfo{ 0x1f, "PUSH15", 0, 0, "The number 15 is pushed onto the stack." },
      OpCodeInfo{ 0x20, "PUSH16", 0, 0, "The number 16 is pushed onto the stack." },
      //#endregion // Constants
      //#region Flow control
      OpCodeInfo{ 0x21, "NOP", 0, 0, "The NOP operation does nothing. It is intended to fill in space if opcodes are patched." },
      OpCodeInfo{ 0x22, "JMP", 1, 0, "Unconditionally transfers control to a target instruction. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x23, "JMP_L", 4, 0, "Unconditionally transfers control to a target instruction. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x24, "JMPIF", 1, 0, "Transfers control to a target instruction if the value is true, not null, or non-zero. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x25, "JMPIF_L", 4, 0, "Transfers control to a target instruction if the value is true, not null, or non-zero. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x26, "JMPIFNOT", 1, 0, "Transfers control to a target instruction if the value is false, a null reference, or zero. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x27, "JMPIFNOT_L", 4, 0, "Transfers control to a target instruction if the value is false, a null reference, or zero. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x28, "JMPEQ", 1, 0, "Transfers control to a target instruction if two values are equal. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x29, "JMPEQ_L", 4, 0, "Transfers control to a target instruction if two values are equal. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x2A, "JMPNE", 1, 0, "Transfers control to a target instruction when two values are not equal. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x2B, "JMPNE_L", 4, 0, "Transfers control to a target instruction when two values are not equal. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x2C, "JMPGT", 1, 0, "Transfers control to a target instruction if the first value is greater than the second value. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x2D, "JMPGT_L", 4, 0, "Transfers control to a target instruction if the first value is greater than the second value. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x2E, "JMPGE", 1, 0, "Transfers control to a target instruction if the first value is greater than or equal to the second value. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x2F, "JMPGE_L", 4, 0, "Transfers control to a target instruction if the first value is greater than or equal to the second value. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x30, "JMPLT", 1, 0, "Transfers control to a target instruction if the first value is less than the second value. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x31, "JMPLT_L", 4, 0, "Transfers control to a target instruction if the first value is less than the second value. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x32, "JMPLE", 1, 0, "Transfers control to a target instruction if the first value is less than or equal to the second value. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x33, "JMPLE_L", 4, 0, "Transfers control to a target instruction if the first value is less than or equal to the second value. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x34, "CALL", 1, 0, "Calls the function at the target address which is represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x35, "CALL_L", 4, 0, "Calls the function at the target address which is represented as a 4-bytes signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x36, "CALLA", 0, 0, "Pop the address of a function from the stack, and call the function." },
      OpCodeInfo{ 0x37, "CALLT", 2, 0, "Calls the function which is described by the token." },
      OpCodeInfo{ 0x38, "ABORT", 0, 0, "It turns the vm state to FAULT immediately, and cannot be caught." },
      OpCodeInfo{ 0x39, "ASSERT", 0, 0, "Pop the top value of the stack, if it false, then exit vm execution and set vm state to FAULT." },
      OpCodeInfo{ 0x3A, "THROW", 0, 0, "Pop the top value of the stack, and throw it." },
      OpCodeInfo{ 0x3B, "TRY", 2, 0, "TRY CatchOffset(sbyte) FinallyOffset(sbyte). If there's no catch body, set CatchOffset 0. If there's no finally body, set FinallyOffset 0." },
      OpCodeInfo{ 0x3C, "TRY_L", 8, 0, "TRY_L CatchOffset(int) FinallyOffset(int). If there's no catch body, set CatchOffset 0. If there's no finally body, set FinallyOffset 0." },
      OpCodeInfo{ 0x3D, "ENDTRY", 1, 0, "Ensures that the appropriate surrounding finally blocks are executed. And then unconditionally transfers control to the specific target instruction, represented as a 1-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x3E, "ENDTRY_L", 4, 0, "Ensures that the appropriate surrounding finally blocks are executed. And then unconditionally transfers control to the specific target instruction, represented as a 4-byte signed offset from the beginning of the current instruction." },
      OpCodeInfo{ 0x3F, "ENDFINALLY", 0, 0, "End finally, If no exception happen or be catched, vm will jump to the target instruction of ENDTRY/ENDTRY_L. Otherwise vm will rethrow the exception to upper layer." },
      OpCodeInfo{ 0x40, "RET", 0, 0, "Returns from the current method." },
      OpCodeInfo{ 0x41, "SYSCALL", 4, 0, "Calls to an interop service." },
      //#endregion // Flow
      //#region Stack
      OpCodeInfo{ 0x42, "0x42", 0, 0, "unused" },
      OpCodeInfo{ 0x43, "DEPTH", 0, 0, "Puts the number of stack items onto the stack." },
      OpCodeInfo{ 0x44, "0x44", 0, 0, "unused" },
      OpCodeInfo{ 0x45, "DROP", 0, 0, "Removes the top stack item." },
      OpCodeInfo{ 0x46, "NIP", 0, 0, "Removes the second-to-top stack item." },
      OpCodeInfo{ 0x47, "0x47", 0, 0, "unused." },
      OpCodeInfo{ 0x48, "XDROP", 0, 0, "The item n back in the main stack is removed." },
      OpCodeInfo{ 0x49, "CLEAR", 0, 0, "Clear the stack." },
      OpCodeInfo{ 0x4a, "DUP", 0, 0, "Duplicates the top stack item." },
      OpCodeInfo{ 0x4b, "OVER", 0, 0, "Copies the second-to-top stack item to the top." },
      OpCodeInfo{ 0x4c, "0x4c", 0, 0, "unused." },
      OpCodeInfo{ 0x4d, "PICK", 0, 0, "The item n back in the stack is copied to the top." },
      OpCodeInfo{ 0x4e, "TUCK", 0, 0, "The item at the top of the stack is copied and inserted before the second-to-top item." },
      OpCodeInfo{ 0x4f, "0x4f", 0, 0, "unused." },
      OpCodeInfo{ 0x50, "SWAP", 0, 0, "The top two items on the stack are swapped." },
      OpCodeInfo{ 0x51, "ROT", 0, 0, "The top three items on the stack are rotated to the left." },
      OpCodeInfo{ 0x52, "ROLL", 0, 0, "The item n back in the stack is moved to the top." },
      OpCodeInfo{ 0x53, "REVERSE3", 0, 0, "Reverse the order of the top 3 items on the stack." },
      OpCodeInfo{ 0x54, "REVERSE4", 0, 0, "Reverse the order of the top 4 items on the stack." },
      OpCodeInfo{ 0x55, "REVERSEN", 0, 0, "Pop the number N on the stack, and reverse the order of the top N items on the stack." },
      //#endregion Stack
      //#region Slot
      OpCodeInfo{ 0x56, "INITSSLOT", 1, 0, "Initialize the static field list for the current execution context." },
      OpCodeInfo{ 0x57, "INITSLOT", 2, 0, "Initialize the argument slot and the local variable list for the current execution context." },
      OpCodeInfo{ 0x58, "LDSFLD0", 0, 0, "Loads the static field at index 0 onto the evaluation stack." },
      OpCodeInfo{ 0x59, "LDSFLD1", 0, 0, "Loads the static field at index 1 onto the evaluation stack." },
      OpCodeInfo{ 0x5a, "LDSFLD2", 0, 0, "Loads the static field at index 2 onto the evaluation stack." },
      OpCodeInfo{ 0x5b, "LDSFLD3", 0, 0, "Loads the static field at index 3 onto the evaluation stack." },
      OpCodeInfo{ 0x5c, "LDSFLD4", 0, 0, "Loads the static field at index 4 onto the evaluation stack." },
      OpCodeInfo{ 0x5d, "LDSFLD5", 0, 0, "Loads the static field at index 5 onto the evaluation stack." },
      OpCodeInfo{ 0x5e, "LDSFLD6", 0, 0, "Loads the static field at index 6 onto the evaluation stack." },
      OpCodeInfo{ 0x5f, "LDSFLD", 1, 0, "Loads the static field at a specified index onto the evaluation stack. The index is represented as a 1-byte unsigned integer." },
      OpCodeInfo{ 0x60, "STSFLD0", 0, 0, "Stores the value on top of the evaluation stack in the static field list at index 0." },
      OpCodeInfo{ 0x61, "STSFLD1", 0, 0, "Stores the value on top of the evaluation stack in the static field list at index 1." },
      OpCodeInfo{ 0x62, "STSFLD2", 0, 0, "Stores the value on top of the evaluation stack in the static field list at index 2." },
      OpCodeInfo{ 0x63, "STSFLD3", 0, 0, "Stores the value on top of the evaluation stack in the static field list at index 3." },
      OpCodeInfo{ 0x64, "STSFLD4", 0, 0, "Stores the value on top of the evaluation stack in the static field list at index 4." },
      OpCodeInfo{ 0x65, "STSFLD5", 0, 0, "Stores the value on top of the evaluation stack in the static field list at index 5." },
      OpCodeInfo{ 0x66, "STSFLD6", 0, 0, "Stores the value on top of the evaluation stack in the static field list at index 6." },
      OpCodeInfo{ 0x67, "STSFLD", 1, 0, "Stores the value on top of the evaluation stack in the static field list at a specified index. The index is represented as a 1-byte unsigned integer." },
      OpCodeInfo{ 0x68, "LDLOC0", 0, 0, "Loads the local variable at index 0 onto the evaluation stack." },
      OpCodeInfo{ 0x69, "LDLOC1", 0, 0, "Loads the local variable at index 1 onto the evaluation stack." },
      OpCodeInfo{ 0x6a, "LDLOC2", 0, 0, "Loads the local variable at index 2 onto the evaluation stack." },
      OpCodeInfo{ 0x6b, "LDLOC3", 0, 0, "Loads the local variable at index 3 onto the evaluation stack." },
      OpCodeInfo{ 0x6c, "LDLOC4", 0, 0, "Loads the local variable at index 4 onto the evaluation stack." },
      OpCodeInfo{ 0x6d, "LDLOC5", 0, 0, "Loads the local variable at index 5 onto the evaluation stack." },
      OpCodeInfo{ 0x6e, "LDLOC6", 0, 0, "Loads the local variable at index 6 onto the evaluation stack." },
      OpCodeInfo{ 0x6f, "LDLOC", 1, 0, "Loads the local variable at a specified index onto the evaluation stack. The index is represented as a 1-byte unsigned integer." },
      OpCodeInfo{ 0x70, "STLOC0", 0, 0, "Stores the value on top of the evaluation stack in the local variable list at index 0." },
      OpCodeInfo{ 0x71, "STLOC1", 0, 0, "Stores the value on top of the evaluation stack in the local variable list at index 1." },
      OpCodeInfo{ 0x72, "STLOC2", 0, 0, "Stores the value on top of the evaluation stack in the local variable list at index 2." },
      OpCodeInfo{ 0x73, "STLOC3", 0, 0, "Stores the value on top of the evaluation stack in the local variable list at index 3." },
      OpCodeInfo{ 0x74, "STLOC4", 0, 0, "Stores the value on top of the evaluation stack in the local variable list at index 4." },
      OpCodeInfo{ 0x75, "STLOC5", 0, 0, "Stores the value on top of the evaluation stack in the local variable list at index 5." },
      OpCodeInfo{ 0x76, "STLOC6", 0, 0, "Stores the value on top of the evaluation stack in the local variable list at index 6." },
      OpCodeInfo{ 0x77, "STLOC", 1, 0, "Stores the value on top of the evaluation stack in the local variable list at a specified index. The index is represented as a 1-byte unsigned integer." },
      OpCodeInfo{ 0x78, "LDARG0", 0, 0, "Loads the argument at index 0 onto the evaluation stack." },
      OpCodeInfo{ 0x79, "LDARG1", 0, 0, "Loads the argument at index 1 onto the evaluation stack." },
      OpCodeInfo{ 0x7a, "LDARG2", 0, 0, "Loads the argument at index 2 onto the evaluation stack." },
      OpCodeInfo{ 0x7b, "LDARG3", 0, 0, "Loads the argument at index 3 onto the evaluation stack." },
      OpCodeInfo{ 0x7c, "LDARG4", 0, 0, "Loads the argument at index 4 onto the evaluation stack." },
      OpCodeInfo{ 0x7d, "LDARG5", 0, 0, "Loads the argument at index 5 onto the evaluation stack." },
      OpCodeInfo{ 0x7e, "LDARG6", 0, 0, "Loads the argument at index 6 onto the evaluation stack." },
      OpCodeInfo{ 0x7f, "LDARG", 1, 0, "Loads the argument at a specified index onto the evaluation stack. The index is represented as a 1-byte unsigned integer." },
      OpCodeInfo{ 0x80, "STARG0", 0, 0, "Stores the value on top of the evaluation stack in the argument slot at index 0." },
      OpCodeInfo{ 0x81, "STARG1", 0, 0, "Stores the value on top of the evaluation stack in the argument slot at index 1." },
      OpCodeInfo{ 0x82, "STARG2", 0, 0, "Stores the value on top of the evaluation stack in the argument slot at index 2." },
      OpCodeInfo{ 0x83, "STARG3", 0, 0, "Stores the value on top of the evaluation stack in the argument slot at index 3." },
      OpCodeInfo{ 0x84, "STARG4", 0, 0, "Stores the value on top of the evaluation stack in the argument slot at index 4." },
      OpCodeInfo{ 0x85, "STARG5", 0, 0, "Stores the value on top of the evaluation stack in the argument slot at index 5." },
      OpCodeInfo{ 0x86, "STARG6", 0, 0, "Stores the value on top of the evaluation stack in the argument slot at index 6." },
      OpCodeInfo{ 0x87, "STARG", 1, 0, "Stores the value on top of the evaluation stack in the argument slot at a specified index. The index is represented as a 1-byte unsigned integer." },
      //#endregion // Slot
      //#region Splice
      OpCodeInfo{ 0x88, "NEWBUFFER", 0, 0, "OP_NEWBUFFER" },
      OpCodeInfo{ 0x89, "MEMCPY", 0, 0, "OP_MEMCPY" },
      OpCodeInfo{ 0x8a, "0x8a", 0, 0, "unused" },
      OpCodeInfo{ 0x8b, "CAT", 0, 0, "Concatenates two strings." },
      OpCodeInfo{ 0x8c, "SUBSTR", 0, 0, "Returns a section of a string." },
      OpCodeInfo{ 0x8d, "LEFT", 0, 0, "Keeps only characters left of the specified point in a string." },
      OpCodeInfo{ 0x8e, "RIGHT", 0, 0, "Keeps only characters right of the specified point in a string." },
      OpCodeInfo{ 0x8f, "0x8a", 0, 0, "unused" },
      //#endregion // Splice
      //#region Bitwise logic
      OpCodeInfo{ 0x90, "INVERT", 0, 0, "Flips all of the bits in the input." },
      OpCodeInfo{ 0x91, "AND", 0, 0, "Boolean and between each bit in the inputs." },
      OpCodeInfo{ 0x92, "OR", 0, 0, "Boolean or between each bit in the inputs." },
      OpCodeInfo{ 0x93, "XOR", 0, 0, "Boolean exclusive or between each bit in the inputs." },
      OpCodeInfo{ 0x94, "0x94", 0, 0, "unused" },
      OpCodeInfo{ 0x95, "0x95", 0, 0, "unused" },
      OpCodeInfo{ 0x96, "0x96", 0, 0, "unused" },
      OpCodeInfo{ 0x97, "EQUAL", 0, 0, "Returns 1 if the inputs are exactly equal, 0 otherwise." },
      OpCodeInfo{ 0x98, "NOTEQUAL", 0, 0, "Returns 1 if the inputs are not equal, 0 otherwise." },
      //#endregion // Bitwise
      //#region Arithmetic
      OpCodeInfo{ 0x99, "SIGN", 0, 0, "Puts the sign of top stack item on top of the main stack. If value is negative, put -1; if positive, put 1; if value is zero, put 0." },
      OpCodeInfo{ 0x9a, "ABS", 0, 0, "The input is made positive." },
      OpCodeInfo{ 0x9b, "NEGATE", 0, 0, "The sign of the input is flipped." },
      OpCodeInfo{ 0x9c, "INC", 0, 0, "1 is added to the input." },
      OpCodeInfo{ 0x9d, "DEC", 0, 0, "1 is subtracted from the input." },
      OpCodeInfo{ 0x9e, "ADD", 0, 0, "a is added to b." },
      OpCodeInfo{ 0x9f, "SUB", 0, 0, "b is subtracted from a." },
      OpCodeInfo{ 0xa0, "MUL", 0, 0, "a is multiplied by b." },
      OpCodeInfo{ 0xa1, "DIV", 0, 0, "a is divided by b." },
      OpCodeInfo{ 0xa2, "MOD", 0, 0, "Returns the remainder after dividing a by b." },
      OpCodeInfo{ 0xa3, "0xa3", 0, 0, "unused" },
      OpCodeInfo{ 0xa4, "0xa4", 0, 0, "unused" },
      OpCodeInfo{ 0xa5, "0xa5", 0, 0, "unused" },
      OpCodeInfo{ 0xa6, "0xa6", 0, 0, "unused" },
      OpCodeInfo{ 0xa7, "0xa7", 0, 0, "unused" },
      OpCodeInfo{ 0xa8, "SHL", 0, 0, "Shifts a left b bits, preserving sign." },
      OpCodeInfo{ 0xa9, "SHR", 0, 0, "Shifts a right b bits, preserving sign." },
      OpCodeInfo{ 0xaa, "NOT", 0, 0, "If the input is 0 or 1, it is flipped. Otherwise the output will be 0." },
      OpCodeInfo{ 0xab, "BOOLAND", 0, 0, "If both a and b are not 0, the output is 1. Otherwise 0." },
      OpCodeInfo{ 0xac, "BOOLOR", 0, 0, "If a or b is not 0, the output is 1. Otherwise 0." },
      OpCodeInfo{ 0xad, "0xad", 0, 0, "unused" },
      OpCodeInfo{ 0xae, "0xae", 0, 0, "unused" },
      OpCodeInfo{ 0xaf, "0xaf", 0, 0, "unused" },
      OpCodeInfo{ 0xb0, "0xb0", 0, 0, "unused" },
      OpCodeInfo{ 0xb1, "NZ", 0, 0, "Returns 0 if the input is 0. 1 otherwise." },
      OpCodeInfo{ 0xb2, "0xb2", 0, 0, "unused" },
      OpCodeInfo{ 0xb3, "NUMEQUAL", 0, 0, "Returns 1 if the numbers are equal, 0 otherwise." },
      OpCodeInfo{ 0xb4, "NUMNOTEQUAL", 0, 0, "Returns 1 if the numbers are not equal, 0 otherwise." },
      OpCodeInfo{ 0xb5, "LT", 0, 0, "Returns 1 if a is less than b, 0 otherwise." },
      OpCodeInfo{ 0xb6, "LE", 0, 0, "Returns 1 if a is less than or equal to b, 0 otherwise." },
      OpCodeInfo{ 0xb7, "GT", 0, 0, "Returns 1 if a is greater than b, 0 otherwise." },
      OpCodeInfo{ 0xb8, "GE", 0, 0, "Returns 1 if a is greater than or equal to b, 0 otherwise." },
      OpCodeInfo{ 0xb9, "MIN", 0, 0, "Returns the smaller of a and b." },
      OpCodeInfo{ 0xba, "MAX", 0, 0, "Returns the larger of a and b." },
      OpCodeInfo{ 0xbb, "WITHIN", 0, 0, "Returns 1 if x is within the specified range (left-inclusive), 0 otherwise." },
      OpCodeInfo{ 0xbc, "0xbc", 0, 0, "unused" },
      OpCodeInfo{ 0xbd, "0xbd", 0, 0, "unused" },
      OpCodeInfo{ 0xbe, "0xbe", 0, 0, "unused" },
      OpCodeInfo{ 0xbf, "0xbf", 0, 0, "unused" },
      //#endregion // Arithmetic
      //#region Compound-type
      OpCodeInfo{ 0xc0, "PACK", 0, 0, "A value n is taken from top of main stack. The next n items on main stack are removed, put inside n-sized array and this array is put on top of the main stack." },
      OpCodeInfo{ 0xc1, "UNPACK", 0, 0, "An array is removed from top of the main stack. Its elements are put on top of the main stack (in reverse order) and the array size is also put on main stack." },
      OpCodeInfo{ 0xc2, "NEWARRAY0", 0, 0, "An empty array (with size 0) is put on top of the main stack." },
      OpCodeInfo{ 0xc3, "NEWARRAY", 0, 0, "A value n is taken from top of main stack. A null-filled array with size n is put on top of the main stack." },
      OpCodeInfo{ 0xc4, "NEWARRAY_T", 1, 0, "A value n is taken from top of main stack. An array of type T with size n is put on top of the main stack." },
      OpCodeInfo{ 0xc5, "NEWSTRUCT0", 0, 0, "An empty struct (with size 0) is put on top of the main stack." },
      OpCodeInfo{ 0xc6, "NEWSTRUCT", 0, 0, "A value n is taken from top of main stack. A zero-filled struct with size n is put on top of the main stack." },
      OpCodeInfo{ 0xc7, "0xc7", 0, 0, "unused" },
      OpCodeInfo{ 0xc8, "NEWMAP", 0, 0, "A Map is created and put on top of the main stack." },
      OpCodeInfo{ 0xc9, "0xc9", 0, 0, "unused" },
      OpCodeInfo{ 0xca, "SIZE", 0, 0, "An array is removed from top of the main stack. Its size is put on top of the main stack." },
      OpCodeInfo{ 0xcb, "HASKEY", 0, 0, "An input index n (or key) and an array (or map) are removed from the top of the main stack. Puts True on top of main stack if array[n] (or map[n]) exist, and False otherwise." },
      OpCodeInfo{ 0xcc, "KEYS", 0, 0, "A map is taken from top of the main stack. The keys of this map are put on top of the main stack." },
      OpCodeInfo{ 0xcd, "VALUES", 0, 0, "A map is taken from top of the main stack. The values of this map are put on top of the main stack." },
      OpCodeInfo{ 0xce, "PICKITEM", 0, 0, "An input index n (or key) and an array (or map) are taken from main stack. Element array[n] (or map[n]) is put on top of the main stack." },
      OpCodeInfo{ 0xcf, "APPEND", 0, 0, "The item on top of main stack is removed and appended to the second item on top of the main stack." },
      OpCodeInfo{ 0xd0, "SETITEM", 0, 0, "A value v, index n (or key) and an array (or map) are taken from main stack. Attribution array[n]=v (or map[n]=v) is performed." },
      OpCodeInfo{ 0xd1, "REVERSEITEMS", 0, 0, "An array is removed from the top of the main stack and its elements are reversed." },
      OpCodeInfo{ 0xd2, "REMOVE", 0, 0, "An input index n (or key) and an array (or map) are removed from the top of the main stack. Element array[n] (or map[n]) is removed." },
      OpCodeInfo{ 0xd3, "CLEARITEMS", 0, 0, "Remove all the items from the compound-type." },
      OpCodeInfo{ 0xd4, "0xd4", 0, 0, "unused" },
      OpCodeInfo{ 0xd5, "0xd5", 0, 0, "unused" },
      OpCodeInfo{ 0xd6, "0xd6", 0, 0, "unused" },
      OpCodeInfo{ 0xd7, "0xd7", 0, 0, "unused" },
      // #endregion // Compound-type
      //#region Types
      OpCodeInfo{ 0xd8, "ISNULL", 0, 0, "Returns true if the input is null. Returns false otherwise." },
      OpCodeInfo{ 0xd9, "ISTYPE", 1, 0, "Returns true if the top item is of the specified type." },
      OpCodeInfo{ 0xda, "0xda", 0, 0, "unused" },
      OpCodeInfo{ 0xdb, "CONVERT", 1, 0, "Converts the top item to the specified type." },
      //#endregion // Types
   };
};
// check first and last (at compile time)
// 0x00
static_assert(OpCodeInfoGlobal::oplist[OP_PUSHINT8].name == "PUSHINT8");
// 0xdb
static_assert(OpCodeInfoGlobal::oplist[OP_CONVERT].name == "CONVERT");
//
} // namespace nvm3

#endif // NVM3_OPCODE_TEXT_HPP