#ifndef NEOPT_NVM_STACKITEM_H
#define NEOPT_NVM_STACKITEM_H

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/BigInteger.h>
#include <numbers/UInt256.hpp>
#include <system/IEquatable.h>
#include <system/printable.h>
#include <system/vhelper.hpp>

#include "StackItemType.h"

namespace neopt {
namespace nvm {

class StackItem : IEquatable<StackItem>
{
public:
   StackItemType type; // stack item type

   static StackItem* GetNull()
   {
      // useful?
      return nullptr; //new StackItem(vbyte(0));
   }

   // helper method to decide which type is collection. Array? Map? Struct?
   virtual bool IsCollection() const
   {
      return false;
   }

   // From IEquatable
   virtual bool Equals(const StackItem* other) = 0;

   /*
   virtual bool Equals(object obj) override
   {
      if (obj == null)
         return false;
      if (obj == this)
         return true;
      if (obj is StackItem other)
         return Equals(other);
      return false;
   }
   */

   // perhaps forward declaration?
   template<class T>
   static StackItem* FromInterface(T& value)
   {
      return new InteropInterface<T>(value);
   }

   // move semantics
   virtual BigInteger GetBigInteger() const
   {
      return std::move(BigInteger(GetByteArray()));
   }

   virtual bool GetBoolean() const = 0;

   virtual vbyte GetByteArray() const = 0;

   virtual int GetByteLength() const
   {
      return GetByteArray().size();
   }

   /*
   override int GetHashCode()
   {
      unchecked
      {
         int hash = 17;
         foreach (byte element in GetByteArray())
            hash = hash * 31 + element;
         return hash;
      }
   }
*/

   virtual string GetString()
   {
      return ""; //Encoding.UTF8.GetString(GetByteArray());
   }

   // TODO: implicit
   /*
   static implicit operator StackItem(int value)
   {
      return (BigInteger)value;
   }

   static implicit operator StackItem(uint value)
   {
      return (BigInteger)value;
   }

   static implicit operator StackItem(long value)
   {
      return (BigInteger)value;
   }

   static implicit operator StackItem(ulong value)
   {
      return (BigInteger)value;
   }

   static implicit operator StackItem(BigInteger value)
   {
      return new Integer(value);
   }

   static implicit operator StackItem(bool value)
   {
      return new Boolean(value);
   }

   static implicit operator StackItem(byte[] value)
   {
      return new ByteArray(value);
   }


   static implicit operator StackItem(string value)
   {
      return new ByteArray(Encoding.UTF8.GetBytes(value));
   }


   static implicit operator StackItem(StackItem[] value)
   {
      return new Array(value);
   }

   static implicit operator StackItem(List<StackItem> value)
   {
      return new Array(value);
   }
   */
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_STACKITEM_H