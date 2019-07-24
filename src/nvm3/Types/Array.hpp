#ifndef NEOPT_NVM_TYPES_ARRAY_HPP
#define NEOPT_NVM_TYPES_ARRAY_HPP

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
class Array : public StackItem // TODO: , ICollection   , IList<StackItem>
{
protected:
   std::vector<StackItem*> _array;

public:
   StackItem& operator[] (int index) {
      return *_array[index];
   }

   int Count() {
      return _array.size();
   }

   // TODO: why?
   bool IsReadOnly(){
      return false;
   } 

   //bool ICollection.IsSynchronized = > false;
   //object ICollection.SyncRoot = > _array;

   //Array()
   //  : Array(std::vector<StackItem*>())
   //{}

//   Array(IEnumerable<StackItem> value)
//   {
//      this._array = value as List<StackItem> ? ? value.ToList();
//   }

   // no cloning here! beware of memory leaks
   void Add(StackItem* item)
   {
      _array.push_back(item);
   }

   // no deleting here! beware of memory leaks
   void Clear()
   {
      _array.clear();
   }

//   bool Contains(StackItem item)
//   {
//      return _array.Contains(item);
//   }

/*
   void ICollection<StackItem>.CopyTo(StackItem[] array, int arrayIndex)
   {
      _array.CopyTo(array, arrayIndex);
   }

   void ICollection.CopyTo(System.Array array, int index)
   {
      foreach (StackItem item in _array)
         array.SetValue(item, index++);
   }
*/

   virtual bool Equals(const StackItem* pother) override 
   {
      if (pother == nullptr)
         return true;
      const StackItem& other = *pother;
      return this == &other; // only pointer comparison here?
   }

   bool GetBoolean() const override 
   {
      return true;
   }

   vbyte GetByteArray() const override
   {
      //throw new NotSupportedException();
      NEOPT_EXCEPTION("NotSupportedException");
      return vbyte();
   }

   //IEnumerator IEnumerable.GetEnumerator()
   //{
   //   return GetEnumerator();
  // }

//   IEnumerator<StackItem> GetEnumerator()
//   {
//      return _array.GetEnumerator();
//   }

//   int IList<StackItem>.IndexOf(StackItem item)
//   {
//      return _array.IndexOf(item);
//   }

   void Insert(int index, StackItem* item)
   {
      _array.insert(_array.begin()+index, item);
   }

//   bool ICollection<StackItem>.Remove(StackItem item)
//   {
//      return _array.Remove(item);
//   }

   void RemoveAt(int index)
   {
      _array.erase(_array.begin()+index);
   }

   void Reverse()
   {
      std::reverse(_array.begin(), _array.end());
   }
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_TYPES_ARRAY_HPP