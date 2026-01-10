# DES Fun
This project is a side project implementing the **Data Encryption Standard (DES)**
encryption algorithm in C++. It was inspired by a discussion with a friend who
implemented DES in Python as part of a college course.

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
The executable will be generated in the `build/bin/` directory.

## Usage
```
./bin/des_fun
```
Running the executable performs a basic encryption test using known DES test vectors and prints the results to standard output.

## Notes
* No external cryptography libraries are used.
* All permutation tables and S-boxes are defined explicitly
* Bit operations are performed MSB-first, following the DES specification

## Potential Future improvements:
* Unit Testing
* Decryption
