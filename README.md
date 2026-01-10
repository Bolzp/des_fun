# DES Fun

An educational C++ implementation of the **Data Encryption Standard (DES)**
encryption algorithm.

This project was created as a learning exercise focused on:
- Bit-level manipulation
- Permutation tables and S-box processing
- Implementing a well-defined cryptographic specification in modern C++

For background on the DES algorithm, see:
[Data Encryption Standard (DES)](https://en.wikipedia.org/wiki/Data_Encryption_Standard).

> ⚠️ **Disclaimer**  
> DES is considered cryptographically insecure and is implemented here
> strictly for educational and experimental purposes.

---

## Build

This project uses **CMake**.

```bash
mkdir build
cd build
cmake ..
make
```
The executable will be generated in the `bin/` directory.

## Usage
```
./bin/des_fun
```
Running the executable performs a basic encryption test using known DES test vectors and prints the results to standard output.

## Notes
* No external cryptography libraries are used.
* All permutation tables and S-boxes are defined explicitly
* Bit operations are performed MSB-first, following the DES specification