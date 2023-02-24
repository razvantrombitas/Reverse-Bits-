// Computer Specification: 11th Gen Intel® Core™ i7-1165G7, 16 GB RAM
// Done in 220ms
// 64bit reverse - Algorithm:
/*      uint64_t mask;
        mask = 0b1111111111111111111111111111111100000000000000000000000000000000;
        b = (b & mask) >> 32 | (b & ~mask) << 32;
        mask = 0b1111111111111111000000000000000011111111111111110000000000000000;
        b = (b & mask) >> 16 | (b & ~mask) << 16;
        mask = 0b1111111100000000111111110000000011111111000000001111111100000000;
        b = (b & mask) >> 8 | (b & ~mask) << 8;
        mask = 0b1111000011110000111100001111000011110000111100001111000011110000;
        b = (b & mask) >> 4 | (b & ~mask) << 4;
        mask = 0b1100110011001100110011001100110011001100110011001100110011001100;
        b = (b & mask) >> 2 | (b & ~mask) << 2;
        mask = 0b1010101010101010101010101010101010101010101010101010101010101010;
        b = (b & mask) >> 1 | (b & ~mask) << 1;
*/
#include <iostream>
#include <chrono>
#include <bitset>
#include <immintrin.h>

using namespace std::chrono;
using namespace std;

constexpr uint64_t N = 100*1000*1000;
alignas(64) uint64_t data[N];
alignas(64) uint64_t result[N];

void simd_reverse(){

    register uint64_t mask1, mask2;

    for(register uint64_t i = 0; i<N-8; i+=8) {

        register __m512i result_vector        = _mm512_load_epi64(data+i);

        mask1 = 0b1111111111111111111111111111111100000000000000000000000000000000;
        mask2 = 0b0000000000000000000000000000000011111111111111111111111111111111;
        register __m512i shift_count_1        = _mm512_set_epi64(mask1, mask1, mask1, mask1, mask1, mask1, mask1, mask1); //1111111111111111111111111111111100000000000000000000000000000000
        register __m512i shift_count_2        = _mm512_set_epi64(mask2, mask2, mask2, mask2, mask2, mask2, mask2, mask2);//0000000000000000000000000000000011111111111111111111111111111111
        register __m512i shift_limit_1        = _mm512_set_epi64(32, 32, 32, 32,32, 32, 32, 32);
        result_vector                         = _mm512_or_epi64(_mm512_srlv_epi64(_mm512_and_epi64(result_vector,shift_count_1),shift_limit_1), _mm512_sllv_epi64(_mm512_and_epi64(result_vector,shift_count_2),shift_limit_1));

        mask1 = 0b1111111111111111000000000000000011111111111111110000000000000000;
        mask2 = 0b0000000000000000111111111111111100000000000000001111111111111111;
        register __m512i shift_count_3        = _mm512_set_epi64(mask1, mask1, mask1, mask1, mask1, mask1, mask1, mask1);
        register __m512i shift_count_4        = _mm512_set_epi64(mask2, mask2, mask2, mask2, mask2, mask2, mask2, mask2);
        register __m512i shift_limit_2        = _mm512_set_epi64(16, 16, 16, 16,16, 16, 16, 16);
        result_vector                         = _mm512_or_epi64(_mm512_srlv_epi64(_mm512_and_epi64(result_vector,shift_count_3),shift_limit_2), _mm512_sllv_epi64(_mm512_and_epi64(result_vector,shift_count_4),shift_limit_2));

        mask1 = 0b1111111100000000111111110000000011111111000000001111111100000000;
        mask2 = 0b0000000011111111000000001111111100000000111111110000000011111111;
        register __m512i shift_count_5        = _mm512_set_epi64(mask1, mask1, mask1, mask1, mask1, mask1, mask1, mask1);
        register __m512i shift_count_6        = _mm512_set_epi64(mask2, mask2, mask2, mask2, mask2, mask2, mask2, mask2);
        register __m512i shift_limit_3        = _mm512_set_epi64(8, 8, 8, 8,8, 8, 8, 8);
        result_vector                         = _mm512_or_epi64(_mm512_srlv_epi64(_mm512_and_epi64(result_vector,shift_count_5),shift_limit_3), _mm512_sllv_epi64(_mm512_and_epi64(result_vector,shift_count_6),shift_limit_3));

        mask1 = 0b1111000011110000111100001111000011110000111100001111000011110000;
        mask2 = 0b0000111100001111000011110000111100001111000011110000111100001111;
        register __m512i shift_count_7        = _mm512_set_epi64(mask1, mask1, mask1, mask1, mask1, mask1, mask1, mask1);
        register __m512i shift_count_8        = _mm512_set_epi64(mask2, mask2, mask2, mask2, mask2, mask2, mask2, mask2);
        register __m512i shift_limit_4        = _mm512_set_epi64(4, 4, 4, 4,4, 4, 4, 4);
        result_vector                         = _mm512_or_epi64(_mm512_srlv_epi64(_mm512_and_epi64(result_vector,shift_count_7),shift_limit_4), _mm512_sllv_epi64(_mm512_and_epi64(result_vector,shift_count_8),shift_limit_4));

        mask1 = 0b1100110011001100110011001100110011001100110011001100110011001100;
        mask2 = 0b0011001100110011001100110011001100110011001100110011001100110011;
        register __m512i shift_count_9        = _mm512_set_epi64(mask1, mask1, mask1, mask1, mask1, mask1, mask1, mask1);
        register __m512i shift_count_10       = _mm512_set_epi64(mask2, mask2, mask2, mask2, mask2, mask2, mask2, mask2);
        register __m512i shift_limit_5        = _mm512_set_epi64(2, 2, 2, 2,2, 2, 2, 2);
        result_vector                         = _mm512_or_epi64(_mm512_srlv_epi64(_mm512_and_epi64(result_vector,shift_count_9),shift_limit_5), _mm512_sllv_epi64(_mm512_and_epi64(result_vector,shift_count_10),shift_limit_5));

        mask1 = 0b1010101010101010101010101010101010101010101010101010101010101010;
        mask2 = 0b0101010101010101010101010101010101010101010101010101010101010101;
        register __m512i shift_count_11       = _mm512_set_epi64(mask1, mask1, mask1, mask1, mask1, mask1, mask1, mask1);
        register __m512i shift_count_12       = _mm512_set_epi64(mask2, mask2, mask2, mask2, mask2, mask2, mask2, mask2);
        register __m512i shift_limit_6        = _mm512_set_epi64(1, 1, 1, 1,1, 1, 1, 1);
        result_vector                         = _mm512_or_epi64(_mm512_srlv_epi64(_mm512_and_epi64(result_vector,shift_count_11),shift_limit_6), _mm512_sllv_epi64(_mm512_and_epi64(result_vector,shift_count_12),shift_limit_6));

        _mm512_store_epi64(result+i, result_vector);
    }
}

int main() {
//    for(register uint64_t i = 0; i<N; i++)
//        data[i] = i;
    for(uint64_t i = 0; i<N; i++)
        data[i] = (uint64_t) rand() * rand() * rand() * rand();

    auto start = std::chrono::high_resolution_clock::now();
    simd_reverse();
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Done in " << duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms" << std::endl;
    cout << "Input  = "<< bitset<64> (data[7]) << endl;
    cout << "Output = "<<bitset<64>(result[7]) << endl;
    return 0;
}
