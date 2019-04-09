#include <fsciolib/fscio.hpp>

using namespace fscio;

class hello : public fscio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
      }
};

FSCIO_ABI( hello, (hi) )
