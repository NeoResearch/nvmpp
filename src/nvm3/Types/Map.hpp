#ifndef NEOPT_NVM_TYPES_MAP_HPP
#define NEOPT_NVM_TYPES_MAP_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/Dictionary.hpp>
#include <system/printable.h>
#include <system/vhelper.hpp>

#include "../StackItem.h"

using namespace std; // TODO: remove

namespace neopt {
namespace nvm {
class Map : public StackItem // TODO: , ICollection   , IList<StackItem>
{
private:
   Dictionary<StackItem, StackItem> dictionary;

public:

   Map()
   {
   }

   StackItem& operator[](const StackItem& key)
   {
      return dictionary[key];
   }

   //public ICollection<StackItem> Keys => dictionary.Keys;
   //public ICollection<StackItem> Values => dictionary.Values;
   int Count()
   {
      return dictionary.Count();
   }

   bool IsReadOnly()
   {
      return false;
   }

   //bool ICollection.IsSynchronized => false;
   //object ICollection.SyncRoot => dictionary;

   //public Map() : this(new Dictionary<StackItem, StackItem>()) { }

   // TODO: copy-base and move-base
   Map(const Dictionary<StackItem, StackItem>& value)
   {
      this->dictionary = value;
   }

   void Add(StackItem& key, StackItem& value)
   {
      dictionary.Add(key, value);
   }

   //void ICollection<KeyValuePair<StackItem, StackItem>>.Add(KeyValuePair<StackItem, StackItem> item)
   //{
   //    dictionary.Add(item.Key, item.Value);
   //}

   void Clear()
   {
      dictionary.Clear();
   }

   //bool ICollection<KeyValuePair<StackItem, StackItem>>.Contains(KeyValuePair<StackItem, StackItem> item)
   //{
   //    return dictionary.ContainsKey(item.Key);
   //}

   bool ContainsKey(const StackItem& key)
   {
      return dictionary.ContainsKey(key);
   }

   //void ICollection<KeyValuePair<StackItem, StackItem>>.CopyTo(KeyValuePair<StackItem, StackItem>[] array, int arrayIndex)
   //{
   //    foreach (KeyValuePair<StackItem, StackItem> item in dictionary)
   //        array[arrayIndex++] = item;
   //}

   //void ICollection.CopyTo(System.Array array, int index)
   //{
   //    foreach (KeyValuePair<StackItem, StackItem> item in dictionary)
   //        array.SetValue(item, index++);
   //}

   virtual bool Equals(const StackItem* pother) override 
   {
      if (pother == nullptr)
         return true;
      const StackItem& other = *pother;
      return this == &other;
   }

   bool GetBoolean() const override
   {
      return true;
   }

   vbyte GetByteArray() const override
   {
      //throw new NotSupportedException();
      NEOPT_EXCEPTION("NotSupportedException");
      return vbyte(0);
   }

   //IEnumerator<KeyValuePair<StackItem, StackItem>> IEnumerable<KeyValuePair<StackItem, StackItem>>.GetEnumerator()
   //{
   //    return dictionary.GetEnumerator();
   //}

   //IEnumerator IEnumerable.GetEnumerator()
   //{
   //    return dictionary.GetEnumerator();
   //}

   bool Remove(const StackItem& key)
   {
      return dictionary.Remove(key);
   }

   //bool ICollection<KeyValuePair<StackItem, StackItem>>.Remove(KeyValuePair<StackItem, StackItem> item)
   //{
   //    return dictionary.Remove(item.Key);
   //}

   StackItem* TryGetValue(const StackItem& key)
   {
      return dictionary.TryGetValue(key);
   }
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_TYPES_MAP_HPP