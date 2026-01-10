#include <cstdint>
#include <string>
#include <stdexcept>
#include <vector>
#include <array>
#include <cmath>

#pragma once

namespace des_fun
{
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

  /// @brief For ease of use with the sboxes
  typedef std::array<std::array<uint8_t, 16>, 4> sbox;

  /// @brief For easier usage/handling of a single sbox array.
  typedef std::array<sbox, 8> a_sboxes;

  /// @brief The initial permutationt able used in DES encryption. @note often referred to as IP.
  inline const std::vector<uint16_t> int_perm_table = {58, 50, 42, 34, 26, 18, 10, 2,
                                                       60, 52, 44, 36, 28, 20, 12, 4, 
                                                       62, 54, 46, 38, 30, 22, 14, 6, 
                                                       64, 56, 48, 40, 32, 24, 16, 8,
                                                       57, 49, 41, 33, 25, 17, 9, 1,
                                                       59, 51, 43, 35, 27, 19, 11, 3,
                                                       61, 53, 45, 37, 29, 21, 13, 5,
                                                       63, 55, 47, 39, 31, 23, 15, 7};                                          
  
  /// @brief The second choice permutation table. @note often referred to as PC-2.
  inline const std::vector<uint16_t> sec_perm_table = {14, 17, 11, 24, 1, 5, 3, 28,
                                                       15, 6, 21, 10, 23, 19, 12, 4,
                                                       26, 8, 16, 7, 27, 20, 13, 2,
                                                       41, 52, 31, 37, 47, 55, 30, 40,
                                                       51, 45, 33, 48, 44, 49, 39, 56,
                                                       34, 53, 46, 42, 50, 36, 29, 32};

  /// @brief The first choice permutation table. @note often referred to as PC-1
  inline const std::vector<uint16_t> fir_perm_table = {57, 49, 41, 33, 25, 17, 9,
                                                       1, 58, 50, 42, 34, 26, 18,
                                                       10, 2, 59, 51, 43, 35, 27,
                                                       19, 11, 3, 60, 52, 44, 36,
                                                       63, 55, 47, 39, 31, 23, 15,
                                                       7, 62, 54, 46, 38, 30, 22,
                                                       14, 6, 61, 53, 45, 37, 29,
                                                       21, 13, 5, 28, 20, 12, 4};

  /// @brief The expansion function permutation table. @note often referred to as E.
  inline const std::vector<uint16_t> exp_perm_table = {32, 1, 2, 3, 4, 5,
                                                       4, 5, 6, 7, 8, 9,
                                                       8, 9, 10, 11, 12, 13,
                                                       12, 13, 14, 15, 16, 17,
                                                       16, 17, 18, 19, 20, 21,
                                                       20, 21, 22, 23, 24, 25,
                                                       24, 25, 26, 27, 28, 29,
                                                       28, 29, 30, 31, 32, 1};

  /// @brief The inverse permutation table (Final permutation table). @note often referred to as IP^-1
  inline const std::vector<uint16_t> inv_perm_table = {40, 8, 48, 16, 56, 24, 64, 32,
                                                       39, 7, 47, 15, 55, 23, 63, 31,
                                                       38, 6, 46, 14, 54, 22, 62, 30,
                                                       37, 5, 45, 13, 53, 21, 61, 29,
                                                       36, 4, 44, 12, 52, 20, 60, 28,
                                                       35, 3, 43, 11, 51, 19, 59, 27,
                                                       34, 2, 42, 10, 50, 18, 58, 26,
                                                       33, 1, 41, 9, 49, 17, 57, 25};

  /// @brief The P box permutation table. @note often referred to as P.
  inline const std::vector<uint16_t> pbox_perm_table = {16, 7, 20, 21, 29, 12, 28, 17,
                                                        1, 15, 23, 26, 5, 18, 31, 10,
                                                        2, 8, 24, 14, 32, 27, 3, 9,
                                                        19, 13, 30, 6, 22, 11, 4, 25};

  /// @brief The first substitution box.
  inline constexpr sbox sbox_one =
  {{
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
  }};

  /// @brief The second substitution box.
  inline constexpr sbox sbox_two =
  {{
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
    {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
  }};

  /// @brief The third substitution box.
  inline constexpr sbox sbox_three =
  {{
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
    {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
    {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
    {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
  }};

  /// @brief The fourth substitution box.
  inline constexpr sbox sbox_four =
  {{
    {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
    {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
    {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
  }};

  /// @brief The fifth substitution box.
  inline constexpr sbox sbox_five =
  {{
    {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
    {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
    {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
    {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
  }};

  /// @brief The sixth substitution box.
  inline constexpr sbox sbox_six =
  {{
    {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
    {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
    {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
  }};

  /// @brief The seventh substitution box.
  inline constexpr sbox sbox_seven =
  {{
    {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
    {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
    {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
    {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
  }};

  /// @brief The eigth substitution box.
  inline constexpr sbox sbox_eight =
  {{
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
    {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
    {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
    {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
  }};

  /// @brief Array to easily obtain the correct substition box.
  static a_sboxes sboxes =
  {
    sbox_one,
    sbox_two, 
    sbox_three, 
    sbox_four, 
    sbox_five, 
    sbox_six, 
    sbox_seven, 
    sbox_eight
  };

  /**
   * @brief Enum containing the numerous differ data sizes that are used within
   * the algorithm.
   */
  enum data_size
  {
    size_64 = 64, ///< 64 bits
    size_56 = 56, ///< 56 bits
    size_48 = 48, ///< 48 bits
    size_42 = 42, ///< 42 bits
    size_32 = 32, ///< 32 bits
    size_28 = 28, ///< 28 bits
    size_8 = 8,   ///<  8 bits
    size_6 = 6,   ///<  6 bits
    size_4 = 4    ///<  4 bits
  };

  /**
   * @brief Generates a needed mask based on the provided bit position
   * @param pos where in the bit "array" you need the mask for.
   * @return mask of 1s going up to the designated position.
   */
  inline constexpr uint64_t gen_mask(uint64_t pos) { return (1ULL << pos) - 1; }

  /// @brief The total number of fiestel rounds used in the algorithm.
  inline constexpr uint8_t total_fiestel_rounds = 16;

  /**
   * @brief Implements permutation tables in an MSB manner to ensure
   * proper implementation of DES encryption standard.
   * @param perm_table The permutation table to use.
   * @param value The value to be permutated.
   * @param input_width The width of valid bits with in the provided value.
   * e.g., 32 for a 32 bit value or 48 for a 48 bit value.
   * @return The permutated value.
   */
  uint64_t permutate_msb(const std::vector<uint16_t>& perm_table,
                         uint64_t value, 
                         uint8_t input_width);

  /**
   * @brief This class handles the generation of keys per fiestel round.
   * @note this class also keeps track of which fiestel round is the current.
   */
  class des_key
  {
    public:
    /// @brief Default constructor
    des_key() :
    round_counter(0)
    {};

    /**
     * @brief Default constructor with the ability to provide an initial key.
     * @param key The first key to be used.
     */
    des_key(uint64_t key) :
    i_key(key),
    round_counter(0)
    {};

    /**
     * @brief Sets the initial key. Changing the initial key restarts the counter.
     * @note This is intended to only be used when restarting the encryption.
     * @param key The key to be used when encrypting.
     */
    void set_i_key(uint64_t key);

    /**
     * @brief Provides the counter value for the current round.
     * @return The current round.
     */
    uint8_t get_current_round() const { return round_counter; }

    /** 
     * @brief Provides the key for this specific round.
     * Each call will move the round forward.
     * @note this means this is intended to be called once.
     * @return the current round's key. 
     */
    uint64_t get_round_key();

    private:
    /**
     * @brief Conducts the initital transformation on the i_key that is needed
     * for DES encryption.
     */
    void initial_key_trans();

    /**
     * @brief Shifts a 28 bit value by the provide number of n bits
     * in the leftward cirular motion.
     * @param value 
     * @param shift_bit_size 
     * @return uint32_t 
     */
    uint32_t left_n_bit_circle_shift(uint32_t value,  
                                     uint8_t shift_bit_size);

    /// @brief Maintains the initial key provided.
    uint64_t i_key;

    /// @brief For containing the key
    des_fun::splits curr_round_key;

    /// @brief For containing the 28 bit left key
    uint32_t left_key;

    /// @brief For containing the 28 bit right key
    uint32_t right_key;

    /// @brief Constant expression for number of bits to shift.
    static constexpr uint8_t one_shift_bit = 1;

    /// @brief Constant expression for number of bits to shift.
    static constexpr uint8_t two_shift_bit = 2;

    /// @brief Constant expression for indicating number of bits in the two key halves.
    static constexpr uint8_t key_halves_bit_size = 28;

    /// @brief For keeping track of which round we are currently in.
    uint8_t round_counter;

    /// @brief For easily indexing to the correct shift bit for each round.
    std::array<uint8_t, 16> fiestel_round_shift_bits
    {
      one_shift_bit, //< fiestel round 1 0
      one_shift_bit, //< fiestel round 2 1
      two_shift_bit, //< fiestel round 3 2
      two_shift_bit, //< fiestel round 4 3 
      two_shift_bit, //< fiestel round 5 4
      two_shift_bit, //< fiestel round 6 5
      two_shift_bit, //< fiestel round 7 6
      two_shift_bit, //< fiestel round 8 7
      one_shift_bit, //< fiestel round 9 8
      two_shift_bit, //< fiestel round 10 9
      two_shift_bit, //< fiestel round 11 10
      two_shift_bit, //< fiestel round 12 11
      two_shift_bit, //< fiestel round 13 12
      two_shift_bit, //< fiestel round 14 13
      two_shift_bit, //< fiestel round 15 14
      one_shift_bit  //< fiestel round 16 15
    };
  }; // End class des_key

  class encryptor
  {
    public:
    /// @brief Default constructor
    encryptor() {};
    
    /**
     * @brief Function used to encrypt data for DES algorithm.
     * @param data Data to encrypt.
     * @param key The key used for encryption.
     * @return The encrypted value.
     */
    uint64_t encrypt(uint64_t data, uint64_t key);

    private:
    /**
     * @brief The xor data and key part of the DES encryption algorithm/
     * @param value The 48 bit data value to be XORed.
     * @param key_48 The 48 bit key value to be XORed.
     * @return uint64_t 
     */
    uint64_t xor_data_key(uint64_t value, uint64_t key_48) const;

    /**
     * @brief This function will process the specific 4 bit value for the
     * specific subsitution box provided.
     * @param sbox_n The substitution box to be used.
     * @param value The 6 bit data used to obtain the new data value from the
     * substitution box.
     * @return the processed valued.
     */
    uint8_t proc_n_sbox(const des_fun::sbox& sbox_n, uint8_t value) const;

    /**
     * @brief This function handles generating the 32bit data value obtained
     * from the substitution part of the DES key algorithm.
     * @param data_48 The data to be used in the substitution boxes.
     * @return the proccessed substitution box data. 
     */
    uint32_t proc_sbox(uint64_t data_48) const;

    /**
     * @brief This function handles the mangler function portion of the DES
     * algorithm. It will produce a uint32_t value from combining the right
     * half of the data and the provided 48 bit key.
     * @param data_right part of the data to be combined with the 48 bit key.
     * @param key_48 the 48 bit key to be combined with the right half of the data.
     * @return the generated uint32_t value.
     */
    uint32_t mangler_func(uint32_t data_right, uint64_t key_48) const;

    /// @brief The key used for encrypting.
    des_fun::des_key e_key;
  };
} // end namespace des_fun