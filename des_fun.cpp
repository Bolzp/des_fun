#include <cstdint>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <array>
#include <cmath>

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
                                       34, 53, 46, 42, 50, 36, 29, 32};

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

std::vector<uint16_t> pbox_perm_table = {16, 7, 20, 21, 29, 12, 28, 17,
                                         1, 15, 23, 26, 5, 18, 31, 10,
                                         2, 8, 24, 14, 32, 27, 3, 9,
                                         19, 13, 30, 6, 22, 11, 4, 25};

typedef std::array<std::array<uint8_t, 16>, 4> sbox;
typedef std::array<sbox, 8> a_sboxes;

sbox sbox_one =
{{
  {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
  {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
  {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
  {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
}};

sbox sbox_two =
{{
  {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
  {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
  {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
  {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
}};

sbox sbox_three =
{{
  {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
  {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
  {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
  {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
}};

sbox sbox_four =
{{
  {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
  {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
  {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
  {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
}};

sbox sbox_five =
{{
  {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
  {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
  {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
  {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
}};

sbox sbox_six =
{{
  {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
  {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
  {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
  {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
}};

sbox sbox_seven =
{{
  {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
  {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
  {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
  {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
}};

sbox sbox_eight =
{{
  {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
  {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
  {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
  {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
}};

a_sboxes sboxes =
{
  sbox_one, sbox_two, sbox_three, sbox_four, sbox_five, sbox_six, sbox_seven, sbox_eight
};

uint64_t permutate_msb(const std::vector<uint16_t>& perm_table, uint64_t value, const uint8_t& input_width)
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

uint64_t gen_mask(const uint8_t& size)
{
  return (1ULL << size) - 1; 
}

uint64_t xor_plain_and_key(const uint64_t& value, const uint64_t& key_48)
{
  return (value ^ key_48) & ((1ULL << 48) - 1);
}

uint8_t proc_n_sbox(const sbox& sbox_n, const uint8_t& value)
{
  uint8_t row = ((value >> 5) & 1) * 2 + (value & 1);
  uint8_t column = (value >> 1) & gen_mask(4);
  return sbox_n.at(row).at(column);

}

uint32_t proc_sbox(const uint64_t& data_48)
{
  uint32_t new_val = 0;
  for(auto i = 0; i < 8; i++)
  {
    uint8_t shift_index = (6 * i);
    new_val |= static_cast<uint32_t>((proc_n_sbox(sboxes.at(i), ((data_48 >> (42 - shift_index)) & gen_mask(6))) & gen_mask(4)) << (28 - (4 * i)));
  }
  return new_val;
}

uint32_t mangler_func(const uint32_t& data_right, const uint64_t& key_48)
{
  uint64_t data_half = permutate_msb(exp_perm_table, data_right, 32);
  uint64_t xor_key = xor_plain_and_key(data_half, key_48);
  data_half = proc_sbox(xor_key);
  data_half = static_cast<uint32_t>(permutate_msb(pbox_perm_table, data_half, 32));
  return data_half;
}

uint32_t xor_32uint_t(const uint32_t& data_left, const uint32_t& key_32)
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

  uint64_t gen_round_key(const uint64_t& value)
  {
    uint64_t new_val = permutate_msb(sec_perm_table, value, 56);
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
  uint32_t left_n_bit_circle_shift(const uint32_t& value, 
                                   const uint32_t& valid_bits, 
                                   const uint8_t& shift_bit_size)
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
  splits get_halves(const uint64_t& value, 
                    const uint8_t& size)
  {
    splits split;

  
    split.value = permutate_msb(fir_perm_table, value, 64);
  
    return split;
  }

  uint64_t i_key;
  splits curr_round_key;

  uint8_t round_counter;
};

uint64_t encrypt(uint64_t data,
                 const uint64_t& key)
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

  // std::cout << encrypt(0x123456ABCD132536, 0xAABB09182736CCDD) << std::endl;
  std::cout << encrypt(1, 0xAABB09182736CCDD) << std::endl;
  std::cout << (encrypt(0x1200000000000000, 0xAABB09182736CCDD) == 0x492967C4E99F8523) << std::endl;

  std::cout << (encrypt(0x0123456789ABCDEF, 0x133457799BBCDFF1) == 0x85E813540F0AB405) << std::endl;
  std::cout << (encrypt(0x23456ABCD132536a, 0xAABB09182736CCDD) == 0xC2490D5EC178E1D3) << std::endl;

  std::cout << "bye world!" << std::endl;
}