// Computer Specification: 11th Gen Intel® Core™ i7-1165G7, 16 GB RAM
// Done in 360ms (0.36s)

#include <iostream>
#include <chrono>
#include <bitset>

using namespace std::chrono;
constexpr uint64_t N = 100*1000*1000;

typedef size_t bits_array;
typedef enum
{
    NOT_INITIALIZED,
    INITIALIZED
} mirrored_lut_status_ty;

uint8_t LUT[256] = {0};

bits_array BitArrayMirror(bits_array bitarr);

mirrored_lut_status_ty mirrored_lut_status = NOT_INITIALIZED;

void InitMirroredLUT()
{
    size_t integer_value = 0;

    for (integer_value = 0; integer_value < 256; ++integer_value)
    {
        LUT[integer_value] = BitArrayMirror(integer_value);
    }
}

bits_array BitArrayMirror(bits_array bitarr)
{
    size_t curr_bit_index = 0;
    bits_array mirrored_bitarr = 0;

    for (curr_bit_index = 0; curr_bit_index < 8; ++curr_bit_index)
    {
        if((bitarr & (1UL << curr_bit_index)))
        {
            mirrored_bitarr |= 1UL << ((8 - 1) - curr_bit_index);
        }
    }
    return(mirrored_bitarr);
}

bits_array BitArrayMirrorLUT(bits_array bitarr)
{
    bits_array mirrored_bitarr = 0;

    if (NOT_INITIALIZED == mirrored_lut_status)
    {
        InitMirroredLUT();
        mirrored_lut_status = INITIALIZED;
    }
    mirrored_bitarr = (bits_array)LUT[bitarr & 0xff] << 56 |
                      (bits_array)LUT[(bitarr >> 8) & 0xff] << 48 |
                      (bits_array)LUT[(bitarr >> 16) & 0xff] << 40 |
                      (bits_array)LUT[(bitarr >> 24) & 0xff] << 32 |
                      (bits_array)LUT[(bitarr >> 32) & 0xff] << 24 |
                      (bits_array)LUT[(bitarr >> 40) & 0xff] << 16 |
                      (bits_array)LUT[(bitarr >> 48) & 0xff] << 8 |
                      (bits_array)LUT[(bitarr >> 56) & 0xff];

    return (mirrored_bitarr);
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    for(bits_array i = 0; i < N; i++){

        bits_array reverse_number;
        reverse_number = BitArrayMirrorLUT(i);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Done in " << duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms" << std::endl;
    return 0;
}
