/**
 *  @file
 *  @copyright defined in fsc/LICENSE
 */
#pragma once

#include <fscio/chain/types.hpp>
#include <fscio/chain/contract_types.hpp>

namespace fscio { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_fscio_newaccount(apply_context&);
   void apply_fscio_updateauth(apply_context&);
   void apply_fscio_deleteauth(apply_context&);
   void apply_fscio_linkauth(apply_context&);
   void apply_fscio_unlinkauth(apply_context&);

   /*
   void apply_fscio_postrecovery(apply_context&);
   void apply_fscio_passrecovery(apply_context&);
   void apply_fscio_vetorecovery(apply_context&);
   */

   void apply_fscio_setcode(apply_context&);
   void apply_fscio_setabi(apply_context&);

   void apply_fscio_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace fscio::chain
