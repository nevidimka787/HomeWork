#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define DEFAULT_OUTPUT_VALUE    0
#define CHAR_FIRST_POSITION     0u

#define BIT     1lu

#define TRUE    1u
#define FALSE   0u

#define POSITIVE   0u
#define NEGATIVE    1u

#define CHANGE_SIGNT -1

#define FUNCTION_ERROR                  -1
#define PROGRAM_FINISHED_SUCCESSFULLY   0

#define CHAR_ENDL    '\n'
#define CHAR_END     '\0'

#define MAX_POINT_POSITION  ((sizeof(int64_t) * CHAR_BIT) - 1)

#define MIN_NEGATIVE_VALUE  0x

//The function reverse bits in x beginning from indicated bit.
int64_t Revers(int64_t x, uint8_t from_bit);

int main()
{
    int64_t value = DEFAULT_OUTPUT_VALUE;
    char buffer;
    
    uint8_t point = CHAR_FIRST_POSITION;
    uint8_t sign = POSITIVE;
    uint8_t flag_number_found = FALSE;
    
    printf("Set binare value.\n");
    
    while(
        (buffer = getchar()) != EOF &&
        buffer != CHAR_ENDL &&
        buffer != CHAR_END)
    {
        switch(buffer)
        {
        case '-':
            if(!point)
            {
                sign = NEGATIVE;
            }
            else
            {
                printf("ERROR::The minus sign is not in the first position.\nSigt position: %i\n", point + 1);
                exit(FUNCTION_ERROR);
            }
            break;
        case '1':
            value |= BIT << point;
        case '0':
            point++;
            if(flag_number_found == FALSE)
            {
                flag_number_found = TRUE;
            }
            break;
        default:
            printf("ERROR::Undefined symbol: \'%c\'.\nSymbol id: %i.\n", buffer, buffer);
            exit(FUNCTION_ERROR);
            break;
        }
        if(
            (sign == POSITIVE && point > MAX_POINT_POSITION) ||
            (sign == NEGATIVE && (point > MAX_POINT_POSITION && value != 1) || point > MAX_POINT_POSITION + 1)
        )
        {//Check max positive value and min negative value.
            printf("ERROR::Value is overflow.\n");
            exit(FUNCTION_ERROR);
        }
    }
    
    if(flag_number_found == FALSE)
    {
        printf("ERROR::Value doesn't set.\n");
        exit(FUNCTION_ERROR);
    }
    
    value = Revers(value, point - 1);
    
    if(sign == NEGATIVE)
    {
        value *= -1;
    }
    
    printf("Decimal value: %li\n", value);
    
    exit(CHANGE_SIGNT);
}

#define INVERT__DEFAUL_OUTPUT_VALUE 0
#define INVERT__BIT                 1lu

int64_t Revers(int64_t x, uint8_t from_bit)
{
    int64_t r_x = INVERT__DEFAUL_OUTPUT_VALUE;
    for(uint8_t p = from_bit + 1; p > 0; p--)
    {
        if(x & (INVERT__BIT << (p - 1)))
        {
            r_x += INVERT__BIT << (from_bit - (p - 1));
        }
    }
    return r_x;
}

//1000 0000 0000 0000 0000 0000 0000 0000

//100000000000000000000000000000000000




