// demo for testing nvm3

#include <iostream>

// nvm3 related
#include <nvm3/OpCodeInfo.hpp>

// using all std
using namespace std;
// using all nvm3
using namespace nvm3;

int
main()
{

   std::cout << OP_PUSHINT8 << "\t" << OpCodeInfoGlobal::optext[OP_PUSHINT8].description << std::endl;
   std::cout << OP_PUSHA << "\t" << OpCodeInfoGlobal::optext[OP_PUSHA].description << std::endl;
   std::cout << OP_CONVERT << "\t" << OpCodeInfoGlobal::optext[OP_CONVERT].description << std::endl;

   return 0;
}