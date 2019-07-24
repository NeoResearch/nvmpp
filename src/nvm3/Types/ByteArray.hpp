#ifndef NEOPT_NVM_TYPES_BYTEARRAY_HPP
#define NEOPT_NVM_TYPES_BYTEARRAY_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/printable.h>
#include <system/vhelper.hpp>

#include "../ExecutionEngineLimits.h"
#include "../StackItem.h"

using namespace std; // TODO: remove

namespace neopt {
namespace nvm {
class ByteArray : public StackItem // TODO: , ICollection   , IList<StackItem>
{
private:
   vbyte value;

public:
   ByteArray(vbyte value)
   {
      this->value = value;
   }

   // default constructor
   ByteArray()
   {
   }

   bool Equals(const StackItem* pother) override
   {
      if (pother == nullptr)
         return true;
      const StackItem& other = *pother;
      if (this == &other)
         return true;
      vbyte bytes_other;
      bytes_other = other.GetByteArray();
      // let it crash
      /*
      try {
         bytes_other = other.GetByteArray();
      } catch (NotSupportedException) {
         return false;
      }
      */
      return value == bytes_other;
   }

   bool GetBoolean() const override
   {
      if (value.size() > ExecutionEngineLimits::getMaxSizeForBigInteger())
         return true;
      return value.size() == 1 ? value[0] != 0x00 : true;
   }

   vbyte GetByteArray() const override
   {
      return value;
   }
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_TYPES_BYTEARRAY_HPP