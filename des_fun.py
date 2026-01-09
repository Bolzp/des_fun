from ctypes import c_uint64, c_uint32
                 # 1   2    3  4   5   6   7   8
int_perm_table = [58, 50, 42, 34, 26, 18, 10, 2,
                  60, 52, 44, 36, 28, 20, 12, 4, 
                  62, 54, 46, 38, 30, 22, 14, 6, 
                  64, 56, 48, 40, 32, 24, 16, 8,
                  57, 49, 41, 33, 25, 17, 9, 1,
                  59, 51, 43, 35, 27, 19, 11, 3,
                  61, 53, 45, 37, 29, 21, 13, 5,
                  63, 55, 47, 39, 31, 23, 15, 7]

test_perm_table = [1, 2, 0]

def get_bit(pos, value):
    mask = 1 << pos
    return value & mask

def permutate(some_table: list, value):
    new_val = 0
    for i, pos in enumerate(some_table):
        new_val |= ((value >> (len(some_table) - pos)) & 1) << ((len(some_table) - 1) - i)
    return new_val

def six4_five6_key_con(key):
    new_val = 0x0000000000000000
    par_bits = 0
    for i in range(64):
        if (i % 8 != 0):
            new_val |= (key >> (64 - i) & 1) << (58 - i)
        else:
            par_bits = (key >> (64 - i) & 1) << (64 - i)
    print(par_bits)
    return new_val

def cal_check():
    a = 64
    skip_shift = 8
    for i in range(64):
        # if(i == 0):
        #   b = 64 - (i + 1)
        #   c = b - (skip_shift)
        #   print(str(i) +"|"+str(b) + "|" + str(c))
        if((i +1) % 8 != 0):
          b = 64 - (i + 1)
          c = b - skip_shift
          print(str(i) +"|"+str(b) + "|" + str(c))
        else:
            skip_shift -= 1

def cal_2_check():
    a = 64
    for i in range(8,64):
        print(64-i)




# print(0x123456ABCD132536)

# print(get_bit(2, 4))

# print(permutate(test_perm_table, 5))
# print(permutate(int_perm_table, 18446744073709551615) == 18446744073709551615)
# print(permutate(int_perm_table, 81985529216486895) )
# print(permutate(int_perm_table, 0x123456789abcdef)

# cal_check()

# a = "00101101001101101000011100100010011111111110101101111111"
# print(len(a))
# b = a[:28]
# c = a[28:]
# print(len(b))
# print(c)

cal_2_check()