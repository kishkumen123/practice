
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define ArraySize(x) (sizeof(x)/sizeof(x[0]))
#define StringSize(x) get_string_size(x);


static i32
get_string_size(char* s){
    char* at;
    i32 size = 0;

    for(at = s; *at != '\0'; ++at){
        size++;
    }
    return(size);
}


i32 main(i32 argc, char** argv){
    char* input = "f2 f2 d7 f6 d7 f4 d7 u2 f4 d2 d4 d5 f4 u1 u2 f9 f7 d1 f4 f7 f9 d2 d3 f1 f4 f6 u2 f6 d2 d5 u4 d5 f6 d7 d4 u5 f9 f5 d8 f3 f1 d7 d5 f2 d3 f8 d1 f4 u8 u8 u8 f2 d3 d5 u8 f1 f3 u1 u2 u4 d8 f5 d9 d9 f9 u3 d2 d9 u8 f3 u2 d7 f9 f1 u1 f9 f1 d1 f7 u3 u5 f3 f8 f4 d3 f5 f4 f2 d2 d3 f1 u2 u2 d9 d6 d6 u2 d6 f6 f5 d8 u3 u2 u1 f8 d3 d5 f8 f7 d9 d7 d9 d2 f8 d9 f2 f2 d5 u8 f9 d7 d9 f2 f9 f1 f3 f1 f3 d4 f6 f4 d7 u4 u5 f1 d4 d8 d3 d8 u3 f2 u7 d1 d7 d3 f3 f4 u8 d2 f8 d8 u8 u5 f5 f1 f5 u4 d5 d1 f3 f4 d8 d9 f4 d5 d5 f9 f7 d3 d4 f2 d7 d3 d9 d8 f6 f3 f1 f5 d4 d4 f9 d9 d5 u8 f1 f3 d1 d4 f1 u5 d9 f8 d8 d2 d3 f2 f9 f7 u3 d3 f4 d8 f7 d3 f3 d5 f8 f7 f4 d2 u5 f9 f8 d7 u5 u8 d4 d9 f5 u6 f7 d4 f8 u4 u2 d8 f4 d8 d3 d3 f1 u7 f5 f1 d5 f4 d3 d4 f4 d5 u9 f6 d6 u6 d8 f2 d9 d8 f7 d2 f1 f4 d7 f1 u8 f6 f2 f5 u1 f6 u7 d8 d5 d2 f4 f3 d7 u5 f1 f2 f3 f6 d9 d2 f7 u3 d4 f3 f3 f6 u2 d4 f8 d3 d4 f1 f3 f8 f1 f6 f1 f7 d8 u3 u5 f4 f6 d3 f5 f5 d9 f4 d5 f6 d1 f2 f3 f2 u4 f9 f7 f6 u1 d6 d1 f5 u4 u9 f5 f3 u9 d4 f7 u9 d7 f5 d4 d9 u4 f2 f2 f1 f3 f4 d3 d5 u9 f8 u5 d3 f5 d4 f1 f1 u5 d7 u7 d3 f7 d3 d3 d5 d2 d7 d5 d1 u3 f5 f9 u1 d8 u5 f4 d5 f5 d3 u8 f2 u7 d4 f1 u6 d7 d4 f9 f3 f7 u5 d1 d3 u2 f3 d8 u7 f9 f9 f9 d3 f4 f9 d6 u1 u7 d3 f4 f9 d9 u4 d2 f6 f4 d5 u3 d6 u4 d5 d7 d3 u1 d2 f1 f8 u7 f4 d5 d3 u7 f1 f7 u6 f4 f5 f3 f1 d5 u3 u3 d8 f1 f2 u6 d3 d6 d5 d4 u1 d9 f3 d8 u9 d3 f6 d8 f2 f4 f6 f3 f6 u6 u3 d6 u1 f9 f2 u6 f7 d5 f5 f7 d6 d9 f9 f1 u4 f3 f2 f2 u4 d7 d2 u2 d2 u9 f4 f3 f3 u4 d7 f5 d5 f1 d4 f4 u1 d5 f2 u3 u1 d9 u9 d3 f1 d6 f8 d5 f7 d4 f2 d3 d1 f6 f4 d9 f3 u4 u8 d2 u5 u8 u7 d2 d9 f8 d4 u7 f2 u4 f7 d3 d3 d6 u3 d6 d6 u7 d6 u9 d6 f3 f8 f3 d9 f6 f8 d7 f3 f7 f3 f8 f6 d9 u4 f1 f6 f2 f4 d4 d9 f7 f4 f4 u3 u6 f4 f7 f4 d2 f8 u4 f8 u2 u4 d5 f5 u2 u8 u9 f6 f2 u9 f5 u3 f8 f8 d5 f6 u6 d6 d1 f2 d1 d5 f2 d3 u7 f6 u9 d3 u3 f3 d9 d4 d2 f7 f2 d4 f5 u1 d6 d6 u2 d2 d4 d4 f8 d3 d5 d3 u2 d6 d9 u8 f3 d9 d6 d7 d6 f9 u1 f9 d8 f8 u5 d8 f5 d6 d9 f1 u5 u5 f4 f1 f6 d1 d4 d3 d1 d1 d9 d3 f6 u9 u4 d1 u6 f3 d2 d8 f1 f8 f4 d4 d5 u5 u5 f7 f6 f4 d5 f7 d4 f2 f5 f3 f5 u6 u9 d6 f8 d3 u2 f8 d9 f9 d3 d4 d5 u3 f6 f6 f8 u6 u4 f2 d1 d5 f1 f8 u5 d2 f4 d9 u5 d8 f6 f3 d8 u1 d5 d6 f2 f7 d8 f2 f8 f1 d1 d3 d8 d1 f1 f8 u4 u5 f2 f5 f5 f9 f2 f4 f4 d1 u8 f3 d9 f9 u5 f7 f3 u5 u5 d9 f9 u2 f1 f1 d5 d7 f2 u8 u7 d4 d6 d6 d6 f4 f7 d6 f3 f5 d2 u3 f3 f6 f9 f7 f6 d4 d9 f4 f4 d8 d7 d1 d6 u7 f3 f9 f9 u7 f2 u5 u6 d7 d7 d5 f8 d1 u4 d4 f4 f3 f7 f4 d6 d3 d3 f6 f7 f6 u5 d9 f9 f5 u5 d9 u8 d6 d8 d8 d8 f2 d8 d4 d6 f8 f3 f2 d5 d3 f1 f2 u9 f6 d8 u2 d2 f7 u6 u2 f1 d2 f7 f4 d6 f4 u4 f3 d2 d5 u5 d2 d1 d9 f3 d5 u8 d6 f3 f9 u6 d2 f6 f7 d1 u9 u9 u9 u4 f2 d7 d1 f8 d2 d1 f9 f8 u8 d5 f8 d1 d4 d3 d1 f2 d2 d6 f5 d9 f8 d9 u6 u5 f8 f3 d9 u6 d8 d3 d2 u1 u9 u7 u1 u4 f7 d8 u3 f1 u3 u7 f4 u3 d1 f3 f4 f7 d4 d4 d2 u1 u5 u3 f6 f6 f9 d9 f2 u3 f3 d2 d4 f6 f7 d5 f9 u7 d9 d1 d1 f1 u1 u5 d5 f4 u3 d1 d3 f3 f6 u4 d2 f1 f5 f3 f2 f4 d3 f2 d4 d7 u4 d7 f8 f2 d4 d2 f8 u7 f1 u4 f4 u7 f2 f7 f9 d8 d2 f8 d3 u5 f3 u9 f8 f5 u2 d5 d9 u9 f1 f3 d3 d6 f9 f5 d4 u7 f4 f3 d2 u1 f3 d4 d8 u4 d9 f6 d7 d3 d9 f3 d8 f7 f7 d1 d1 f1 d4 f8";
    //char* input = "f2 f2 f6 d7 f4 d7 u2 u1 u2 f9 f7 d2";

    i32 depth = 0;
    i32 aim = 0;
    i32 horizontal = 0;

    i32 input_size = get_string_size(input);
    for(i32 i=0; i < input_size; i = i + 3){
        char letter = input[i];
        i32 number = (i32)input[i + 1] - 48;
        if(letter == 'f'){
            horizontal += number;
            depth += (aim * number);
        }
        if(letter == 'd'){
            aim += number;
        }
        if(letter == 'u'){
            aim -= number;
        }
    }

    printf("horizontal: %i depth: %i total: %i\n", horizontal, depth, (horizontal*depth));


    return(0); 
}
