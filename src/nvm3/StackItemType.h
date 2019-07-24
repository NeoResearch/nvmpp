#ifndef NEOPT_NVM_STACKITEMTYPE_H
#define NEOPT_NVM_STACKITEMTYPE_H

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

enum StackItemType
{
   /// <summary>
   /// Boolean (true,false)
   /// </summary>
   SIT_Boolean,

   /// <summary>
   /// ByteArray
   /// </summary>
   SIT_ByteArray,

   /// <summary>
   /// ByteArray as UTF8 string
   /// </summary>
   SIT_String,

   /// <summary>
   /// String
   /// </summary>
   SIT_Interop,

   /// <summary>
   /// BigInteger
   /// </summary>
   SIT_Integer,

   /// <summary>
   /// Array
   /// </summary>
   SIT_Array,

   /// <summary>
   /// Struct
   /// </summary>
   SIT_Struct,

   /// <summary>
   /// Map
   /// </summary>
   SIT_Map
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_STACKITEMTYPE_H