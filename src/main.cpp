#include "des_fun.hpp"
#include <iostream>

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
  // std::cout << encrypt(1, 0xAABB09182736CCDD) << std::endl;
  // std::cout << (encrypt(0x1200000000000000, 0xAABB09182736CCDD) == 0x492967C4E99F8523) << std::endl;

  // std::cout << (encrypt(0x0123456789ABCDEF, 0x133457799BBCDFF1) == 0x85E813540F0AB405) << std::endl;
  // std::cout << (encrypt(0x23456ABCD132536a, 0xAABB09182736CCDD) == 0xC2490D5EC178E1D3) << std::endl;

  des_fun::encryptor des_encryptor;

  // auto a = des_encryptor.encrypt(0x1200000000000000, 0xAABB09182736CCDD);
  std::cout << (des_encryptor.encrypt(0x1200000000000000, 0xAABB09182736CCDD) == 0x492967C4E99F8523) << std::endl;
  std::cout << (des_encryptor.encrypt(0x0123456789ABCDEF, 0x133457799BBCDFF1) == 0x85E813540F0AB405) << std::endl;
  std::cout << (des_encryptor.encrypt(0x23456ABCD132536a, 0xAABB09182736CCDD) == 0xC2490D5EC178E1D3) << std::endl;

  std::cout << "bye world!" << std::endl;
}