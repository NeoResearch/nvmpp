#ifndef NEOPT_NVM_TYPES_INTEROP_HPP
#define NEOPT_NVM_TYPES_INTEROP_HPP

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
class InteropInterface : public StackItem // TODO: , ICollection   , IList<StackItem>
{

public:
   vbyte GetByteArray() const override
   {
      //throw new NotSupportedException();
      NEOPT_EXCEPTION("NotSupportedException");
      return vbyte(0);
   }

   //virtual T* GetInterface() = 0;
};

template<class T>
class Interop : public InteropInterface
{
private:
   T* _object;

public:
   Interop(T* value)
   {
      this._object = value;
   }

   virtual bool Equals(const StackItem* pother) override 
   {
      if (pother == nullptr)
         return true;
      const StackItem& other = *pother;
      if (!(other.type == SIT_Interop))
         return false;
      Interop<T>& i = (Interop<T>&)other;
      return _object->Equals(i._object);
   }

   bool GetBoolean() const override
   {
      return _object != nullptr;
   }

   template<class I>
   I& GetInterface()
   {
      return (I&)*_object;
   }

   //public static implicit operator T(InteropInterface<T> @interface)
   //{
   //    return @interface._object;
   //}
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_TYPES_INTEROP_HPP