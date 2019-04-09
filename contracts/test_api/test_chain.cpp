/**
 *  @file
 *  @copyright defined in fsc/LICENSE
 */
#include <fsciolib/action.h>
#include <fsciolib/chain.h>
#include <fsciolib/fscio.hpp>
#include "test_api.hpp"

#pragma pack(push, 1)
struct producers {
   char len;
   account_name producers[21];
};
#pragma pack(pop)

void test_chain::test_activeprods() {
  producers act_prods;
  read_action_data(&act_prods, sizeof(producers));
   
  fscio_assert(act_prods.len == 21, "producers.len != 21");

  producers api_prods;
  get_active_producers(api_prods.producers, sizeof(account_name)*21);

  for( int i = 0; i < 21 ; ++i )
      fscio_assert(api_prods.producers[i] == act_prods.producers[i], "Active producer");
}
