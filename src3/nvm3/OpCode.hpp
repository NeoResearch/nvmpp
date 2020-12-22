#ifndef NVM3_OPCODE_HPP
#define NVM3_OPCODE_HPP

// c++ standard part
// ..

namespace nvm3 {
//
enum OpCode
{
   //#region Constants

   //[OperandSize(Size = 1)]
   OP_PUSHINT8 = 0x00,
   //[OperandSize(Size = 2)]
   OP_PUSHINT16 = 0x01,
   //[OperandSize(Size = 4)]
   OP_PUSHINT32 = 0x02,
   //[OperandSize(Size = 8)]
   OP_PUSHINT64 = 0x03,
   //[OperandSize(Size = 16)]
   OP_PUSHINT128 = 0x04,
   //[OperandSize(Size = 32)]
   OP_PUSHINT256 = 0x05,
   /// <summary>
   /// Convert the next four bytes to an address, and push the address onto the stack.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_PUSHA = 0x0A,
   /// <summary>
   /// The item <see langword="null"/> is pushed onto the stack.
   /// </summary>
   OP_PUSHNULL = 0x0B,
   /// <summary>
   /// The next byte contains the number of bytes to be pushed onto the stack.
   /// </summary>
   //[OperandSize(SizePrefix = 1)]
   OP_PUSHDATA1 = 0x0C,
   /// <summary>
   /// The next two bytes contain the number of bytes to be pushed onto the stack.
   /// </summary>
   //[OperandSize(SizePrefix = 2)]
   OP_PUSHDATA2 = 0x0D,
   /// <summary>
   /// The next four bytes contain the number of bytes to be pushed onto the stack.
   /// </summary>
   //[OperandSize(SizePrefix = 4)]
   OP_PUSHDATA4 = 0x0E,
   /// <summary>
   /// The number -1 is pushed onto the stack.
   /// </summary>
   OP_PUSHM1 = 0x0F,
   /// <summary>
   /// The number 0 is pushed onto the stack.
   /// </summary>
   OP_PUSH0 = 0x10,
   /// <summary>
   /// The number 1 is pushed onto the stack.
   /// </summary>
   OP_PUSH1 = 0x11,
   /// <summary>
   /// The number 2 is pushed onto the stack.
   /// </summary>
   OP_PUSH2 = 0x12,
   /// <summary>
   /// The number 3 is pushed onto the stack.
   /// </summary>
   OP_PUSH3 = 0x13,
   /// <summary>
   /// The number 4 is pushed onto the stack.
   /// </summary>
   OP_PUSH4 = 0x14,
   /// <summary>
   /// The number 5 is pushed onto the stack.
   /// </summary>
   OP_PUSH5 = 0x15,
   /// <summary>
   /// The number 6 is pushed onto the stack.
   /// </summary>
   OP_PUSH6 = 0x16,
   /// <summary>
   /// The number 7 is pushed onto the stack.
   /// </summary>
   OP_PUSH7 = 0x17,
   /// <summary>
   /// The number 8 is pushed onto the stack.
   /// </summary>
   OP_PUSH8 = 0x18,
   /// <summary>
   /// The number 9 is pushed onto the stack.
   /// </summary>
   OP_PUSH9 = 0x19,
   /// <summary>
   /// The number 10 is pushed onto the stack.
   /// </summary>
   OP_PUSH10 = 0x1A,
   /// <summary>
   /// The number 11 is pushed onto the stack.
   /// </summary>
   OP_PUSH11 = 0x1B,
   /// <summary>
   /// The number 12 is pushed onto the stack.
   /// </summary>
   OP_PUSH12 = 0x1C,
   /// <summary>
   /// The number 13 is pushed onto the stack.
   /// </summary>
   OP_PUSH13 = 0x1D,
   /// <summary>
   /// The number 14 is pushed onto the stack.
   /// </summary>
   OP_PUSH14 = 0x1E,
   /// <summary>
   /// The number 15 is pushed onto the stack.
   /// </summary>
   OP_PUSH15 = 0x1F,
   /// <summary>
   /// The number 16 is pushed onto the stack.
   /// </summary>
   OP_PUSH16 = 0x20,

   //#endregion // Constants

   //#region Flow control

   /// <summary>
   /// The <see cref="NOP"/> operation does nothing. It is intended to fill in space if opcodes are patched.
   /// </summary>
   OP_NOP = 0x21,
   /// <summary>
   /// Unconditionally transfers control to a target instruction. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_JMP = 0x22,
   /// <summary>
   /// Unconditionally transfers control to a target instruction. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_JMP_L = 0x23,
   /// <summary>
   /// Transfers control to a target instruction if the value is <see langword="true"/>, not <see langword="null"/>, or non-zero. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_JMPIF = 0x24,
   /// <summary>
   /// Transfers control to a target instruction if the value is <see langword="true"/>, not <see langword="null"/>, or non-zero. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_JMPIF_L = 0x25,
   /// <summary>
   /// Transfers control to a target instruction if the value is <see langword="false"/>, a <see langword="null"/> reference, or zero. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_JMPIFNOT = 0x26,
   /// <summary>
   /// Transfers control to a target instruction if the value is <see langword="false"/>, a <see langword="null"/> reference, or zero. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_JMPIFNOT_L = 0x27,
   /// <summary>
   /// Transfers control to a target instruction if two values are equal. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_JMPEQ = 0x28,
   /// <summary>
   /// Transfers control to a target instruction if two values are equal. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_JMPEQ_L = 0x29,
   /// <summary>
   /// Transfers control to a target instruction when two values are not equal. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_JMPNE = 0x2A,
   /// <summary>
   /// Transfers control to a target instruction when two values are not equal. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_JMPNE_L = 0x2B,
   /// <summary>
   /// Transfers control to a target instruction if the first value is greater than the second value. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_JMPGT = 0x2C,
   /// <summary>
   /// Transfers control to a target instruction if the first value is greater than the second value. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_JMPGT_L = 0x2D,
   /// <summary>
   /// Transfers control to a target instruction if the first value is greater than or equal to the second value. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_JMPGE = 0x2E,
   /// <summary>
   /// Transfers control to a target instruction if the first value is greater than or equal to the second value. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_JMPGE_L = 0x2F,
   /// <summary>
   /// Transfers control to a target instruction if the first value is less than the second value. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_JMPLT = 0x30,
   /// <summary>
   /// Transfers control to a target instruction if the first value is less than the second value. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_JMPLT_L = 0x31,
   /// <summary>
   /// Transfers control to a target instruction if the first value is less than or equal to the second value. The target instruction is represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_JMPLE = 0x32,
   /// <summary>
   /// Transfers control to a target instruction if the first value is less than or equal to the second value. The target instruction is represented as a 4-bytes signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_JMPLE_L = 0x33,
   /// <summary>
   /// Calls the function at the target address which is represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_CALL = 0x34,
   /// <summary>
   /// Calls the function at the target address which is represented as a 4-bytes signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_CALL_L = 0x35,
   /// <summary>
   /// Pop the address of a function from the stack, and call the function.
   /// </summary>
   OP_CALLA = 0x36,
   /// <summary>
   /// Calls the function which is described by the token.
   /// </summary>
   //[OperandSize(Size = 2)]
   OP_CALLT = 0x37,
   /// <summary>
   /// It turns the vm state to FAULT immediately, and cannot be caught.
   /// </summary>
   OP_ABORT = 0x38,
   /// <summary>
   /// Pop the top value of the stack, if it false, then exit vm execution and set vm state to FAULT.
   /// </summary>
   OP_ASSERT = 0x39,
   /// <summary>
   /// Pop the top value of the stack, and throw it.
   /// </summary>
   OP_THROW = 0x3A,
   /// <summary>
   /// TRY CatchOffset(sbyte) FinallyOffset(sbyte). If there's no catch body, set CatchOffset 0. If there's no finally body, set FinallyOffset 0.
   /// </summary>
   //[OperandSize(Size = 2)]
   OP_TRY = 0x3B,
   /// <summary>
   /// TRY_L CatchOffset(int) FinallyOffset(int). If there's no catch body, set CatchOffset 0. If there's no finally body, set FinallyOffset 0.
   /// </summary>
   //[OperandSize(Size = 8)]
   OP_TRY_L = 0x3C,
   /// <summary>
   /// Ensures that the appropriate surrounding finally blocks are executed. And then unconditionally transfers control to the specific target instruction, represented as a 1-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_ENDTRY = 0x3D,
   /// <summary>
   /// Ensures that the appropriate surrounding finally blocks are executed. And then unconditionally transfers control to the specific target instruction, represented as a 4-byte signed offset from the beginning of the current instruction.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_ENDTRY_L = 0x3E,
   /// <summary>
   /// End finally, If no exception happen or be catched, vm will jump to the target instruction of ENDTRY/ENDTRY_L. Otherwise vm will rethrow the exception to upper layer.
   /// </summary>
   OP_ENDFINALLY = 0x3F,
   /// <summary>
   /// Returns from the current method.
   /// </summary>
   OP_RET = 0x40,
   /// <summary>
   /// Calls to an interop service.
   /// </summary>
   //[OperandSize(Size = 4)]
   OP_SYSCALL = 0x41,

   //#endregion // Flow

   //#region Stack

   /// <summary>
   /// Puts the number of stack items onto the stack.
   /// </summary>
   OP_DEPTH = 0x43,
   /// <summary>
   /// Removes the top stack item.
   /// </summary>
   OP_DROP = 0x45,
   /// <summary>
   /// Removes the second-to-top stack item.
   /// </summary>
   OP_NIP = 0x46,
   /// <summary>
   /// The item n back in the main stack is removed.
   /// </summary>
   OP_XDROP = 0x48,
   /// <summary>
   /// Clear the stack
   /// </summary>
   OP_CLEAR = 0x49,
   /// <summary>
   /// Duplicates the top stack item.
   /// </summary>
   OP_DUP = 0x4A,
   /// <summary>
   /// Copies the second-to-top stack item to the top.
   /// </summary>
   OP_OVER = 0x4B,
   /// <summary>
   /// The item n back in the stack is copied to the top.
   /// </summary>
   OP_PICK = 0x4D,
   /// <summary>
   /// The item at the top of the stack is copied and inserted before the second-to-top item.
   /// </summary>
   OP_TUCK = 0x4E,
   /// <summary>
   /// The top two items on the stack are swapped.
   /// </summary>
   OP_SWAP = 0x50,
   /// <summary>
   /// The top three items on the stack are rotated to the left.
   /// </summary>
   OP_ROT = 0x51,
   /// <summary>
   /// The item n back in the stack is moved to the top.
   /// </summary>
   OP_ROLL = 0x52,
   /// <summary>
   /// Reverse the order of the top 3 items on the stack.
   /// </summary>
   OP_REVERSE3 = 0x53,
   /// <summary>
   /// Reverse the order of the top 4 items on the stack.
   /// </summary>
   OP_REVERSE4 = 0x54,
   /// <summary>
   /// Pop the number N on the stack, and reverse the order of the top N items on the stack.
   /// </summary>
   OP_REVERSEN = 0x55,

   //#endregion Stack

   //#region Slot

   /// <summary>
   /// Initialize the static field list for the current execution context.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_INITSSLOT = 0x56,
   /// <summary>
   /// Initialize the argument slot and the local variable list for the current execution context.
   /// </summary>
   //[OperandSize(Size = 2)]
   OP_INITSLOT = 0x57,
   /// <summary>
   /// Loads the static field at index 0 onto the evaluation stack.
   /// </summary>
   OP_LDSFLD0 = 0x58,
   /// <summary>
   /// Loads the static field at index 1 onto the evaluation stack.
   /// </summary>
   OP_LDSFLD1 = 0x59,
   /// <summary>
   /// Loads the static field at index 2 onto the evaluation stack.
   /// </summary>
   OP_LDSFLD2 = 0x5A,
   /// <summary>
   /// Loads the static field at index 3 onto the evaluation stack.
   /// </summary>
   OP_LDSFLD3 = 0x5B,
   /// <summary>
   /// Loads the static field at index 4 onto the evaluation stack.
   /// </summary>
   OP_LDSFLD4 = 0x5C,
   /// <summary>
   /// Loads the static field at index 5 onto the evaluation stack.
   /// </summary>
   OP_LDSFLD5 = 0x5D,
   /// <summary>
   /// Loads the static field at index 6 onto the evaluation stack.
   /// </summary>
   OP_LDSFLD6 = 0x5E,
   /// <summary>
   /// Loads the static field at a specified index onto the evaluation stack. The index is represented as a 1-byte unsigned integer.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_LDSFLD = 0x5F,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the static field list at index 0.
   /// </summary>
   OP_STSFLD0 = 0x60,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the static field list at index 1.
   /// </summary>
   OP_STSFLD1 = 0x61,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the static field list at index 2.
   /// </summary>
   OP_STSFLD2 = 0x62,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the static field list at index 3.
   /// </summary>
   OP_STSFLD3 = 0x63,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the static field list at index 4.
   /// </summary>
   OP_STSFLD4 = 0x64,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the static field list at index 5.
   /// </summary>
   OP_STSFLD5 = 0x65,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the static field list at index 6.
   /// </summary>
   OP_STSFLD6 = 0x66,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the static field list at a specified index. The index is represented as a 1-byte unsigned integer.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_STSFLD = 0x67,
   /// <summary>
   /// Loads the local variable at index 0 onto the evaluation stack.
   /// </summary>
   OP_LDLOC0 = 0x68,
   /// <summary>
   /// Loads the local variable at index 1 onto the evaluation stack.
   /// </summary>
   OP_LDLOC1 = 0x69,
   /// <summary>
   /// Loads the local variable at index 2 onto the evaluation stack.
   /// </summary>
   OP_LDLOC2 = 0x6A,
   /// <summary>
   /// Loads the local variable at index 3 onto the evaluation stack.
   /// </summary>
   OP_LDLOC3 = 0x6B,
   /// <summary>
   /// Loads the local variable at index 4 onto the evaluation stack.
   /// </summary>
   OP_LDLOC4 = 0x6C,
   /// <summary>
   /// Loads the local variable at index 5 onto the evaluation stack.
   /// </summary>
   OP_LDLOC5 = 0x6D,
   /// <summary>
   /// Loads the local variable at index 6 onto the evaluation stack.
   /// </summary>
   OP_LDLOC6 = 0x6E,
   /// <summary>
   /// Loads the local variable at a specified index onto the evaluation stack. The index is represented as a 1-byte unsigned integer.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_LDLOC = 0x6F,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the local variable list at index 0.
   /// </summary>
   OP_STLOC0 = 0x70,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the local variable list at index 1.
   /// </summary>
   OP_STLOC1 = 0x71,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the local variable list at index 2.
   /// </summary>
   OP_STLOC2 = 0x72,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the local variable list at index 3.
   /// </summary>
   OP_STLOC3 = 0x73,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the local variable list at index 4.
   /// </summary>
   OP_STLOC4 = 0x74,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the local variable list at index 5.
   /// </summary>
   OP_STLOC5 = 0x75,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the local variable list at index 6.
   /// </summary>
   OP_STLOC6 = 0x76,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the local variable list at a specified index. The index is represented as a 1-byte unsigned integer.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_STLOC = 0x77,
   /// <summary>
   /// Loads the argument at index 0 onto the evaluation stack.
   /// </summary>
   OP_LDARG0 = 0x78,
   /// <summary>
   /// Loads the argument at index 1 onto the evaluation stack.
   /// </summary>
   OP_LDARG1 = 0x79,
   /// <summary>
   /// Loads the argument at index 2 onto the evaluation stack.
   /// </summary>
   OP_LDARG2 = 0x7A,
   /// <summary>
   /// Loads the argument at index 3 onto the evaluation stack.
   /// </summary>
   OP_LDARG3 = 0x7B,
   /// <summary>
   /// Loads the argument at index 4 onto the evaluation stack.
   /// </summary>
   OP_LDARG4 = 0x7C,
   /// <summary>
   /// Loads the argument at index 5 onto the evaluation stack.
   /// </summary>
   OP_LDARG5 = 0x7D,
   /// <summary>
   /// Loads the argument at index 6 onto the evaluation stack.
   /// </summary>
   OP_LDARG6 = 0x7E,
   /// <summary>
   /// Loads the argument at a specified index onto the evaluation stack. The index is represented as a 1-byte unsigned integer.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_LDARG = 0x7F,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the argument slot at index 0.
   /// </summary>
   OP_STARG0 = 0x80,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the argument slot at index 1.
   /// </summary>
   OP_STARG1 = 0x81,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the argument slot at index 2.
   /// </summary>
   OP_STARG2 = 0x82,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the argument slot at index 3.
   /// </summary>
   OP_STARG3 = 0x83,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the argument slot at index 4.
   /// </summary>
   OP_STARG4 = 0x84,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the argument slot at index 5.
   /// </summary>
   OP_STARG5 = 0x85,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the argument slot at index 6.
   /// </summary>
   OP_STARG6 = 0x86,
   /// <summary>
   /// Stores the value on top of the evaluation stack in the argument slot at a specified index. The index is represented as a 1-byte unsigned integer.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_STARG = 0x87,

   //#endregion // Slot

   //#region Splice

   OP_NEWBUFFER = 0x88,
   OP_MEMCPY = 0x89,
   /// <summary>
   /// Concatenates two strings.
   /// </summary>
   OP_CAT = 0x8B,
   /// <summary>
   /// Returns a section of a string.
   /// </summary>
   OP_SUBSTR = 0x8C,
   /// <summary>
   /// Keeps only characters left of the specified point in a string.
   /// </summary>
   OP_LEFT = 0x8D,
   /// <summary>
   /// Keeps only characters right of the specified point in a string.
   /// </summary>
   OP_RIGHT = 0x8E,

   //#endregion // Splice

   //#region Bitwise logic

   /// <summary>
   /// Flips all of the bits in the input.
   /// </summary>
   OP_INVERT = 0x90,
   /// <summary>
   /// Boolean and between each bit in the inputs.
   /// </summary>
   OP_AND = 0x91,
   /// <summary>
   /// Boolean or between each bit in the inputs.
   /// </summary>
   OP_OR = 0x92,
   /// <summary>
   /// Boolean exclusive or between each bit in the inputs.
   /// </summary>
   OP_XOR = 0x93,
   /// <summary>
   /// Returns 1 if the inputs are exactly equal, 0 otherwise.
   /// </summary>
   OP_EQUAL = 0x97,
   /// <summary>
   /// Returns 1 if the inputs are not equal, 0 otherwise.
   /// </summary>
   OP_NOTEQUAL = 0x98,

   //#endregion // Bitwise

   //#region Arithmetic

   /// <summary>
   /// Puts the sign of top stack item on top of the main stack. If value is negative, put -1; if positive, put 1; if value is zero, put 0.
   /// </summary>
   OP_SIGN = 0x99,
   /// <summary>
   /// The input is made positive.
   /// </summary>
   OP_ABS = 0x9A,
   /// <summary>
   /// The sign of the input is flipped.
   /// </summary>
   OP_NEGATE = 0x9B,
   /// <summary>
   /// 1 is added to the input.
   /// </summary>
   OP_INC = 0x9C,
   /// <summary>
   /// 1 is subtracted from the input.
   /// </summary>
   OP_DEC = 0x9D,
   /// <summary>
   /// a is added to b.
   /// </summary>
   OP_ADD = 0x9E,
   /// <summary>
   /// b is subtracted from a.
   /// </summary>
   OP_SUB = 0x9F,
   /// <summary>
   /// a is multiplied by b.
   /// </summary>
   OP_MUL = 0xA0,
   /// <summary>
   /// a is divided by b.
   /// </summary>
   OP_DIV = 0xA1,
   /// <summary>
   /// Returns the remainder after dividing a by b.
   /// </summary>
   OP_MOD = 0xA2,
   /// <summary>
   /// Shifts a left b bits, preserving sign.
   /// </summary>
   OP_SHL = 0xA8,
   /// <summary>
   /// Shifts a right b bits, preserving sign.
   /// </summary>
   OP_SHR = 0xA9,
   /// <summary>
   /// If the input is 0 or 1, it is flipped. Otherwise the output will be 0.
   /// </summary>
   OP_NOT = 0xAA,
   /// <summary>
   /// If both a and b are not 0, the output is 1. Otherwise 0.
   /// </summary>
   OP_BOOLAND = 0xAB,
   /// <summary>
   /// If a or b is not 0, the output is 1. Otherwise 0.
   /// </summary>
   OP_BOOLOR = 0xAC,
   /// <summary>
   /// Returns 0 if the input is 0. 1 otherwise.
   /// </summary>
   OP_NZ = 0xB1,
   /// <summary>
   /// Returns 1 if the numbers are equal, 0 otherwise.
   /// </summary>
   OP_NUMEQUAL = 0xB3,
   /// <summary>
   /// Returns 1 if the numbers are not equal, 0 otherwise.
   /// </summary>
   OP_NUMNOTEQUAL = 0xB4,
   /// <summary>
   /// Returns 1 if a is less than b, 0 otherwise.
   /// </summary>
   OP_LT = 0xB5,
   /// <summary>
   /// Returns 1 if a is less than or equal to b, 0 otherwise.
   /// </summary>
   OP_LE = 0xB6,
   /// <summary>
   /// Returns 1 if a is greater than b, 0 otherwise.
   /// </summary>
   OP_GT = 0xB7,
   /// <summary>
   /// Returns 1 if a is greater than or equal to b, 0 otherwise.
   /// </summary>
   OP_GE = 0xB8,
   /// <summary>
   /// Returns the smaller of a and b.
   /// </summary>
   OP_MIN = 0xB9,
   /// <summary>
   /// Returns the larger of a and b.
   /// </summary>
   OP_MAX = 0xBA,
   /// <summary>
   /// Returns 1 if x is within the specified range (left-inclusive), 0 otherwise.
   /// </summary>
   OP_WITHIN = 0xBB,

   //#endregion // Arithmetic

   //#region Compound-type

   /// <summary>
   /// A value n is taken from top of main stack. The next n items on main stack are removed, put inside n-sized array and this array is put on top of the main stack.
   /// </summary>
   OP_PACK = 0xC0,
   /// <summary>
   /// An array is removed from top of the main stack. Its elements are put on top of the main stack (in reverse order) and the array size is also put on main stack.
   /// </summary>
   OP_UNPACK = 0xC1,
   /// <summary>
   /// An empty array (with size 0) is put on top of the main stack.
   /// </summary>
   OP_NEWARRAY0 = 0xC2,
   /// <summary>
   /// A value n is taken from top of main stack. A null-filled array with size n is put on top of the main stack.
   /// </summary>
   OP_NEWARRAY = 0xC3,
   /// <summary>
   /// A value n is taken from top of main stack. An array of type T with size n is put on top of the main stack.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_NEWARRAY_T = 0xC4,
   /// <summary>
   /// An empty struct (with size 0) is put on top of the main stack.
   /// </summary>
   OP_NEWSTRUCT0 = 0xC5,
   /// <summary>
   /// A value n is taken from top of main stack. A zero-filled struct with size n is put on top of the main stack.
   /// </summary>
   OP_NEWSTRUCT = 0xC6,
   /// <summary>
   /// A Map is created and put on top of the main stack.
   /// </summary>
   OP_NEWMAP = 0xC8,
   /// <summary>
   /// An array is removed from top of the main stack. Its size is put on top of the main stack.
   /// </summary>
   OP_SIZE = 0xCA,
   /// <summary>
   /// An input index n (or key) and an array (or map) are removed from the top of the main stack. Puts True on top of main stack if array[n] (or map[n]) exist, and False otherwise.
   /// </summary>
   OP_HASKEY = 0xCB,
   /// <summary>
   /// A map is taken from top of the main stack. The keys of this map are put on top of the main stack.
   /// </summary>
   OP_KEYS = 0xCC,
   /// <summary>
   /// A map is taken from top of the main stack. The values of this map are put on top of the main stack.
   /// </summary>
   OP_VALUES = 0xCD,
   /// <summary>
   /// An input index n (or key) and an array (or map) are taken from main stack. Element array[n] (or map[n]) is put on top of the main stack.
   /// </summary>
   OP_PICKITEM = 0xCE,
   /// <summary>
   /// The item on top of main stack is removed and appended to the second item on top of the main stack.
   /// </summary>
   OP_APPEND = 0xCF,
   /// <summary>
   /// A value v, index n (or key) and an array (or map) are taken from main stack. Attribution array[n]=v (or map[n]=v) is performed.
   /// </summary>
   OP_SETITEM = 0xD0,
   /// <summary>
   /// An array is removed from the top of the main stack and its elements are reversed.
   /// </summary>
   OP_REVERSEITEMS = 0xD1,
   /// <summary>
   /// An input index n (or key) and an array (or map) are removed from the top of the main stack. Element array[n] (or map[n]) is removed.
   /// </summary>
   OP_REMOVE = 0xD2,
   /// <summary>
   /// Remove all the items from the compound-type.
   /// </summary>
   OP_CLEARITEMS = 0xD3,

   // #endregion // Compound-type

   //#region Types

   /// <summary>
   /// Returns true if the input is null. Returns false otherwise.
   /// </summary>
   OP_ISNULL = 0xD8,
   /// <summary>
   /// Returns true if the top item is of the specified type.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_ISTYPE = 0xD9,
   /// <summary>
   /// Converts the top item to the specified type.
   /// </summary>
   //[OperandSize(Size = 1)]
   OP_CONVERT = 0xDB,

   //#endregion // Types
};
//
} // namespace nvm3

#endif // NVM3_OPCODE_HPP