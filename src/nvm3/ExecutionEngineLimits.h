#ifndef NEOPT_NVM_EXECUTIONENGINELIMITS_HPP
#define NEOPT_NVM_EXECUTIONENGINELIMITS_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/BigInteger.h>
#include <numbers/UInt256.hpp>
#include <system/IEquatable.h>
#include <system/printable.h>
#include <system/vhelper.hpp>

namespace neopt {
namespace nvm {

class ExecutionEngineLimits
{
public:

   // TODO: remove (keep only base reference for constant)
   static int getMaxSizeForBigInteger()
   {
      ExecutionEngineLimits limits;
      return limits.MaxSizeForBigInteger;
   }

   /// <summary>
   /// Max value for SHL and SHR
   /// </summary>
   virtual int Max_SHL_SHR()
   {
      return 256;
   }

   /// <summary>
   /// Min value for SHL and SHR
   /// </summary>
   virtual int Min_SHL_SHR()
   {
      return -256;
   }

   /// <summary>
   /// The max size in bytes allowed size for BigInteger
   /// </summary>
   const int MaxSizeForBigInteger = 32;

   /// <summary>
   /// Set the max Stack Size
   /// </summary>
   virtual uint MaxStackSize()
   {
      return 2 * 1024;
   }

   /// <summary>
   /// Set Max Item Size
   /// </summary>
   virtual uint MaxItemSize()
   {
      return 1024 * 1024;
   }

   /// <summary>
   /// Set Max Invocation Stack Size
   /// </summary>
   virtual uint MaxInvocationStackSize()
   {
      return 1024;
   }

   /// <summary>
   /// Set Max Array Size
   /// </summary>
   virtual uint MaxArraySize()
   {
      return 1024;
   }

   // PART2

   /// <summary>
        /// Check if it is possible to overflow the MaxArraySize
        /// </summary>
        /// <param name="length">Length</param>
        /// <returns>Return True if are allowed, otherwise False</returns>
        
        bool CheckArraySize(int length)
        {
           return length <= MaxArraySize();
        }

        /// <summary>
        /// Check if the is possible to overflow the MaxItemSize
        /// </summary>
        /// <param name="length">Length</param>
        /// <returns>Return True if are allowed, otherwise False</returns>
        bool CheckMaxItemSize(int length)
        {
           return length >= 0 && length <= MaxItemSize();
        } 

        /// <summary>
        /// Check if the BigInteger is allowed for numeric operations
        /// </summary>
        /// <param name="value">Value</param>
        /// <returns>Return True if are allowed, otherwise False</returns>
        bool CheckBigInteger(BigInteger value)
        {
           return value.ToByteArray().size() <= MaxSizeForBigInteger;
        } 

        /// <summary>
        /// Check if the number is allowed from SHL and SHR
        /// </summary>
        /// <param name="shift">Shift</param>
        /// <returns>Return True if are allowed, otherwise False</returns>
        bool CheckShift(int shift) {
           return shift <= Max_SHL_SHR() && shift >= Min_SHL_SHR();
        }

};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_ExecutionEngineLimits_HPP