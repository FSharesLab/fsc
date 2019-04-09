/**
 *  @file
 *  @copyright defined in fsc/LICENSE
 */

#include <fsciolib/fscio.hpp>

namespace asserter {
   struct assertdef {
      int8_t      condition;
      std::string message;

      FSCLIB_SERIALIZE( assertdef, (condition)(message) )
   };
}
