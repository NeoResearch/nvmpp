#include "StackItem.h"

#include "Types/InteropInterface.hpp"

using namespace neopt::nvm;

// perhaps forward declaration?
template<class T>
StackItem* StackItem::FromInterface(T& value)
{
   return new InteropInterface<T>(value);
}
