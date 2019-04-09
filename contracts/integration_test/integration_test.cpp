#include <fsciolib/fscio.hpp>
using namespace fscio;

struct integration_test : public fscio::contract {
      using contract::contract;

      struct payload {
         uint64_t            key;
         vector<uint64_t>    data;

         uint64_t primary_key()const { return key; }
      };
      typedef fscio::multi_index<N(payloads), payload> payloads;

      /// @abi action 
      void store( account_name from,
                  account_name to,
                  uint64_t     num ) {
         require_auth( from );
         fscio_assert( is_account( to ), "to account does not exist");
         fscio_assert( num < std::numeric_limits<size_t>::max(), "num to large");
         payloads data ( _self, from );
         uint64_t key = 0;
         const uint64_t num_keys = 5;
         while (data.find( key ) != data.end()) {
            key += num_keys;
         }
         for (size_t i = 0; i < num_keys; ++i) {
            data.emplace(from, [&]( auto& g ) {
               g.key = key + i;
               g.data = vector<uint64_t>( static_cast<size_t>(num), 5);
            });
         }
      }
};

FSCIO_ABI( integration_test, (store) )
