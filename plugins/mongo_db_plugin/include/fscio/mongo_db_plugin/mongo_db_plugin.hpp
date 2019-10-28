/**
 *  @file
 *  @copyright defined in fsc/LICENSE
 */
#pragma once

#include <fscio/chain_plugin/chain_plugin.hpp>
#include <appbase/application.hpp>
#include <memory>

namespace fscio {

using mongo_db_plugin_impl_ptr = std::shared_ptr<class mongo_db_plugin_impl>;

/**
 * Provides persistence to MongoDB for:
 * accounts
 * actions
 * block_states
 * blocks
 * transaction_traces
 * transactions
 * pub_keys
 * account_controls
 *
 *   See data dictionary (DB Schema Definition - FSC API) for description of MongoDB schema.
 *
 *   If cmake -DBUILD_MONGO_DB_PLUGIN=true  not specified then this plugin not compiled/included.
 */
class mongo_db_plugin : public plugin<mongo_db_plugin> {
public:
   APPBASE_PLUGIN_REQUIRES((chain_plugin))

   mongo_db_plugin();
   virtual ~mongo_db_plugin();

   virtual void set_program_options(options_description& cli, options_description& cfg) override;

   void plugin_initialize(const variables_map& options);
   void plugin_startup();
   void plugin_shutdown();

   struct transfer {
      account_name                     from;
      account_name                     to;
      asset                            quantity;
      std::string                      memo;
      static action_name get_name() {
         return N(transfer);
      }
   };

   struct transferext {
      std::string                     from_address;
      std::string                     to_address;
      asset                           quantity;
      std::string                     memo;
      static action_name get_name() {
         return N(transferext);
      }
   };

private:
   mongo_db_plugin_impl_ptr my;
};

}
FC_REFLECT( eosio::mongo_db_plugin::transfer                         , (from)(to)(quantity)(memo) )
FC_REFLECT( eosio::mongo_db_plugin::transferext                      , (from_address)(to_address)(quantity)(memo) )

