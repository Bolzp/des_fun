#include "des_fun.hpp"

////////////////////////////////////////////////////////////////////////////////

uint64_t des_fun::permutate_msb(const std::vector<uint16_t>& perm_table, 
                                uint64_t value, 
                                uint8_t input_width)
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

////////////////////////////////////////////////////////////////////////////////

uint64_t des_fun::encryptor::xor_data_key(uint64_t value, 
                                          uint64_t key_48) const
{
  return (value ^ key_48) & (gen_mask(des_fun::size_48));
}

////////////////////////////////////////////////////////////////////////////////

uint8_t des_fun::encryptor::proc_n_sbox(const des_fun::sbox& sbox_n, 
                                        uint8_t value) const
{
  uint8_t row = ((value >> 5) & 1) * 2 + (value & 1);
  uint8_t column = (value >> 1) & des_fun::gen_mask(des_fun::size_4);
  return sbox_n.at(row).at(column);
}

////////////////////////////////////////////////////////////////////////////////

uint32_t des_fun::encryptor::proc_sbox(uint64_t data_48) const
{
  uint32_t new_val = 0;
  uint8_t six_m = des_fun::gen_mask(des_fun::size_6);
  uint8_t four_m = des_fun::gen_mask(des_fun::size_4);
  for(auto i = 0; i < des_fun::size_8; i++)
  {
    uint8_t shift_index = (des_fun::data_size::size_6 * i);
    uint8_t sbox_in = ((data_48 >> (des_fun::size_42 - shift_index)) & six_m);
    uint32_t packet = proc_n_sbox(des_fun::sboxes.at(i), sbox_in) & four_m;
    new_val |= packet << (des_fun::size_28 - (des_fun::size_4 * i));
  }
  return new_val;
}

////////////////////////////////////////////////////////////////////////////////

uint32_t des_fun::encryptor::mangler_func(uint32_t data_right, 
                                          uint64_t key_48) const
{
  uint64_t data_half = des_fun::permutate_msb(des_fun::exp_perm_table, 
                                              data_right, 
                                              des_fun::data_size::size_32);
  uint64_t xor_key = des_fun::encryptor::xor_data_key(data_half, key_48);
  data_half = proc_sbox(xor_key);
  data_half = static_cast<uint32_t>(des_fun::permutate_msb(des_fun::pbox_perm_table, 
                                                           data_half,
                                                           des_fun::data_size::size_32));
  return data_half;
}

////////////////////////////////////////////////////////////////////////////////

void des_fun::des_key::set_i_key(uint64_t key)
{
  i_key = key;
  // if I key changes it's a new encryption.
  round_counter = 0;
  initial_key_trans();
}

////////////////////////////////////////////////////////////////////////////////

uint64_t des_fun::des_key::get_round_key()
{
  uint8_t curr_round = round_counter++;
  // Shift the two halves.
  curr_round_key.halves.left = 
    left_n_bit_circle_shift(curr_round_key.halves.left, 
                            fiestel_round_shift_bits.at(curr_round));
  curr_round_key.halves.right = 
    left_n_bit_circle_shift(curr_round_key.halves.right, 
                            fiestel_round_shift_bits.at(curr_round));
  return des_fun::permutate_msb(des_fun::sec_perm_table, 
                                curr_round_key.value,
                                56);
}

////////////////////////////////////////////////////////////////////////////////

void des_fun::des_key::initial_key_trans()
{
  curr_round_key.value = des_fun::permutate_msb(des_fun::fir_perm_table, i_key, 64);
}

////////////////////////////////////////////////////////////////////////////////

uint32_t des_fun::des_key::left_n_bit_circle_shift(uint32_t value,  
                                                   uint8_t shift_bit_size)
{
  uint32_t mask = gen_mask(des_fun::des_key::key_halves_bit_size);
  uint32_t new_value = value & mask;
  new_value =((new_value << shift_bit_size) | (new_value >> (des_fun::des_key::key_halves_bit_size - shift_bit_size)));
  return new_value & mask;
}

////////////////////////////////////////////////////////////////////////////////

uint64_t des_fun::encryptor::encrypt(uint64_t data, uint64_t key)
{
  e_key.set_i_key(key);

  data = des_fun::permutate_msb(des_fun::int_perm_table, 
                                data,
                                des_fun::data_size::size_64);
  uint32_t left_half = (data & ~(gen_mask(des_fun::data_size::size_32))) >> des_fun::data_size::size_32;
  uint32_t right_half = data & gen_mask(32);
  while(e_key.get_current_round() < des_fun::total_fiestel_rounds)
  {
    uint32_t comp_data = mangler_func(right_half, e_key.get_round_key());
    comp_data = left_half ^ comp_data;
    left_half = right_half;
    right_half = comp_data;
  }

  uint64_t proc_data = static_cast<uint64_t>(right_half) << des_fun::data_size::size_32;
  proc_data |= left_half;
  return des_fun::permutate_msb(des_fun::inv_perm_table, 
                                proc_data,
                                des_fun::data_size::size_64);
}

////////////////////////////////////////////////////////////////////////////////