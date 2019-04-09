/**
 *  @file
 *  @copyright defined in fsc/LICENSE
 */

#include <fscio/chain/chain_id_type.hpp>
#include <fscio/chain/exceptions.hpp>

namespace fscio { namespace chain {

   void chain_id_type::reflector_init()const {
      FSC_ASSERT( *reinterpret_cast<const fc::sha256*>(this) != fc::sha256(), chain_id_type_exception, "chain_id_type cannot be zero" );
   }

} }  // namespace fscio::chain

namespace fc {

   void to_variant(const fscio::chain::chain_id_type& cid, fc::variant& v) {
      to_variant( static_cast<const fc::sha256&>(cid), v);
   }

   void from_variant(const fc::variant& v, fscio::chain::chain_id_type& cid) {
      from_variant( v, static_cast<fc::sha256&>(cid) );
   }

} // fc
