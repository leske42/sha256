/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:10:36 by mhuszar           #+#    #+#             */
/*   Updated: 2025/01/05 21:02:47 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <cstdint>
#include <endian.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sstream>
#include "testing.hpp"

uint32_t h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

uint32_t a = 0;
uint32_t b = 0;
uint32_t c = 0;
uint32_t d = 0;
uint32_t e = 0;
uint32_t f = 0;
uint32_t g = 0;
uint32_t _h = 0;

uint32_t k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

uint32_t w[64];
   

static inline  uint32_t __attribute__ ((always_inline)) rotate_right(uint32_t num, uint8_t val)
{
    __asm__ (
        "rorl %1, %%eax;"
      : "+a" (num)
      : "c" (val)
      :
    );
    return (num);
}

static inline uint32_t __attribute__ ((always_inline)) sigma0 (uint32_t word)
{
    return (rotate_right(word, 7) ^ rotate_right(word, 18) ^ (word >> 3));
}

static inline uint32_t __attribute__ ((always_inline)) sigma1 (uint32_t word)
{
    return (rotate_right(word, 17) ^ rotate_right(word, 19) ^ (word >> 10));
}

static inline uint32_t __attribute__ ((always_inline)) SIGMA0 (uint32_t word)
{
    return (rotate_right(word, 2) ^ rotate_right(word, 13) ^ rotate_right(word, 22));
}

static inline uint32_t __attribute__ ((always_inline)) SIGMA1 (uint32_t word)
{
    return (rotate_right(word, 6) ^ rotate_right(word, 11) ^ rotate_right(word, 25));
}

void add_chunks()
{
    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
    h[5] += f;
    h[6] += g;
    h[7] += _h;

    a = h[0];
    b = h[1];
    c = h[2];
    d = h[3];
    e = h[4];
    f = h[5];
    g = h[6];
    _h = h[7];
}

void create_padding(std::vector<unsigned char>& data)
{
    size_t L = data.size() << 3;
    size_t K = 512 - ((L + 1 + 64) & 511);
    size_t octets = (K + 1) >> 3;

    data.push_back(128);
    while (--octets)
        data.push_back(0);
    
    size_t *proxy_ptr = &L;
    unsigned char *ptr = (unsigned char *)proxy_ptr;
    for (int i = 7; i >= 0; i--)
    {
        data.push_back(*(ptr + i));
    }
}

void extend_w()
{
    for (int t = 16; t < 64; t++)
    {
        w[t] = w[t-16] + sigma0(w[t-15]) + w[t-7] + sigma1(w[t-2]);
    }
}

void compress()
{
    uint32_t ch, maj, temp1, temp2;

    for (int t = 0; t < 64; t++)
    {
        ch = (e & f) ^ (~e & g);
        temp1 = _h + SIGMA1(e) + ch + k[t] + w[t];
        maj = (a & b) ^ (a & c) ^ (b & c);
        temp2 = SIGMA0(a) + maj;

        _h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }
}

void process(std::vector<unsigned char>& data)
{
    size_t total = data.size();
    unsigned char *raw = data.data();
    uint32_t *raw_mod = (uint32_t *)raw;
    add_chunks();
    for (size_t size = 0; size < total; size += 512)
    {
        for (int i = 0; i < 16; i++)
        {
            w[i] = __bswap_constant_32(*raw_mod);
            raw_mod += 1;
        }
        extend_w();
        compress();
        add_chunks();
    }
}

std::string hexnum(uint32_t num)
{
    std::stringstream res;
    uint32_t part = (num >> 24) & 255;
    if (part < 16)
        res << "0";
    res << std::hex << part;

    part = (num >> 16) & 255;
    if (part < 16)
        res << "0";
    res << std::hex << part;

    part = (num >> 8) & 255;
    if (part < 16)
        res << "0";
    res << std::hex << part;

    part = num & 255;
    if (part < 16)
        res << "0";
    res << std::hex << part;

    return (res.str());
}

void display_hash()
{
    std::ostringstream output;
    for (int i = 0; i < 8; ++i)
    {
        output << hexnum(h[i]);
    }
    std::cout << output.str() << std::endl;
}

#ifndef TEST_MODE
int main(int argc, char **argv)
{
    if (argc != 2)
        return 0;
    std::string input = argv[1];
    std::vector<unsigned char> data(input.begin(), input.end());
    
    create_padding(data);
    process(data);
    display_hash();
}
#else
int main(void)
{
    assert_eq(rotate_right(42, 2), 2147483658);
    assert_eq(hexnum(42), "0000002a");
    display_result();
}
#endif