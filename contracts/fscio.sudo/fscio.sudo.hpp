#pragma once

#include <fsciolib/fscio.hpp>

namespace fscio {

   class sudo : public contract {
      public:
         sudo( account_name self ):contract(self){}

         void exec();

   };

} /// namespace fscio
