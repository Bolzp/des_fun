#include <cstdint>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>

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

union test
{
  uint64_t value = 0;
  struct
  {
    uint64_t right: 48;
    uint64_t extra: 16;
  } parts;
};

std::vector<uint16_t> int_perm_table = {58, 50, 42, 34, 26, 18, 10, 2,
                                        60, 52, 44, 36, 28, 20, 12, 4, 
                                        62, 54, 46, 38, 30, 22, 14, 6, 
                                        64, 56, 48, 40, 32, 24, 16, 8,
                                        57, 49, 41, 33, 25, 17, 9, 1,
                                        59, 51, 43, 35, 27, 19, 11, 3,
                                        61, 53, 45, 37, 29, 21, 13, 5,
                                        63, 55, 47, 39, 31, 23, 15, 7};                                          

std::vector<uint16_t> sec_perm_table = {14, 17, 11, 24, 1, 5, 3, 28,
                                       15, 6, 21, 10, 23, 19, 12, 4,
                                       26, 8, 16, 7, 27, 20, 13, 2,
                                       41, 52, 31, 37, 47, 55, 30, 40,
                                       51, 45, 33, 48, 44, 49, 39, 56,
                                       34, 53, 46, 42, 50, 36, 29, 32,
                                       0, 0, 0, 0, 0, 0, 0, 0};

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

uint64_t permutate_msb(std::vector<uint16_t> perm_table, uint64_t value)
{
  std::cout << perm_table.size() << std::endl;
  uint64_t new_val = 0;
  for(auto i = 0; i < perm_table.size(); i++)
  {
    new_val |= ((value >> (perm_table.size() - perm_table.at(i))) & 1) << (perm_table.size() - (i + 1));
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

uint64_t sixtyfour_to_fiftysix_con_msb(uint64_t key)
{
  uint64_t new_val = 0;
  uint64_t par_bits = 0;
  uint8_t skip_shift = 8;
  for(auto i = 0; i < 64; i++)
    if((i + 1) % 8 != 0)
    {
      new_val |= ((key >> (64 - i)) & 1) << ((64 - ( i + 1 )) - skip_shift);
    }
    else
    {
      par_bits = ((key >> (64 - i)) & 1) << (64 - i);
      skip_shift--;
    }
  return new_val;
}

uint64_t gen_mask(uint8_t size)
{
  if(size % 2 != 0)
  {
    throw std::invalid_argument(std::to_string(size));
  }
  return (1 << (size / 2)) - 1; 
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
  split.value = (is_lsb ? sixtyfour_to_fiftysix_con_lsb(value) : 
                          sixtyfour_to_fiftysix_con_msb(value));
  
  return split;
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
  uint32_t new_value = value << shift_bit_size;
  new_value |= (new_value >> valid_bits);
  return new_value;
  //return new_value >> valid_bits;
}

uint64_t gen_round_key(splits two_halves, bool is_lsb = false)
{
  std::cout << two_halves.value << std::endl;
  uint64_t new_val = (is_lsb ? permutate_lsb(sec_perm_table, two_halves.value) : 
                             permutate_msb(sec_perm_table, two_halves.value));
  uint64_t mask = ((1ULL << 48) - 1);
  test a;
  a.value = new_val;
  auto b = new_val & mask;
  return b;
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
  std::cout << permutate_lsb(int_perm_table, 81985529216486895) << std::endl;
  std::cout << permutate_lsb(int_perm_table, 288230376151711744) << std::endl;
  std::cout << permutate_lsb(int_perm_table, pow(2, 58)) << std::endl;
  std::cout << permutate_msb(int_perm_table, pow(2, 6)) << std::endl;
  std::cout << permutate_msb(int_perm_table, 64) << std::endl;
  std::cout << permutate_msb(sec_perm_table, pow(2, 41)) << std::endl;

  std::cout << "bye world!" << std::endl;
}