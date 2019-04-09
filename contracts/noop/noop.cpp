/**
 *  @file
 *  @copyright defined in fsc/LICENSE
 */

#include <fsciolib/fscio.hpp>

namespace fscio {

   class noop: public contract {
      public:
         noop( account_name self ): contract( self ) { }
         void anyaction( account_name from,
                         const std::string& /*type*/,
                         const std::string& /*data*/ )
         {
            require_auth( from );
         }
   };

   FSCIO_ABI( noop, ( anyaction ) )

} /// fscio     
