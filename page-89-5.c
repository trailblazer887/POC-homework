#include <stdio.h>
#include <string.h>
int store_bit_field(int original_value,
int value_to_store,
unsigned starting_bit, unsigned ending_bit){
    unsigned mask = (unsigned)(~0) << (sizeof(unsigned) * 8 - 1 - starting_bit) >> (sizeof(unsigned) * 8 - 1 - starting_bit)
                                   >> ending_bit << ending_bit;
    original_value &= ~mask;
    value_to_store <<= ending_bit;
    value_to_store &= mask;
    original_value |= value_to_store;
    return original_value;
}
int main(){
    printf("%x\n", store_bit_field(0xffff, 0x123, 13, 9));
    return 0;
}