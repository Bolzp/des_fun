#include <cstdint>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <map>

// struct splits
// {
//   uint32_t left;
//   uint32_t right;
// };

union splits
{
  splits()
  {
    value = 0;
    halves.extra = 0;
    halves.left = 0;
    halves.right = 0;
  }
  uint64_t value = 0;
  struct
  {
    uint64_t right: 28;
    uint64_t left: 28;
    uint64_t extra: 8;
  } halves;
};

// union test
// {
//   uint64_t value = 0;
//   struct
//   {
//     uint64_t right: 48;
//     uint64_t extra: 16;
//   } parts;
// };

std::vector<uint16_t> int_perm_table = {58, 50, 42, 34, 26, 18, 10, 2,
                                        60, 52, 44, 36, 28, 20, 12, 4, 
                                        62, 54, 46, 38, 30, 22, 14, 6, 
                                        64, 56, 48, 40, 32, 24, 16, 8,
                                        57, 49, 41, 33, 25, 17, 9, 1,
                                        59, 51, 43, 35, 27, 19, 11, 3,
                                        61, 53, 45, 37, 29, 21, 13, 5,
                                        63, 55, 47, 39, 31, 23, 15, 7};                                          

// std::vector<uint16_t> sec_perm_table = {14, 17, 11, 24, 1, 5, 3, 28,
//                                        15, 6, 21, 10, 23, 19, 12, 4,
//                                        26, 8, 16, 7, 27, 20, 13, 2,
//                                        41, 52, 31, 37, 47, 55, 30, 40,
//                                        51, 45, 33, 48, 44, 49, 39, 56,
//                                        34, 53, 46, 42, 50, 36, 29, 32,
//                                        0, 0, 0, 0, 0, 0, 0, 0};

std::vector<uint16_t> sec_perm_table = {14, 17, 11, 24, 1, 5, 3, 28,
                                       15, 6, 21, 10, 23, 19, 12, 4,
                                       26, 8, 16, 7, 27, 20, 13, 2,
                                       41, 52, 31, 37, 47, 55, 30, 40,
                                       51, 45, 33, 48, 44, 49, 39, 56,
                                       34, 53, 46, 42, 50, 36, 29, 32};

// std::vector<uint16_t> fir_perm_table = {1, 2, 3, 4, 5, 6, 7,
//                                         9, 10, 11, 12, 13, 14, 15,
//                                         17, 18, 19, 20, 21, 22, 23,
//                                         25, 26, 27, 28, 29, 30, 31,
//                                         33, 34, 35, 36, 37, 38, 39,
//                                         41, 42, 43, 44, 45, 46, 47,
//                                         49, 50, 51, 52, 53, 54, 55,
//                                         57, 58, 59, 60, 61, 62, 63};

std::vector<uint16_t> fir_perm_table = {57, 49, 41, 33, 25, 17, 9,
                                        1, 58, 50, 42, 34, 26, 18,
                                        10, 2, 59, 51, 43, 35, 27,
                                        19, 11, 3, 60, 52, 44, 36,
                                        63, 55, 47, 39, 31, 23, 15,
                                        7, 62, 54, 46, 38, 30, 22,
                                        14, 6, 61, 53, 45, 37, 29,
                                        21, 13, 5, 28, 20, 12, 4};

std::vector<uint16_t> exp_perm_table = {32, 1, 2, 3, 4, 5,
                                        4, 5, 6, 7, 8, 9,
                                        8, 9, 10, 11, 12, 13,
                                        12, 13, 14, 15, 16, 17,
                                        16, 17, 18, 19, 20, 21,
                                        20, 21, 22, 23, 24, 25,
                                        24, 25, 26, 27, 28, 29,
                                        28, 29, 30, 31, 32, 1};

std::vector<uint16_t> inv_perm_table = {40, 8, 48, 16, 56, 24, 64, 32,
                                        39, 7, 47, 15, 55, 23, 63, 31,
                                        38, 6, 46, 14, 54, 22, 62, 30,
                                        37, 5, 45, 13, 53, 21, 61, 29,
                                        36, 4, 44, 12, 52, 20, 60, 28,
                                        35, 3, 43, 11, 51, 19, 59, 27,
                                        34, 2, 42, 10, 50, 18, 58, 26,
                                        33, 1, 41, 9, 49, 17, 57, 25};

std::map<uint8_t, uint8_t> sbox_1 =
{
  {0b000000, 14}, {0b000010, 4},  {0b000100, 13}, {0b000110, 1},  {0b001000, 2},  
  {0b000001, 0},  {0b000011, 15}, {0b000101, 7},  {0b000111, 4},  {0b001001, 14}, 
  {0b100000, 4},  {0b100010, 1},  {0b100100, 14}, {0b100110, 8},  {0b101000, 13}, 
  {0b100001, 15}, {0b100011, 12}, {0b100101, 8},  {0b100111, 2},  {0b101001, 4},  

  {0b001010, 15}, {0b001100, 11}, {0b001110, 8},  {0b010000, 3},  {0b010010, 10},
  {0b001011, 2},  {0b001101, 13}, {0b001111, 1},  {0b010001, 10}, {0b010011, 6},
  {0b101010, 6},  {0b101100, 2},  {0b101110, 11}, {0b110000, 15}, {0b110010, 12},
  {0b101011, 9},  {0b101101, 1},  {0b101111, 7},  {0b110001, 5},  {0b110011, 11},
                                         
  {0b010100, 6},  {0b010110, 12}, {0b011000, 5},  {0b011010, 9},  {0b011100, 0},
  {0b010101, 12}, {0b010111, 11}, {0b011001, 9},  {0b011011, 5},  {0b011101, 3},
  {0b110100, 9},  {0b110110, 7},  {0b111000, 3},  {0b111010, 10}, {0b111100, 5},
  {0b110101, 3},  {0b110111, 14}, {0b111001, 10}, {0b111011, 0},  {0b111101, 6},
  
  {0b011110, 7},
  {0b011111, 8},
  {0b111110, 0},
  {0b111111, 13}
};

std::map<uint8_t, uint8_t> sbox_2 =
{
  {0b000000, 15}, {0b000010, 1},  {0b000100, 8},  {0b000110, 14}, {0b001000, 6},  
  {0b000001, 3},  {0b000011, 13}, {0b000101, 4},  {0b000111, 7},  {0b001001, 15}, 
  {0b100000, 0},  {0b100010, 14}, {0b100100, 7},  {0b100110, 11}, {0b101000, 10}, 
  {0b100001, 13}, {0b100011, 8},  {0b100101, 10}, {0b100111, 1},  {0b101001, 3},  

  {0b001010, 11}, {0b001100, 3},  {0b001110, 4},  {0b010000, 9},  {0b010010, 7},
  {0b001011, 2},  {0b001101, 8},  {0b001111, 14}, {0b010001, 12}, {0b010011, 0},
  {0b101010, 4},  {0b101100, 13}, {0b101110, 1},  {0b110000, 5},  {0b110010, 8},
  {0b101011, 15}, {0b101101, 4},  {0b101111, 2},  {0b110001, 11}, {0b110011, 6},
                                         
  {0b010100, 2},  {0b010110, 13}, {0b011000, 12}, {0b011010, 0}, {0b011100, 5},
  {0b010101, 1},  {0b010111, 10}, {0b011001, 6},  {0b011011, 9}, {0b011101, 11},
  {0b110100, 12}, {0b110110, 6},  {0b111000, 9},  {0b111010, 3}, {0b111100, 2},
  {0b110101, 7},  {0b110111, 12}, {0b111001, 2},  {0b111011, 5}, {0b111101, 14},
  
  {0b011110, 10},
  {0b011111, 5},
  {0b111110, 15},
  {0b111111, 9}
};

std::map<uint8_t, uint8_t> sbox_3 =
{
  {0b000000, 10}, {0b000010, 0},  {0b000100, 9},  {0b000110, 14}, {0b001000, 6},  
  {0b000001, 13}, {0b000011, 7},  {0b000101, 0},  {0b000111, 9},  {0b001001, 3}, 
  {0b100000, 13}, {0b100010, 6},  {0b100100, 4},  {0b100110, 9},  {0b101000, 8}, 
  {0b100001, 1},  {0b100011, 10}, {0b100101, 13}, {0b100111, 0},  {0b101001, 6},  

  {0b001010, 3},  {0b001100, 15}, {0b001110, 5},  {0b010000, 1},  {0b010010, 13},
  {0b001011, 4},  {0b001101, 6},  {0b001111, 10}, {0b010001, 2},  {0b010011, 8},
  {0b101010, 15}, {0b101100, 3},  {0b101110, 0},  {0b110000, 11}, {0b110010, 1},
  {0b101011, 9},  {0b101101, 8},  {0b101111, 7},  {0b110001, 4},  {0b110011, 15},
                                         
  {0b010100, 12}, {0b010110, 7},  {0b011000, 11}, {0b011010, 4},  {0b011100, 2},
  {0b010101, 5},  {0b010111, 14}, {0b011001, 12}, {0b011011, 11}, {0b011101, 15},
  {0b110100, 2},  {0b110110, 12}, {0b111000, 5},  {0b111010, 10}, {0b111100, 14},
  {0b110101, 14}, {0b110111, 3},  {0b111001, 11}, {0b111011, 5},  {0b111101, 2},
  
  {0b011110, 8},
  {0b011111, 1},
  {0b111110, 7},
  {0b111111, 12}
};

std::map<uint8_t, uint8_t> sbox_4 =
{
  {0b000000, 7},  {0b000010, 13}, {0b000100, 14}, {0b000110, 3},  {0b001000, 0},  
  {0b000001, 13}, {0b000011, 8},  {0b000101, 11}, {0b000111, 5},  {0b001001, 6}, 
  {0b100000, 10}, {0b100010, 6},  {0b100100, 9},  {0b100110, 0},  {0b101000, 12}, 
  {0b100001, 3},  {0b100011, 15}, {0b100101, 0},  {0b100111, 6},  {0b101001, 10},  

  {0b001010, 6},  {0b001100, 9},  {0b001110, 10}, {0b010000, 1},  {0b010010, 2},
  {0b001011, 15}, {0b001101, 0},  {0b001111, 3},  {0b010001, 4},  {0b010011, 7},
  {0b101010, 11}, {0b101100, 7},  {0b101110, 13}, {0b110000, 15}, {0b110010, 1},
  {0b101011, 1},  {0b101101, 13}, {0b101111, 8},  {0b110001, 9},  {0b110011, 4},
                                         
  {0b010100, 8},  {0b010110, 5},  {0b011000, 11}, {0b011010, 12}, {0b011100, 4},
  {0b010101, 2},  {0b010111, 12}, {0b011001, 1},  {0b011011, 10}, {0b011101, 14},
  {0b110100, 3},  {0b110110, 14}, {0b111000, 5},  {0b111010, 2},  {0b111100, 8},
  {0b110101, 5},  {0b110111, 11}, {0b111001, 12}, {0b111011, 7},  {0b111101, 2},
  
  {0b011110, 15},
  {0b011111, 9},
  {0b111110, 4},
  {0b111111, 14}
};

std::map<uint8_t, uint8_t> sbox_5 =
{
  {0b000000, 2},  {0b000010, 12}, {0b000100, 4},  {0b000110, 1},  {0b001000, 7},  
  {0b000001, 14}, {0b000011, 11}, {0b000101, 2},  {0b000111, 12}, {0b001001, 4}, 
  {0b100000, 4},  {0b100010, 2},  {0b100100, 1},  {0b100110, 11}, {0b101000, 10}, 
  {0b100001, 11}, {0b100011, 8},  {0b100101, 12}, {0b100111, 7},  {0b101001, 1},  

  {0b001010, 10}, {0b001100, 11}, {0b001110, 6},  {0b010000, 8},  {0b010010, 5},
  {0b001011, 7},  {0b001101, 13}, {0b001111, 1},  {0b010001, 5},  {0b010011, 0},
  {0b101010, 13}, {0b101100, 7},  {0b101110, 8},  {0b110000, 15}, {0b110010, 9},
  {0b101011, 14}, {0b101101, 2},  {0b101111, 13}, {0b110001, 6},  {0b110011, 15},
                                         
  {0b010100, 3},  {0b010110, 15}, {0b011000, 13}, {0b011010, 0},  {0b011100, 14},
  {0b010101, 15}, {0b010111, 10}, {0b011001, 3},  {0b011011, 9},  {0b011101, 8},
  {0b110100, 12}, {0b110110, 5},  {0b111000, 6},  {0b111010, 3},  {0b111100, 0},
  {0b110101, 0},  {0b110111, 9},  {0b111001, 10}, {0b111011, 4},  {0b111101, 5},
  
  {0b011110, 9},
  {0b011111, 6},
  {0b111110, 14},
  {0b111111, 3}
};

std::map<uint8_t, uint8_t> sbox_6 =
{
  {0b000000, 12}, {0b000010, 1},  {0b000100, 10}, {0b000110, 15}, {0b001000, 9},  
  {0b000001, 10}, {0b000011, 15}, {0b000101, 4},  {0b000111, 2},  {0b001001, 7}, 
  {0b100000, 9},  {0b100010, 14}, {0b100100, 15}, {0b100110, 5},  {0b101000, 2}, 
  {0b100001, 4},  {0b100011, 3},  {0b100101, 2},  {0b100111, 12}, {0b101001, 9},  

  {0b001010, 2},  {0b001100, 6},  {0b001110, 8},  {0b010000, 0},  {0b010010, 13},
  {0b001011, 12}, {0b001101, 9},  {0b001111, 5},  {0b010001, 6},  {0b010011, 1},
  {0b101010, 8},  {0b101100, 12}, {0b101110, 3},  {0b110000, 7},  {0b110010, 0},
  {0b101011, 5},  {0b101101, 15}, {0b101111, 10}, {0b110001, 11}, {0b110011, 14},
                                         
  {0b010100, 3},  {0b010110, 4},  {0b011000, 14}, {0b011010, 7},  {0b011100, 5},
  {0b010101, 13}, {0b010111, 14}, {0b011001, 0},  {0b011011, 11}, {0b011101, 3},
  {0b110100, 4},  {0b110110, 10}, {0b111000, 1},  {0b111010, 13}, {0b111100, 11},
  {0b110101, 1},  {0b110111, 7},  {0b111001, 6},  {0b111011, 0},  {0b111101, 8},
  
  {0b011110, 11},
  {0b011111, 8},
  {0b111110, 6},
  {0b111111, 13}
};

std::map<uint8_t, uint8_t> sbox_7 =
{
  {0b000000, 4},  {0b000010, 11}, {0b000100, 2},  {0b000110, 14}, {0b001000, 15},  
  {0b000001, 13}, {0b000011, 0},  {0b000101, 11}, {0b000111, 7},  {0b001001, 4}, 
  {0b100000, 1},  {0b100010, 4},  {0b100100, 11}, {0b100110, 13}, {0b101000, 12}, 
  {0b100001, 6},  {0b100011, 11}, {0b100101, 13}, {0b100111, 8},  {0b101001, 1},  

  {0b001010, 0},  {0b001100, 8},  {0b001110, 13}, {0b010000, 3},  {0b010010, 12},
  {0b001011, 9},  {0b001101, 1},  {0b001111, 10}, {0b010001, 14}, {0b010011, 3},
  {0b101010, 3},  {0b101100, 7},  {0b101110, 14}, {0b110000, 10}, {0b110010, 15},
  {0b101011, 4},  {0b101101, 10}, {0b101111, 7},  {0b110001, 9},  {0b110011, 5},
                                         
  {0b010100, 9},  {0b010110, 7},  {0b011000, 5},  {0b011010, 10}, {0b011100, 6},
  {0b010101, 5},  {0b010111, 12}, {0b011001, 2},  {0b011011, 15}, {0b011101, 8},
  {0b110100, 6},  {0b110110, 8},  {0b111000, 0},  {0b111010, 5},  {0b111100, 9},
  {0b110101, 0},  {0b110111, 15}, {0b111001, 14}, {0b111011, 2},  {0b111101, 3},
  
  {0b011110, 1},
  {0b011111, 6},
  {0b111110, 2},
  {0b111111, 12}
};

std::map<uint8_t, uint8_t> sbox_8 =
{
  {0b000000, 13}, {0b000010, 2},  {0b000100, 8},  {0b000110, 4},  {0b001000, 6},  
  {0b000001, 1},  {0b000011, 15}, {0b000101, 13}, {0b000111, 8},  {0b001001, 10}, 
  {0b100000, 7},  {0b100010, 11}, {0b100100, 4},  {0b100110, 1},  {0b101000, 9}, 
  {0b100001, 2},  {0b100011, 1},  {0b100101, 14}, {0b100111, 7},  {0b101001, 4},  

  {0b001010, 15}, {0b001100, 11}, {0b001110, 1},  {0b010000, 10}, {0b010010, 9},
  {0b001011, 3},  {0b001101, 7},  {0b001111, 4},  {0b010001, 12}, {0b010011, 5},
  {0b101010, 12}, {0b101100, 14}, {0b101110, 2},  {0b110000, 0},  {0b110010, 6},
  {0b101011, 10}, {0b101101, 8},  {0b101111, 13}, {0b110001, 15}, {0b110011, 12},
                                         
  {0b010100, 3},  {0b010110, 14}, {0b011000, 5},  {0b011010, 0},  {0b011100, 12},
  {0b010101, 6},  {0b010111, 11}, {0b011001, 0},  {0b011011, 14}, {0b011101, 9},
  {0b110100, 10}, {0b110110, 13}, {0b111000, 15}, {0b111010, 3},  {0b111100, 5},
  {0b110101, 9}, {0b110111, 0},  {0b111001, 3},  {0b111011, 5},  {0b111101, 6},
  
  {0b011110, 7},
  {0b011111, 2},
  {0b111110, 8},
  {0b111111, 11}
};

std::vector<uint16_t> pbox_perm_table = {16, 7, 20, 21, 29, 12, 28, 17,
                                         1, 15, 23, 26, 5, 18, 31, 10,
                                         2, 8, 24, 14, 32, 27, 3, 9,
                                         19, 13, 30, 6, 22, 11, 4, 25};

uint8_t proc_n_sbox(const std::map<uint8_t, uint8_t>* sbox, uint8_t value)
{
  return sbox->at(value);
}

uint64_t permutate_lsb(std::vector<uint16_t> perm_table, uint64_t value)
{
  uint64_t new_val = 0;
  for(auto i = 0; i < perm_table.size(); i++)
  {
    //new_val |= ((value >> perm_table.at(i)) & 1) << (perm_table.size() - (i + 1));
    new_val |= ((value >> perm_table.at(i)) & 1) << (i + 1);
  }
  return new_val;
}

// uint64_t permutate_msb(std::vector<uint16_t> perm_table, uint64_t value)
// {
//   uint64_t new_val = 0;
//   for(auto i = 0; i < perm_table.size(); i++)
//   {
//     // Offset allows us to deal with perm tables that are larger than the real
//     // data set they are dealing. Such as expansion perm table.
//     new_val |= ((value >> ((perm_table.size()) - perm_table.at(i))) & 1) << (perm_table.size() - (i + 1));
//   }
//   return new_val;
// }

uint64_t permutate_msb(std::vector<uint16_t> perm_table, uint64_t value, uint8_t input_width)
{
  uint64_t new_val = 0;
  for(auto i = 0; i < perm_table.size(); i++)
  {
    // Offset allows us to deal with perm tables that are larger than the real
    // data set they are dealing. Such as expansion perm table.
    new_val |= ((value >> (input_width - perm_table.at(i))) & 1) << (perm_table.size() - (i + 1));
  }
  return new_val;
}

uint64_t sixtyfour_to_fiftysix_con_lsb(uint64_t key)
{
  uint64_t new_val = 0;
  uint64_t par_bits = 0;
  uint8_t skip_shift = 8;
  for(auto i = 0; i < 64; i++)
    if((i + 1) % 8 != 0)
    {
      new_val |= ((key >> i) & 1) << ((64 - ( i + 1 )) - skip_shift);
    }
    else
    {
      par_bits = ((key >> i) & 1) << (64 - i);
      skip_shift--;
    }
  return new_val;
}

uint64_t gen_mask(uint8_t size)
{
  return (1ULL << size) - 1; 
}

uint64_t xor_plain_and_key(uint64_t value, uint64_t key_48)
{
  // uint64_t new_val = key_48 & ~(gen_mask(sizeof(value) * 8));
  // for(auto i = 0; i < (sizeof(value) * 8); i++)
  // {
  //   new_val |= (((value >> i) & 1) ^ ((key_48 >> i) & 1)) <<  i;
  // }
  // return new_val;
  return (value ^ key_48) & ((1ULL << 48) - 1);
}

uint32_t proc_sbox(uint64_t data_48)
{
  uint32_t new_val = 0;
  const std::map<uint8_t, uint8_t>* sbox;
  for(auto i = 0; i < 8; i++)
  {
    switch(i)
    {
      case 0:
      sbox = &sbox_1;
      break;
      case 1: 
      sbox = &sbox_2;
      break;
      case 2:
      sbox = &sbox_3;
      break;
      case 3:
      sbox = &sbox_4;
      break;
      case 4:
      sbox = &sbox_5;
      break;
      case 5:
      sbox = &sbox_6;
      break;
      case 6:
      sbox = &sbox_7;
      break;
      case 7:
      sbox = &sbox_8;
      break;
    }
    uint8_t shift_index = (6 * i);
    // auto sbox_value = proc_n_sbox(sbox, ((data_48 & gen_mask(6) << shift_index) >> shift_index));
    // new_val |= sbox_value << (4 * i);
    
    // new_val |= proc_n_sbox(sbox, ((data_48 & (gen_mask(6) << shift_index)) >> shift_index)) << (28 - (4 * i));

    new_val |= static_cast<uint32_t>((proc_n_sbox(sbox, ((data_48 >> (42 - shift_index)) & gen_mask(6))) & gen_mask(4)) << (28 - (4 * i)));
  }
  return new_val;
}

uint32_t mangler_func(uint32_t data_right, uint64_t key_48)
{
  uint64_t data_half = permutate_msb(exp_perm_table, data_right, 32);
  uint64_t xor_key = xor_plain_and_key(data_half, key_48);
  data_half = proc_sbox(xor_key);
  data_half = static_cast<uint32_t>(permutate_msb(pbox_perm_table, data_half, 32));
  return data_half;
}

uint32_t xor_32uint_t(uint32_t data_left, uint32_t key_32)
{
  return data_left ^ key_32;
}

class des_key
{
  public:
  des_key() :
  round_counter(0)
  {};

  des_key(uint64_t key) :
  i_key(key),
  round_counter(0)
  {};

  void set_i_key(uint64_t key)
  {
    i_key = key;
    // if I key changes it's a new encryption.
    round_counter = 0;
    initial_key_trans();
  }

  uint8_t get_current_round() { return round_counter; }

  uint64_t get_round_key()
  {
    switch(round_counter++)
    {
      case 0:
      case 1:
      case 8:
      case 15:
      curr_round_key.halves.left = left_n_bit_circle_shift(curr_round_key.halves.left, 28, 1);
      curr_round_key.halves.right = left_n_bit_circle_shift(curr_round_key.halves.right, 28, 1);
      break;
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      curr_round_key.halves.left = left_n_bit_circle_shift(curr_round_key.halves.left, 28, 2);
      curr_round_key.halves.right = left_n_bit_circle_shift(curr_round_key.halves.right, 28, 2);
      break;
    }
    return permutate_msb(sec_perm_table, curr_round_key.value, 56);
  }

  private:

  void initial_key_trans()
  {
    curr_round_key.value = permutate_msb(fir_perm_table, i_key, 64);
  }

  uint64_t gen_round_key(uint64_t value, bool is_lsb = false)
  {
    uint64_t new_val = (is_lsb ? permutate_lsb(sec_perm_table, value) : 
                               permutate_msb(sec_perm_table, value, 56));
    uint64_t mask = ((1ULL << 48) - 1);
    return new_val & mask;
  }
  /**
   * @brief 
   * @note use 47409266 to get 94818532
   *       and 41937791 to get 83875582 with 1 shifts.
   *       use 47409266 to get 189637064
   *       and 41937791 to get 167751164 with 2 shifts.
   * @param value 
   * @param valid_bits 
   * @param shift_bit_size 
   * @return uint32_t 
   */
  uint32_t left_n_bit_circle_shift(uint32_t value, uint32_t valid_bits, uint8_t shift_bit_size)
  {
    uint32_t mask = gen_mask(valid_bits);
    uint32_t new_value = value & mask;
    return ((new_value << shift_bit_size) | (new_value >> (valid_bits - shift_bit_size))) & mask;
  }

  /**
   * @brief Get the halves object
   * @note use: 12726327979273087
   *       left: 47409266
   *       right: 41937791
   *       to test
   * @param value 
   * @param size 
   * @return splits 
   */
  splits get_halves(uint64_t value, uint8_t size, bool is_lsb = false)
  {
    splits split;
    // split.value = (is_lsb ? sixtyfour_to_fiftysix_con_lsb(value) : 
    //                         sixtyfour_to_fiftysix_con_msb(value));
  
    split.value = (is_lsb ? sixtyfour_to_fiftysix_con_lsb(value) :
                            permutate_msb(fir_perm_table, value, 64));
  
    return split;
  }

  uint64_t i_key;
  splits curr_round_key;

  uint8_t round_counter;
};

uint64_t encrypt(uint64_t data, uint64_t key)
{
  des_key d_key;
  d_key.set_i_key(key);
  data = permutate_msb(int_perm_table, data, 64);
  uint32_t left_half = (data & ~(gen_mask(32))) >> 32;
  uint32_t right_half = data & gen_mask(32);
  while(d_key.get_current_round() < 16)
  {
    uint32_t comp_data = mangler_func(right_half, d_key.get_round_key());
    comp_data = xor_32uint_t(left_half, comp_data);
    left_half = right_half;
    right_half = comp_data;
  }

  uint64_t proc_data = static_cast<uint64_t>(right_half) << 32;
  proc_data |= left_half;
  return permutate_msb(inv_perm_table, proc_data, 64);
}

int main()
{
  std::cout << "hello world!\n";
  // auto b = get_halves(12726327979273087, 56);
  // std::cout << "left: " + std::to_string(b.halves.left) + "\n";
  // std::cout << "right: " + std::to_string(b.halves.right) + "\n";
  // std::cout << left_n_bit_circle_shift(47409266, 28, 1) << std::endl;
  // std::cout << (left_n_bit_circle_shift(47409266, 28, 1) == 94818532) << std::endl;
  // std::cout << (left_n_bit_circle_shift(41937791, 28, 1) == 83875582) << std::endl;
  // std::cout << (left_n_bit_circle_shift(47409266, 28, 2) == 189637064) << std::endl;
  // std::cout << (left_n_bit_circle_shift(41937791, 28, 2) == 167751164) << std::endl;
  // std::cout << permutate_lsb(int_perm_table, 81985529216486895) << std::endl;
  // std::cout << permutate_lsb(int_perm_table, 288230376151711744) << std::endl;
  // std::cout << permutate_lsb(int_perm_table, pow(2, 58)) << std::endl;
  // std::cout << permutate_msb(int_perm_table, pow(2, 6)) << std::endl;
  // std::cout << permutate_msb(int_perm_table, 64) << std::endl;
  // std::cout << permutate_msb(sec_perm_table, pow(2, 41)) << std::endl;
  // std::cout << permutate_msb(int_perm_table, pow(2, 6)) << std::endl;
  // std::cout << permutate_msb(exp_perm_table, pow(2, 0), 16) << std::endl;

  // std::cout << sixtyfour_to_fiftysix_con_msb(18446744073709551615) << std::endl;
  // std::cout << permutate_msb(fir_perm_table, 18446744073709551615) << std::endl;

  // std::cout << gen_round_key(pow(2,41)) << std::endl;
  // std::cout << xor_plain_and_key(0, pow(2,47)) << std::endl;
  // std::cout << xor_plain_and_key(1, (pow(2,47))) << std::endl;

  // std::cout << proc_sbox((pow(2,47)+pow(2,45)+pow(2,43))) << std::endl;

  // uint32_t left_half = (static_cast<uint64_t>(pow(2,63)) & ~(gen_mask(32))) >> 32;
  // uint32_t right_half = 1 & gen_mask(32);
  // std::cout << left_half << std::endl;
  // std::cout << right_half << std::endl;

  // for(auto i = 0; i <= 0b111111; i++)
  // {
  //   try
  //   {
  //     sbox_1.at(i);
  //     sbox_2.at(i);
  //     sbox_3.at(i);
  //     sbox_4.at(i);
  //     sbox_5.at(i);
  //     sbox_6.at(i);
  //     sbox_7.at(i);
  //     sbox_8.at(i);
  //   }
  //   catch(...)
  //   {
  //     std::cout << "missing: " + std::to_string(i) << std::endl;  
  //   }
  // }

  // std::cout << encrypt(0x123456ABCD132536, 0xAABB09182736CCDD) << std::endl;
  std::cout << encrypt(1, 0xAABB09182736CCDD) << std::endl;
  std::cout << (encrypt(1, 0xAABB09182736CCDD) == 14650309254962148617) << std::endl;

  std::cout << "bye world!" << std::endl;
}