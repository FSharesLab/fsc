/**
 *  @file
 *  @copyright defined in fsc/LICENSE
 */
#include <fsciolib/fscio.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   fscio_assert( sizeof(int64_t) == 8, "int64_t size != 8");
   fscio_assert( sizeof(uint64_t) ==  8, "uint64_t size != 8");
   fscio_assert( sizeof(uint32_t) ==  4, "uint32_t size != 4");
   fscio_assert( sizeof(int32_t) ==  4, "int32_t size != 4");
   fscio_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   fscio_assert( sizeof(int128_t) == 16, "int128_t size != 16");
   fscio_assert( sizeof(uint8_t) ==  1, "uint8_t size != 1");

   fscio_assert( sizeof(account_name) ==  8, "account_name size !=  8");
   fscio_assert( sizeof(table_name) ==  8, "table_name size !=  8");
   fscio_assert( sizeof(time) ==  4, "time size !=  4");
   fscio_assert( sizeof(fscio::key256) == 32, "key256 size != 32" );
}

void test_types::char_to_symbol() {

   fscio_assert( fscio::char_to_symbol('1') ==  1, "fscio::char_to_symbol('1') !=  1");
   fscio_assert( fscio::char_to_symbol('2') ==  2, "fscio::char_to_symbol('2') !=  2");
   fscio_assert( fscio::char_to_symbol('3') ==  3, "fscio::char_to_symbol('3') !=  3");
   fscio_assert( fscio::char_to_symbol('4') ==  4, "fscio::char_to_symbol('4') !=  4");
   fscio_assert( fscio::char_to_symbol('5') ==  5, "fscio::char_to_symbol('5') !=  5");
   fscio_assert( fscio::char_to_symbol('a') ==  6, "fscio::char_to_symbol('a') !=  6");
   fscio_assert( fscio::char_to_symbol('b') ==  7, "fscio::char_to_symbol('b') !=  7");
   fscio_assert( fscio::char_to_symbol('c') ==  8, "fscio::char_to_symbol('c') !=  8");
   fscio_assert( fscio::char_to_symbol('d') ==  9, "fscio::char_to_symbol('d') !=  9");
   fscio_assert( fscio::char_to_symbol('e') == 10, "fscio::char_to_symbol('e') != 10");
   fscio_assert( fscio::char_to_symbol('f') == 11, "fscio::char_to_symbol('f') != 11");
   fscio_assert( fscio::char_to_symbol('g') == 12, "fscio::char_to_symbol('g') != 12");
   fscio_assert( fscio::char_to_symbol('h') == 13, "fscio::char_to_symbol('h') != 13");
   fscio_assert( fscio::char_to_symbol('i') == 14, "fscio::char_to_symbol('i') != 14");
   fscio_assert( fscio::char_to_symbol('j') == 15, "fscio::char_to_symbol('j') != 15");
   fscio_assert( fscio::char_to_symbol('k') == 16, "fscio::char_to_symbol('k') != 16");
   fscio_assert( fscio::char_to_symbol('l') == 17, "fscio::char_to_symbol('l') != 17");
   fscio_assert( fscio::char_to_symbol('m') == 18, "fscio::char_to_symbol('m') != 18");
   fscio_assert( fscio::char_to_symbol('n') == 19, "fscio::char_to_symbol('n') != 19");
   fscio_assert( fscio::char_to_symbol('o') == 20, "fscio::char_to_symbol('o') != 20");
   fscio_assert( fscio::char_to_symbol('p') == 21, "fscio::char_to_symbol('p') != 21");
   fscio_assert( fscio::char_to_symbol('q') == 22, "fscio::char_to_symbol('q') != 22");
   fscio_assert( fscio::char_to_symbol('r') == 23, "fscio::char_to_symbol('r') != 23");
   fscio_assert( fscio::char_to_symbol('s') == 24, "fscio::char_to_symbol('s') != 24");
   fscio_assert( fscio::char_to_symbol('t') == 25, "fscio::char_to_symbol('t') != 25");
   fscio_assert( fscio::char_to_symbol('u') == 26, "fscio::char_to_symbol('u') != 26");
   fscio_assert( fscio::char_to_symbol('v') == 27, "fscio::char_to_symbol('v') != 27");
   fscio_assert( fscio::char_to_symbol('w') == 28, "fscio::char_to_symbol('w') != 28");
   fscio_assert( fscio::char_to_symbol('x') == 29, "fscio::char_to_symbol('x') != 29");
   fscio_assert( fscio::char_to_symbol('y') == 30, "fscio::char_to_symbol('y') != 30");
   fscio_assert( fscio::char_to_symbol('z') == 31, "fscio::char_to_symbol('z') != 31");

   for(unsigned char i = 0; i<255; i++) {
      if((i >= 'a' && i <= 'z') || (i >= '1' || i <= '5')) continue;
      fscio_assert( fscio::char_to_symbol((char)i) == 0, "fscio::char_to_symbol() != 0");
   }
}

void test_types::string_to_name() {

   fscio_assert( fscio::string_to_name("a") == N(a) , "fscio::string_to_name(a)" );
   fscio_assert( fscio::string_to_name("ba") == N(ba) , "fscio::string_to_name(ba)" );
   fscio_assert( fscio::string_to_name("cba") == N(cba) , "fscio::string_to_name(cba)" );
   fscio_assert( fscio::string_to_name("dcba") == N(dcba) , "fscio::string_to_name(dcba)" );
   fscio_assert( fscio::string_to_name("edcba") == N(edcba) , "fscio::string_to_name(edcba)" );
   fscio_assert( fscio::string_to_name("fedcba") == N(fedcba) , "fscio::string_to_name(fedcba)" );
   fscio_assert( fscio::string_to_name("gfedcba") == N(gfedcba) , "fscio::string_to_name(gfedcba)" );
   fscio_assert( fscio::string_to_name("hgfedcba") == N(hgfedcba) , "fscio::string_to_name(hgfedcba)" );
   fscio_assert( fscio::string_to_name("ihgfedcba") == N(ihgfedcba) , "fscio::string_to_name(ihgfedcba)" );
   fscio_assert( fscio::string_to_name("jihgfedcba") == N(jihgfedcba) , "fscio::string_to_name(jihgfedcba)" );
   fscio_assert( fscio::string_to_name("kjihgfedcba") == N(kjihgfedcba) , "fscio::string_to_name(kjihgfedcba)" );
   fscio_assert( fscio::string_to_name("lkjihgfedcba") == N(lkjihgfedcba) , "fscio::string_to_name(lkjihgfedcba)" );
   fscio_assert( fscio::string_to_name("mlkjihgfedcba") == N(mlkjihgfedcba) , "fscio::string_to_name(mlkjihgfedcba)" );
   fscio_assert( fscio::string_to_name("mlkjihgfedcba1") == N(mlkjihgfedcba2) , "fscio::string_to_name(mlkjihgfedcba2)" );
   fscio_assert( fscio::string_to_name("mlkjihgfedcba55") == N(mlkjihgfedcba14) , "fscio::string_to_name(mlkjihgfedcba14)" );

   fscio_assert( fscio::string_to_name("azAA34") == N(azBB34) , "fscio::string_to_name N(azBB34)" );
   fscio_assert( fscio::string_to_name("AZaz12Bc34") == N(AZaz12Bc34) , "fscio::string_to_name AZaz12Bc34" );
   fscio_assert( fscio::string_to_name("AAAAAAAAAAAAAAA") == fscio::string_to_name("BBBBBBBBBBBBBDDDDDFFFGG") , "fscio::string_to_name BBBBBBBBBBBBBDDDDDFFFGG" );
}

void test_types::name_class() {

   fscio_assert( fscio::name{fscio::string_to_name("azAA34")}.value == N(azAA34), "fscio::name != N(azAA34)" );
   fscio_assert( fscio::name{fscio::string_to_name("AABBCC")}.value == 0, "fscio::name != N(0)" );
   fscio_assert( fscio::name{fscio::string_to_name("AA11")}.value == N(AA11), "fscio::name != N(AA11)" );
   fscio_assert( fscio::name{fscio::string_to_name("11AA")}.value == N(11), "fscio::name != N(11)" );
   fscio_assert( fscio::name{fscio::string_to_name("22BBCCXXAA")}.value == N(22), "fscio::name != N(22)" );
   fscio_assert( fscio::name{fscio::string_to_name("AAAbbcccdd")} == fscio::name{fscio::string_to_name("AAAbbcccdd")}, "fscio::name == fscio::name" );

   uint64_t tmp = fscio::name{fscio::string_to_name("11bbcccdd")};
   fscio_assert(N(11bbcccdd) == tmp, "N(11bbcccdd) == tmp");
}
