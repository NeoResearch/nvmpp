#ifndef NEOPT_NVM_TYPES_BOOLEAN_HPP
#define NEOPT_NVM_TYPES_BOOLEAN_HPP

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
class Boolean : public StackItem // TODO: , ICollection   , IList<StackItem>
{
private:
   static const vbyte TRUE()
   {
      return vbyte(1, 0x01);
   }
   static const vbyte FALSE()
   {
      return vbyte(1, 0x00);
   }

   bool value;

public:
   Boolean(bool value)
   {
      this->value = value;
   }

   virtual bool Equals(const StackItem* pother) override 
   {
      if (pother == nullptr)
         return true;
      const StackItem& other = *pother;
      if (other.type == SIT_Boolean)
         return value == ((Boolean&)other).value;
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
      return std::move(value ? BigInteger::One : BigInteger::Zero);
   }

   bool GetBoolean() const override
   {
      return value;
   }

   vbyte GetByteArray() const override
   {
      return std::move(value ? TRUE() : FALSE());
   }
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_TYPES_BOOLEAN_HPP