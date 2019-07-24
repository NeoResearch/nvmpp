#ifndef NEOPT_NVM_RANDOMACCESSSTACK_HPP
#define NEOPT_NVM_RANDOMACCESSSTACK_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/UInt256.hpp>
#include <system/printable.h>
#include <system/vhelper.hpp>

using namespace std; // TODO: remove

namespace neopt {
namespace nvm {

// TODO: this class is currently intended to work with pointers, but it can be changed to ref/moved based

template<class T>
class RandomAccessStack // TODO: IReadOnlyCollection<T> (does it help in anything?)
{
private:
   vector<T*> list;

public:
   int Count()
   {
      return list.size();
   }

   void Clear()
   {
      list.clear();
   }

   void CopyTo(RandomAccessStack<T>& stack, int count = -1)
   {
      if (count == 0)
         return;
      if (count == -1)
         stack.list.AddRange(list);
      else
         stack.list.AddRange(list.Skip(list.Count - count));
   }

   //[MethodImpl(MethodImplOptions.AggressiveInlining)]
   //public IEnumerator<T> GetEnumerator()
   //{
   //    return list.GetEnumerator();
   //}

   //[MethodImpl(MethodImplOptions.AggressiveInlining)]
   //IEnumerator IEnumerable.GetEnumerator()
   //{
   //    return list.GetEnumerator();
   //}

   void Insert(int index, T* item)
   {
      if (index > list.size()) {
         // throw new InvalidOperationException();
         NEOPT_EXCEPTION("InvalidOperationException");
      }
      list.insert(list.begin() + Count() - index, item);
   }

   T* Peek(int index = 0)
   {
      if (index >= list.size()) {
         // throw new InvalidOperationException();
         NEOPT_EXCEPTION("InvalidOperationException");
      }
      if (index < 0) {
         index += list.size();
         if (index < 0) {
            //throw new InvalidOperationException();
            NEOPT_EXCEPTION("InvalidOperationException");
         }
      }
      return list[(Count() - index - 1)];
   }

   T* Pop()
   {
      return Remove(0);
   }

   void Push(T* item)
   {
      list.push_back(item);
   }

   // push multiple items
   void Push(vector<T*>& items)
   {
      for(unsigned i=0; i<items.size(); i++)
         list.push_back(items[i]);
   }

   T* Remove(int index)
   {
      if (index >= Count()) {
         //throw new InvalidOperationException();
         NEOPT_EXCEPTION("InvalidOperationException");
      }
      if (index < 0) {
         index += Count();
         if (index < 0) {
            //throw new InvalidOperationException();
            NEOPT_EXCEPTION("InvalidOperationException");
         }
      }
      index = Count() - index - 1;
      T* item = list[index];
      list.erase(list.begin() + index);
      return item;
   }

   void Set(int index, T* item)
   {
      if (index >= Count()) {
         //throw new InvalidOperationException();
         NEOPT_EXCEPTION("InvalidOperationException");
      }
      if (index < 0) {
         index += Count();
         if (index < 0) {
            //throw new InvalidOperationException();
            NEOPT_EXCEPTION("InvalidOperationException");
         }
      }
      list[(Count() - index - 1)] = item;
   }
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_RANDOMACCESSSTACK_HPP