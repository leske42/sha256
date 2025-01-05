
Tiny Secure Hash 256 algorithm implementation (according to RFC6234) in C++. Probably has bugs I don't know about yet and isn't optimized at all. But it works & I made it big-endian to match the original signature.

### Usage
![image](https://github.com/user-attachments/assets/3812c217-5407-436c-82f1-30782dbab2ec)



**Tiny testing mode**

This is one feature of Cargo and Gradle that I sometimes miss in C and C++. But I guess I can make my own instead.
Since I created unit tests for some of my smaller functions during the coding process, and I did not just want to delete them, I made a testing mode that can be called with `make test`. Additional tests can be added in `testing.cpp` and the corresponding header file.
