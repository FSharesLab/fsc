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

   struct addlimitlog {
      uint64_t                        block_id;
      account_name                    account;
      double                          limit_double;
      uint8_t                         transfer_type;
      std::string                     transfer_symbol;
      static action_name get_name() {
         return N(addlimitlog);
      }
   };

   struct endreward {
      uint64_t                        block_id;
      account_name                    account;
      asset                           quantity;
      static action_name get_name() {
         return N(endreward);
      }
   };

private:
   mongo_db_plugin_impl_ptr my;
};

}
FC_REFLECT( fscio::mongo_db_plugin::transfer                         , (from)(to)(quantity)(memo) )
FC_REFLECT( fscio::mongo_db_plugin::addlimitlog                      , (block_id)(account)(limit_double)(transfer_type)(transfer_symbol) )
FC_REFLECT( fscio::mongo_db_plugin::endreward                        , (block_id)(account)(quantity) )

