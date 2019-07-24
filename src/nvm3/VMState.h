#ifndef NEOPT_NVM_VMSTATE_H
#define NEOPT_NVM_VMSTATE_H

// c++ standard part
// ..

// neopt core part
// ...

namespace neopt {
namespace nvm {

enum VMState
{
   VMS_NONE = 0,

   VMS_HALT = 1 << 0,
   VMS_FAULT = 1 << 1,
   VMS_BREAK = 1 << 2
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_VMSTATE_H