#include <fsciolib/fscio.hpp>
#include <fsciolib/print.hpp>
using namespace fscio;

class payloadless : public fscio::contract {
  public:
      using contract::contract;

      void doit() {
         print( "Im a payloadless action" );
      }
};

FSCIO_ABI( payloadless, (doit) )
