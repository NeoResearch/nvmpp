#ifndef NEOPT_NVM_TYPES_INTEGER_HPP
#define NEOPT_NVM_TYPES_INTEGER_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/printable.h>
#include <system/vhelper.hpp>

#include "../StackItem.h"

using namespace std; // TODO: remove

namespace neopt {
namespace nvm {
class Integer : public StackItem // TODO: , ICollection   , IList<StackItem>
{

private:
   static vbyte ZeroBytes()
   {
      return vbyte(0);
   }

   BigInteger value;

public:
   // TODO: copy-base and move-base
   Integer(const BigInteger& value)
   {
      // attribution
      this->value = value;
   }

   virtual bool Equals(const StackItem* pother) override 
   {
      if (pother == nullptr)
         return true;
      const StackItem& other = *pother;

      if (other.type == SIT_Integer)
         return value == ((Integer&)other).value;
      vbyte bytes_other;
      bytes_other = other.GetByteArray();
      // let it crash
      /*
            try
            {
                bytes_other = other.GetByteArray();
            }
            catch (NotSupportedException)
            {
                return false;
            }
            */
      return GetByteArray() == bytes_other;
   }

   BigInteger GetBigInteger() const override
   {
      return value;
   }

   bool GetBoolean() const override
   {
      return !value.IsZero;
   }

   vbyte GetByteArray() const override
   {
      return value.IsZero() ? ZeroBytes() : value.ToByteArray();
   }

private:
   int _length = -1;

public:
   int GetByteLength() const override
   {
      if (_length == -1) {
         // const_cast to remove local constness... caching purposes only.
         Integer* i = const_cast<Integer*>(this);
         i->_length = GetByteArray().size();
      }
      return _length;
   }
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_TYPES_ARRAY_HPP