#include "imgui.h"
#include "imgui_impl_dx11.h"

#include <stdio.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "../encryption.hpp"
#include "../memory.hpp"

#define encrypt_or_decrypt(data) for (int i = 0; i < sizeof(data); i++) { data[i] ^= ('A' - 'Z'); }

unsigned char pixelShaderBuffer[660] = 
{
    0xA3, 0xBF, 0xA5, 0xA4, 0x79, 0x29, 0x62, 0x95, 0x40, 0x70, 0xB5, 0x53,
    0x8A, 0x23, 0xCF, 0x1D, 0xF7, 0x27, 0x35, 0x26, 0xE6, 0xE7, 0xE7, 0xE7,
    0x73, 0xE5, 0xE7, 0xE7, 0xE2, 0xE7, 0xE7, 0xE7, 0xD3, 0xE7, 0xE7, 0xE7,
    0x33, 0xE7, 0xE7, 0xE7, 0xAF, 0xE6, 0xE7, 0xE7, 0x9B, 0xE6, 0xE7, 0xE7,
    0xFF, 0xE5, 0xE7, 0xE7, 0xB5, 0xA3, 0xA2, 0xA1, 0x7F, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE5, 0xE7, 0xE7, 0xE7,
    0xFB, 0xE7, 0xE7, 0xE7, 0xE7, 0xE3, 0x18, 0x18, 0xE7, 0xE6, 0xE7, 0xE7,
    0x89, 0xE7, 0xE7, 0xE7, 0xBB, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0x82, 0xE7, 0xE7, 0xE7, 0xE5, 0xE7, 0xE7, 0xE7, 0xE2, 0xE7, 0xE7, 0xE7,
    0xE3, 0xE7, 0xE7, 0xE7, 0x18, 0x18, 0x18, 0x18, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE6, 0xE7, 0xE7, 0xE7, 0xEB, 0xE7, 0xE7, 0xE7, 0x94, 0x86, 0x8A, 0x97,
    0x8B, 0x82, 0x95, 0xD7, 0xE7, 0x93, 0x82, 0x9F, 0x93, 0x92, 0x95, 0x82,
    0xD7, 0xE7, 0xAA, 0x8E, 0x84, 0x95, 0x88, 0x94, 0x88, 0x81, 0x93, 0xC7,
    0xCF, 0xB5, 0xCE, 0xC7, 0xAF, 0xAB, 0xB4, 0xAB, 0xC7, 0xB4, 0x8F, 0x86,
    0x83, 0x82, 0x95, 0xC7, 0xA4, 0x88, 0x8A, 0x97, 0x8E, 0x8B, 0x82, 0x95,
    0xC7, 0xD6, 0xD7, 0xC9, 0xD6, 0xE7, 0x4C, 0x4C, 0xAE, 0xB4, 0xA0, 0xA9,
    0x8B, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7, 0xEF, 0xE7, 0xE7, 0xE7,
    0xB7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0xE4, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE8, 0xE7, 0xE7, 0xE7,
    0xBB, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE4, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7, 0xE8, 0xE8, 0xE7, 0xE7,
    0x85, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE4, 0xE7, 0xE7, 0xE7, 0xE5, 0xE7, 0xE7, 0xE7, 0xE4, 0xE4, 0xE7, 0xE7,
    0xB4, 0xB1, 0xB8, 0xB7, 0xA8, 0xB4, 0xAE, 0xB3, 0xAE, 0xA8, 0xA9, 0xE7,
    0xA4, 0xA8, 0xAB, 0xA8, 0xB5, 0xE7, 0xB3, 0xA2, 0xBF, 0xA4, 0xA8, 0xA8,
    0xB5, 0xA3, 0xE7, 0x4C, 0xA8, 0xB4, 0xA0, 0xA9, 0xCB, 0xE7, 0xE7, 0xE7,
    0xE6, 0xE7, 0xE7, 0xE7, 0xEF, 0xE7, 0xE7, 0xE7, 0xC7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE8, 0xE7, 0xE7, 0xE7, 0xB4, 0xB1, 0xB8, 0xB3,
    0x86, 0x95, 0x80, 0x82, 0x93, 0xE7, 0x4C, 0x4C, 0xB4, 0xAF, 0xA3, 0xB5,
    0x73, 0xE7, 0xE7, 0xE7, 0xA7, 0xE7, 0xE7, 0xE7, 0xC2, 0xE7, 0xE7, 0xE7,
    0xBD, 0xE7, 0xE7, 0xE4, 0xE7, 0x87, 0xF7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xBF, 0xFF, 0xE7, 0xE3, 0xE7, 0x97, 0xF7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xB2, 0xB2, 0xE7, 0xE7, 0x85, 0xF7, 0xE7, 0xE4, 0x15, 0xF7, 0xF7, 0xE7,
    0xE6, 0xE7, 0xE7, 0xE7, 0x85, 0xF7, 0xE7, 0xE4, 0xD5, 0xF7, 0xF7, 0xE7,
    0xE5, 0xE7, 0xE7, 0xE7, 0x82, 0xE7, 0xE7, 0xE4, 0x15, 0xC7, 0xF7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0x8F, 0xE7, 0xE7, 0xE5, 0xE6, 0xE7, 0xE7, 0xE7,
    0xA2, 0xE7, 0xE7, 0xEE, 0x15, 0xE7, 0xF7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xA1, 0xF7, 0xF7, 0xE7, 0xE5, 0xE7, 0xE7, 0xE7, 0xA1, 0x99, 0xF7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0x87, 0xF7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xDF, 0xE7, 0xE7, 0xE0, 0x15, 0xC7, 0xF7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xA1, 0xE9, 0xF7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xA1, 0xF9, 0xF7, 0xE7,
    0xE6, 0xE7, 0xE7, 0xE7, 0xD9, 0xE7, 0xE7, 0xE6, 0xB4, 0xB3, 0xA6, 0xB3,
    0x93, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE6, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7
};
unsigned char vertexBuffer[876] = 
{
           0xA3, 0xBF, 0xA5, 0xA4, 0x9D, 0xB3, 0x63, 0x71, 0x38, 0x36, 0x79, 0xC6,
    0x1A, 0x62, 0x61, 0xDA, 0xCF, 0x36, 0xE4, 0x49, 0xE6, 0xE7, 0xE7, 0xE7,
    0x8B, 0xE4, 0xE7, 0xE7, 0xE2, 0xE7, 0xE7, 0xE7, 0xD3, 0xE7, 0xE7, 0xE7,
    0xE3, 0xE6, 0xE7, 0xE7, 0x93, 0xE6, 0xE7, 0xE7, 0x0F, 0xE6, 0xE7, 0xE7,
    0x17, 0xE5, 0xE7, 0xE7, 0xB5, 0xA3, 0xA2, 0xA1, 0x2F, 0xE7, 0xE7, 0xE7,
    0xE6, 0xE7, 0xE7, 0xE7, 0xAB, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0xFB, 0xE7, 0xE7, 0xE7, 0xE7, 0xE3, 0x19, 0x18, 0xE7, 0xE6, 0xE7, 0xE7,
    0x47, 0xE7, 0xE7, 0xE7, 0xDB, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0x91, 0x82, 0x95, 0x93, 0x82, 0x9F, 0xA5, 0x92, 0x81, 0x81, 0x82, 0x95,
    0xE7, 0x4C, 0x4C, 0x4C, 0xDB, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0x83, 0xE7, 0xE7, 0xE7, 0xA7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0x9B, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xA7, 0xE7, 0xE7, 0xE7, 0xE5, 0xE7, 0xE7, 0xE7, 0x77, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xB7, 0x95, 0x88, 0x8D, 0x82, 0x84, 0x93, 0x8E,
    0x88, 0x89, 0xAA, 0x86, 0x93, 0x95, 0x8E, 0x9F, 0xE7, 0x4C, 0x4C, 0x4C,
    0xE4, 0xE7, 0xE4, 0xE7, 0xE3, 0xE7, 0xE3, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xAA, 0x8E, 0x84, 0x95, 0x88, 0x94, 0x88, 0x81,
    0x93, 0xC7, 0xCF, 0xB5, 0xCE, 0xC7, 0xAF, 0xAB, 0xB4, 0xAB, 0xC7, 0xB4,
    0x8F, 0x86, 0x83, 0x82, 0x95, 0xC7, 0xA4, 0x88, 0x8A, 0x97, 0x8E, 0x8B,
    0x82, 0x95, 0xC7, 0xD6, 0xD7, 0xC9, 0xD6, 0xE7, 0xAE, 0xB4, 0xA0, 0xA9,
    0x8F, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7, 0xEF, 0xE7, 0xE7, 0xE7,
    0xB7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE4, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE4, 0xE4, 0xE7, 0xE7,
    0xBE, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE4, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7, 0xE8, 0xE8, 0xE7, 0xE7,
    0xB8, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE4, 0xE7, 0xE7, 0xE7, 0xE5, 0xE7, 0xE7, 0xE7, 0xE4, 0xE4, 0xE7, 0xE7,
    0xB7, 0xA8, 0xB4, 0xAE, 0xB3, 0xAE, 0xA8, 0xA9, 0xE7, 0xA4, 0xA8, 0xAB,
    0xA8, 0xB5, 0xE7, 0xB3, 0xA2, 0xBF, 0xA4, 0xA8, 0xA8, 0xB5, 0xA3, 0xE7,
    0xA8, 0xB4, 0xA0, 0xA9, 0x8B, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7,
    0xEF, 0xE7, 0xE7, 0xE7, 0xB7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE6, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE8, 0xE7, 0xE7, 0xE7, 0xBB, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0xE8, 0xE7, 0xE7, 0xE7, 0x85, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7, 0xE5, 0xE7, 0xE7, 0xE7,
    0xE4, 0xEB, 0xE7, 0xE7, 0xB4, 0xB1, 0xB8, 0xB7, 0xA8, 0xB4, 0xAE, 0xB3,
    0xAE, 0xA8, 0xA9, 0xE7, 0xA4, 0xA8, 0xAB, 0xA8, 0xB5, 0xE7, 0xB3, 0xA2,
    0xBF, 0xA4, 0xA8, 0xA8, 0xB5, 0xA3, 0xE7, 0x4C, 0xB4, 0xAF, 0xA3, 0xB5,
    0xE7, 0xE6, 0xE7, 0xE7, 0xA7, 0xE7, 0xE6, 0xE7, 0xA7, 0xE7, 0xE7, 0xE7,
    0xBE, 0xE7, 0xE7, 0xE3, 0xA1, 0x69, 0xC7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE3, 0xE7, 0xE7, 0xE7, 0xB8, 0xE7, 0xE7, 0xE4, 0xD5, 0xF7, 0xF7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xB8, 0xE7, 0xE7, 0xE4, 0x15, 0xF7, 0xF7, 0xE7,
    0xE6, 0xE7, 0xE7, 0xE7, 0xB8, 0xE7, 0xE7, 0xE4, 0xD5, 0xF7, 0xF7, 0xE7,
    0xE5, 0xE7, 0xE7, 0xE7, 0x80, 0xE7, 0xE7, 0xE3, 0x15, 0xC7, 0xF7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7, 0x82, 0xE7, 0xE7, 0xE4,
    0x15, 0xC7, 0xF7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7, 0x82, 0xE7, 0xE7, 0xE4,
    0xD5, 0xC7, 0xF7, 0xE7, 0xE5, 0xE7, 0xE7, 0xE7, 0x8F, 0xE7, 0xE7, 0xE5,
    0xE6, 0xE7, 0xE7, 0xE7, 0xDF, 0xE7, 0xE7, 0xEF, 0x15, 0xE7, 0xF7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xB1, 0xF2, 0xF7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xA1, 0x69, 0xC7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0xD5, 0xE7, 0xE7, 0xED, 0x15, 0xE7, 0xF7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xA1, 0x69, 0xC7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE1, 0xF7, 0xF7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xA1, 0xE9, 0xF7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xEF, 0x15, 0xC7, 0xF7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xA1, 0xE9, 0xF7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xA1, 0x69, 0xC7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7,
    0xD1, 0xE7, 0xE7, 0xE2, 0x15, 0xC7, 0xF7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0xA1, 0xF9, 0xF7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7, 0xD1, 0xE7, 0xE7, 0xE2,
    0xD5, 0xC7, 0xF7, 0xE7, 0xE5, 0xE7, 0xE7, 0xE7, 0xA1, 0xF7, 0xF7, 0xE7,
    0xE5, 0xE7, 0xE7, 0xE7, 0xD9, 0xE7, 0xE7, 0xE6, 0xB4, 0xB3, 0xA6, 0xB3,
    0x93, 0xE7, 0xE7, 0xE7, 0xE1, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE1, 0xE7, 0xE7, 0xE7, 0xE4, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE6, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE5, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7
};

struct ImGui_ImplDX11_Data
{
    ID3D11Device* pd3dDevice;
    ID3D11DeviceContext* pd3dDeviceContext;
    IDXGIFactory* pFactory;
    ID3D11Buffer* pVB;
    ID3D11Buffer* pIB;
    ID3D11VertexShader* pVertexShader;
    ID3D11InputLayout* pInputLayout;
    ID3D11Buffer* pVertexConstantBuffer;
    ID3D11PixelShader* pPixelShader;
    ID3D11SamplerState* pFontSampler;
    ID3D11ShaderResourceView* pFontTextureView;
    ID3D11RasterizerState* pRasterizerState;
    ID3D11BlendState* pBlendState;
    ID3D11DepthStencilState* pDepthStencilState;
    int                         VertexBufferSize;
    int                         IndexBufferSize;

    ImGui_ImplDX11_Data() { base::memory::_memset(this, 0, sizeof(*this)); VertexBufferSize = 5000; IndexBufferSize = 10000; }
};

struct VERTEX_CONSTANT_BUFFER
{
    float   mvp[4][4];
};

// Backend data stored in io.BackendRendererUserData to allow support for multiple Dear ImGui contexts
// It is STRONGLY preferred that you use docking branch with multi-viewports (== single Dear ImGui context + multiple windows) instead of multiple Dear ImGui contexts.
static ImGui_ImplDX11_Data* ImGui_ImplDX11_GetBackendData()
{
    return ImGui::GetCurrentContext() ? (ImGui_ImplDX11_Data*)ImGui::GetIO().BackendRendererUserData : NULL;
}

// Functions
static void ImGui_ImplDX11_SetupRenderState(ImDrawData* draw_data, ID3D11DeviceContext* ctx)
{
    ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();

    // Setup viewport
    D3D11_VIEWPORT vp;
    base::memory::_memset(&vp, 0, sizeof(D3D11_VIEWPORT));
    vp.Width = draw_data->DisplaySize.x;
    vp.Height = draw_data->DisplaySize.y;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = vp.TopLeftY = 0;
    ctx->RSSetViewports(1, &vp);

    // Setup shader and vertex buffers
    unsigned int stride = sizeof(ImDrawVert);
    unsigned int offset = 0;
    ctx->IASetInputLayout(bd->pInputLayout);
    ctx->IASetVertexBuffers(0, 1, &bd->pVB, &stride, &offset);
    ctx->IASetIndexBuffer(bd->pIB, sizeof(ImDrawIdx) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ctx->VSSetShader(bd->pVertexShader, NULL, 0);
    ctx->VSSetConstantBuffers(0, 1, &bd->pVertexConstantBuffer);
    ctx->PSSetShader(bd->pPixelShader, NULL, 0);
    ctx->PSSetSamplers(0, 1, &bd->pFontSampler);
    ctx->GSSetShader(NULL, NULL, 0);
    ctx->HSSetShader(NULL, NULL, 0); // In theory we should backup and restore this as well.. very infrequently used..
    ctx->DSSetShader(NULL, NULL, 0); // In theory we should backup and restore this as well.. very infrequently used..
    ctx->CSSetShader(NULL, NULL, 0); // In theory we should backup and restore this as well.. very infrequently used..

    // Setup blend state
    const float blend_factor[4] = { 0.f, 0.f, 0.f, 0.f };
    ctx->OMSetBlendState(bd->pBlendState, blend_factor, 0xffffffff);
    ctx->OMSetDepthStencilState(bd->pDepthStencilState, 0);
    ctx->RSSetState(bd->pRasterizerState);
}

// Render function
void ImGui_ImplDX11_RenderDrawData(ImDrawData* draw_data)
{
    // Avoid rendering when minimized
    if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f)
        return;

    ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
    ID3D11DeviceContext* ctx = bd->pd3dDeviceContext;

    // Create and grow vertex/index buffers if needed
    if (!bd->pVB || bd->VertexBufferSize < draw_data->TotalVtxCount)
    {
        if (bd->pVB) { bd->pVB->Release(); bd->pVB = NULL; }
        bd->VertexBufferSize = draw_data->TotalVtxCount + 5000;
        D3D11_BUFFER_DESC desc;
        base::memory::_memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.ByteWidth = bd->VertexBufferSize * sizeof(ImDrawVert);
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        if (bd->pd3dDevice->CreateBuffer(&desc, NULL, &bd->pVB) < 0)
            return;
    }
    if (!bd->pIB || bd->IndexBufferSize < draw_data->TotalIdxCount)
    {
        if (bd->pIB) { bd->pIB->Release(); bd->pIB = NULL; }
        bd->IndexBufferSize = draw_data->TotalIdxCount + 10000;
        D3D11_BUFFER_DESC desc;
        base::memory::_memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.ByteWidth = bd->IndexBufferSize * sizeof(ImDrawIdx);
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        if (bd->pd3dDevice->CreateBuffer(&desc, NULL, &bd->pIB) < 0)
            return;
    }

    // Upload vertex/index data into a single contiguous GPU buffer
    D3D11_MAPPED_SUBRESOURCE vtx_resource, idx_resource;
    if (ctx->Map(bd->pVB, 0, D3D11_MAP_WRITE_DISCARD, 0, &vtx_resource) != S_OK)
        return;
    if (ctx->Map(bd->pIB, 0, D3D11_MAP_WRITE_DISCARD, 0, &idx_resource) != S_OK)
        return;
    ImDrawVert* vtx_dst = (ImDrawVert*)vtx_resource.pData;
    ImDrawIdx* idx_dst = (ImDrawIdx*)idx_resource.pData;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        base::memory::_memcpy(vtx_dst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
        base::memory::_memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
        vtx_dst += cmd_list->VtxBuffer.Size;
        idx_dst += cmd_list->IdxBuffer.Size;
    }
    ctx->Unmap(bd->pVB, 0);
    ctx->Unmap(bd->pIB, 0);

    // Setup orthographic projection matrix into our constant buffer
    // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
    {
        D3D11_MAPPED_SUBRESOURCE mapped_resource;
        if (ctx->Map(bd->pVertexConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource) != S_OK)
            return;
        VERTEX_CONSTANT_BUFFER* constant_buffer = (VERTEX_CONSTANT_BUFFER*)mapped_resource.pData;
        float L = draw_data->DisplayPos.x;
        float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
        float T = draw_data->DisplayPos.y;
        float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
        float mvp[4][4] =
        {
            { 2.0f / (R - L),   0.0f,           0.0f,       0.0f },
            { 0.0f,         2.0f / (T - B),     0.0f,       0.0f },
            { 0.0f,         0.0f,           0.5f,       0.0f },
            { (R + L) / (L - R),  (T + B) / (B - T),    0.5f,       1.0f },
        };
        base::memory::_memcpy(&constant_buffer->mvp, mvp, sizeof(mvp));
        ctx->Unmap(bd->pVertexConstantBuffer, 0);
    }

    // Backup DX state that will be modified to restore it afterwards (unfortunately this is very ugly looking and verbose. Close your eyes!)
    struct BACKUP_DX11_STATE
    {
        UINT                        ScissorRectsCount, ViewportsCount;
        D3D11_RECT                  ScissorRects[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
        D3D11_VIEWPORT              Viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
        ID3D11RasterizerState* RS;
        ID3D11BlendState* BlendState;
        FLOAT                       BlendFactor[4];
        UINT                        SampleMask;
        UINT                        StencilRef;
        ID3D11DepthStencilState* DepthStencilState;
        ID3D11ShaderResourceView* PSShaderResource;
        ID3D11SamplerState* PSSampler;
        ID3D11PixelShader* PS;
        ID3D11VertexShader* VS;
        ID3D11GeometryShader* GS;
        UINT                        PSInstancesCount, VSInstancesCount, GSInstancesCount;
        ID3D11ClassInstance* PSInstances[256], * VSInstances[256], * GSInstances[256];   // 256 is max according to PSSetShader documentation
        D3D11_PRIMITIVE_TOPOLOGY    PrimitiveTopology;
        ID3D11Buffer* IndexBuffer, * VertexBuffer, * VSConstantBuffer;
        UINT                        IndexBufferOffset, VertexBufferStride, VertexBufferOffset;
        DXGI_FORMAT                 IndexBufferFormat;
        ID3D11InputLayout* InputLayout;
    };
    BACKUP_DX11_STATE old = {};
    old.ScissorRectsCount = old.ViewportsCount = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
    ctx->RSGetScissorRects(&old.ScissorRectsCount, old.ScissorRects);
    ctx->RSGetViewports(&old.ViewportsCount, old.Viewports);
    ctx->RSGetState(&old.RS);
    ctx->OMGetBlendState(&old.BlendState, old.BlendFactor, &old.SampleMask);
    ctx->OMGetDepthStencilState(&old.DepthStencilState, &old.StencilRef);
    ctx->PSGetShaderResources(0, 1, &old.PSShaderResource);
    ctx->PSGetSamplers(0, 1, &old.PSSampler);
    old.PSInstancesCount = old.VSInstancesCount = old.GSInstancesCount = 256;
    ctx->PSGetShader(&old.PS, old.PSInstances, &old.PSInstancesCount);
    ctx->VSGetShader(&old.VS, old.VSInstances, &old.VSInstancesCount);
    ctx->VSGetConstantBuffers(0, 1, &old.VSConstantBuffer);
    ctx->GSGetShader(&old.GS, old.GSInstances, &old.GSInstancesCount);

    ctx->IAGetPrimitiveTopology(&old.PrimitiveTopology);
    ctx->IAGetIndexBuffer(&old.IndexBuffer, &old.IndexBufferFormat, &old.IndexBufferOffset);
    ctx->IAGetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset);
    ctx->IAGetInputLayout(&old.InputLayout);

    // Setup desired DX state
    ImGui_ImplDX11_SetupRenderState(draw_data, ctx);

    // Render command lists
    // (Because we merged all buffers into a single one, we maintain our own offset into them)
    int global_idx_offset = 0;
    int global_vtx_offset = 0;
    ImVec2 clip_off = draw_data->DisplayPos;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback != NULL)
            {
                // User callback, registered via ImDrawList::AddCallback()
                // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                    ImGui_ImplDX11_SetupRenderState(draw_data, ctx);
                else
                    pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                // Project scissor/clipping rectangles into framebuffer space
                ImVec2 clip_min(pcmd->ClipRect.x - clip_off.x, pcmd->ClipRect.y - clip_off.y);
                ImVec2 clip_max(pcmd->ClipRect.z - clip_off.x, pcmd->ClipRect.w - clip_off.y);
                if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y)
                    continue;

                // Apply scissor/clipping rectangle
                const D3D11_RECT r = { (LONG)clip_min.x, (LONG)clip_min.y, (LONG)clip_max.x, (LONG)clip_max.y };
                ctx->RSSetScissorRects(1, &r);

                // Bind texture, Draw
                ID3D11ShaderResourceView* texture_srv = (ID3D11ShaderResourceView*)pcmd->GetTexID();
                ctx->PSSetShaderResources(0, 1, &texture_srv);
                ctx->DrawIndexed(pcmd->ElemCount, pcmd->IdxOffset + global_idx_offset, pcmd->VtxOffset + global_vtx_offset);
            }
        }
        global_idx_offset += cmd_list->IdxBuffer.Size;
        global_vtx_offset += cmd_list->VtxBuffer.Size;
    }

    // Restore modified DX state
    ctx->RSSetScissorRects(old.ScissorRectsCount, old.ScissorRects);
    ctx->RSSetViewports(old.ViewportsCount, old.Viewports);
    ctx->RSSetState(old.RS); if (old.RS) old.RS->Release();
    ctx->OMSetBlendState(old.BlendState, old.BlendFactor, old.SampleMask); if (old.BlendState) old.BlendState->Release();
    ctx->OMSetDepthStencilState(old.DepthStencilState, old.StencilRef); if (old.DepthStencilState) old.DepthStencilState->Release();
    ctx->PSSetShaderResources(0, 1, &old.PSShaderResource); if (old.PSShaderResource) old.PSShaderResource->Release();
    ctx->PSSetSamplers(0, 1, &old.PSSampler); if (old.PSSampler) old.PSSampler->Release();
    ctx->PSSetShader(old.PS, old.PSInstances, old.PSInstancesCount); if (old.PS) old.PS->Release();
    for (UINT i = 0; i < old.PSInstancesCount; i++) if (old.PSInstances[i]) old.PSInstances[i]->Release();
    ctx->VSSetShader(old.VS, old.VSInstances, old.VSInstancesCount); if (old.VS) old.VS->Release();
    ctx->VSSetConstantBuffers(0, 1, &old.VSConstantBuffer); if (old.VSConstantBuffer) old.VSConstantBuffer->Release();
    ctx->GSSetShader(old.GS, old.GSInstances, old.GSInstancesCount); if (old.GS) old.GS->Release();
    for (UINT i = 0; i < old.VSInstancesCount; i++) if (old.VSInstances[i]) old.VSInstances[i]->Release();
    ctx->IASetPrimitiveTopology(old.PrimitiveTopology);
    ctx->IASetIndexBuffer(old.IndexBuffer, old.IndexBufferFormat, old.IndexBufferOffset); if (old.IndexBuffer) old.IndexBuffer->Release();
    ctx->IASetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset); if (old.VertexBuffer) old.VertexBuffer->Release();
    ctx->IASetInputLayout(old.InputLayout); if (old.InputLayout) old.InputLayout->Release();
}

static void ImGui_ImplDX11_CreateFontsTexture()
{
    // Build texture atlas
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    // Upload texture to graphics system
    {
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;

        ID3D11Texture2D* pTexture = NULL;
        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = pixels;
        subResource.SysMemPitch = desc.Width * 4;
        subResource.SysMemSlicePitch = 0;
        bd->pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);
        IM_ASSERT(pTexture != NULL);

        // Create texture view
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        base::memory::_memset(&srvDesc, 0, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        bd->pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &bd->pFontTextureView);
        pTexture->Release();
    }

    // Store our identifier
    io.Fonts->SetTexID((ImTextureID)bd->pFontTextureView);

    // Create texture sampler
    {
        D3D11_SAMPLER_DESC desc;
        base::memory::_memset(&desc, 0, sizeof(desc));
        desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.MipLODBias = 0.f;
        desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        desc.MinLOD = 0.f;
        desc.MaxLOD = 0.f;
        bd->pd3dDevice->CreateSamplerState(&desc, &bd->pFontSampler);
    }
}

bool    ImGui_ImplDX11_CreateDeviceObjects()
{
    ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
    if (!bd->pd3dDevice)
        return false;
    if (bd->pFontSampler)
        ImGui_ImplDX11_InvalidateDeviceObjects();

    // By using D3DCompile() from <d3dcompiler.h> / d3dcompiler.lib, we introduce a dependency to a given version of d3dcompiler_XX.dll (see D3DCOMPILER_DLL_A)
    // If you would like to use this DX11 sample code but remove this dependency you can:
    //  1) compile once, save the compiled shader blobs into a file or source code and pass them to CreateVertexShader()/CreatePixelShader() [preferred solution]
    //  2) use code to detect any version of the DLL and grab a pointer to D3DCompile from the DLL.
    // See https://github.com/ocornut/imgui/pull/638 for sources and details.

    // Create the vertex shader
    {
        
        // Create the input layout
        D3D11_INPUT_ELEMENT_DESC local_layout[] =
        {
            { xorstr_("POSITION"), 0, DXGI_FORMAT_R32G32_FLOAT,   0, (UINT)IM_OFFSETOF(ImDrawVert, pos), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { xorstr_("TEXCOORD"), 0, DXGI_FORMAT_R32G32_FLOAT,   0, (UINT)IM_OFFSETOF(ImDrawVert, uv),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { xorstr_("COLOR"),    0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, (UINT)IM_OFFSETOF(ImDrawVert, col), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };

        encrypt_or_decrypt(vertexBuffer); // decrypt vertexBuffer so we can actually use it
        if (bd->pd3dDevice->CreateVertexShader(vertexBuffer, sizeof(vertexBuffer), NULL, &bd->pVertexShader) != S_OK)
            return false;

        if (bd->pd3dDevice->CreateInputLayout(local_layout, 3, vertexBuffer, sizeof(vertexBuffer), &bd->pInputLayout) != S_OK)
            return false;
        base::memory::_memset(&vertexBuffer, 0, sizeof(vertexBuffer));

        // Create the constant buffer
        {
            D3D11_BUFFER_DESC desc;
            desc.ByteWidth = sizeof(VERTEX_CONSTANT_BUFFER);
            desc.Usage = D3D11_USAGE_DYNAMIC;
            desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            desc.MiscFlags = 0;
            bd->pd3dDevice->CreateBuffer(&desc, NULL, &bd->pVertexConstantBuffer);
        }
    }

    // Create the pixel shader
    {
        encrypt_or_decrypt(pixelShaderBuffer); // decrypt shader
        if (bd->pd3dDevice->CreatePixelShader(pixelShaderBuffer, sizeof(pixelShaderBuffer), NULL, &bd->pPixelShader) != S_OK)
            return false;
        base::memory::_memset(&pixelShaderBuffer, 0, sizeof(pixelShaderBuffer));
    }

    // Create the blending setup
    {
        D3D11_BLEND_DESC desc;
        base::memory::_memset(&desc, 0, sizeof(desc));
        desc.AlphaToCoverageEnable = false;
        desc.RenderTarget[0].BlendEnable = true;
        desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
        desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        bd->pd3dDevice->CreateBlendState(&desc, &bd->pBlendState);
    }

    // Create the rasterizer state
    {
        D3D11_RASTERIZER_DESC desc;
        base::memory::_memset(&desc, 0, sizeof(desc));
        desc.FillMode = D3D11_FILL_SOLID;
        desc.CullMode = D3D11_CULL_NONE;
        desc.ScissorEnable = true;
        desc.DepthClipEnable = true;
        bd->pd3dDevice->CreateRasterizerState(&desc, &bd->pRasterizerState);
    }

    // Create depth-stencil State
    {
        D3D11_DEPTH_STENCIL_DESC desc;
        base::memory::_memset(&desc, 0, sizeof(desc));
        desc.DepthEnable = false;
        desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
        desc.StencilEnable = false;
        desc.FrontFace.StencilFailOp = desc.FrontFace.StencilDepthFailOp = desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        desc.BackFace = desc.FrontFace;
        bd->pd3dDevice->CreateDepthStencilState(&desc, &bd->pDepthStencilState);
    }

    ImGui_ImplDX11_CreateFontsTexture();

    return true;
}

void    ImGui_ImplDX11_InvalidateDeviceObjects()
{
    ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
    if (!bd->pd3dDevice)
        return;

    if (bd->pFontSampler) { bd->pFontSampler->Release(); bd->pFontSampler = NULL; }
    if (bd->pFontTextureView) { bd->pFontTextureView->Release(); bd->pFontTextureView = NULL; ImGui::GetIO().Fonts->SetTexID(NULL); } // We copied data->pFontTextureView to io.Fonts->TexID so let's clear that as well.
    if (bd->pIB) { bd->pIB->Release(); bd->pIB = NULL; }
    if (bd->pVB) { bd->pVB->Release(); bd->pVB = NULL; }
    if (bd->pBlendState) { bd->pBlendState->Release(); bd->pBlendState = NULL; }
    if (bd->pDepthStencilState) { bd->pDepthStencilState->Release(); bd->pDepthStencilState = NULL; }
    if (bd->pRasterizerState) { bd->pRasterizerState->Release(); bd->pRasterizerState = NULL; }
    if (bd->pPixelShader) { bd->pPixelShader->Release(); bd->pPixelShader = NULL; }
    if (bd->pVertexConstantBuffer) { bd->pVertexConstantBuffer->Release(); bd->pVertexConstantBuffer = NULL; }
    if (bd->pInputLayout) { bd->pInputLayout->Release(); bd->pInputLayout = NULL; }
    if (bd->pVertexShader) { bd->pVertexShader->Release(); bd->pVertexShader = NULL; }
}

bool    ImGui_ImplDX11_Init(ID3D11Device* device, ID3D11DeviceContext* device_context)
{
    ImGuiIO& io = ImGui::GetIO();

    // Setup backend capabilities flags
    ImGui_ImplDX11_Data* bd = IM_NEW(ImGui_ImplDX11_Data)();
    io.BackendRendererUserData = (void*)bd;
    io.BackendRendererName = xorstr_("JSHGhgfhJDSGS#A$YSGT#SEFD");
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.

    // Get factory from device
    IDXGIDevice* pDXGIDevice = NULL;
    IDXGIAdapter* pDXGIAdapter = NULL;
    IDXGIFactory* pFactory = NULL;

    if (device->QueryInterface(IID_PPV_ARGS(&pDXGIDevice)) == S_OK)
        if (pDXGIDevice->GetParent(IID_PPV_ARGS(&pDXGIAdapter)) == S_OK)
            if (pDXGIAdapter->GetParent(IID_PPV_ARGS(&pFactory)) == S_OK)
            {
                bd->pd3dDevice = device;
                bd->pd3dDeviceContext = device_context;
                bd->pFactory = pFactory;
            }
    if (pDXGIDevice) pDXGIDevice->Release();
    if (pDXGIAdapter) pDXGIAdapter->Release();
    bd->pd3dDevice->AddRef();
    bd->pd3dDeviceContext->AddRef();

    return true;
}

void ImGui_ImplDX11_Shutdown()
{
    ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
    //IM_ASSERT( bd != NULL && _("No renderer backend to shutdown, or already shutdown?") );
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplDX11_InvalidateDeviceObjects();
    if (bd->pFactory) { bd->pFactory->Release(); }
    if (bd->pd3dDevice) { bd->pd3dDevice->Release(); }
    if (bd->pd3dDeviceContext) { bd->pd3dDeviceContext->Release(); }
    io.BackendRendererName = NULL;
    io.BackendRendererUserData = NULL;
    IM_DELETE(bd);
}

void ImGui_ImplDX11_NewFrame()
{
    ImGui_ImplDX11_Data* bd = ImGui_ImplDX11_GetBackendData();
    if (!bd->pFontSampler)
        ImGui_ImplDX11_CreateDeviceObjects();
}