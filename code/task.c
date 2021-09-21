#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define CHAR_FIRST_POS  0

#define TRUE 1
#define FALSE 0

uint8_t GetNumber(int64_t x, uint64_t exp);
int64_t Invert(int64_t x, uint64_t exp);

int main()
{
    int64_t value = 0;
    int64_t after_point_value = 0;
    
    
    char buffer;
    
    uint64_t point = 1;
    
    uint8_t sign = FALSE;
    uint8_t point_found = FALSE;
    uint8_t first_zero = TRUE;
    uint8_t zero_count = 0;
    
    while((buffer = getchar()) != EOF && buffer != '\n' && buffer != '\0')
    {
        switch(buffer)
        {
        case '-':
            if(point == 1)
            {
                sign = TRUE;
            }
            else
            {
                printf("Input error. Sign found in the value.\n");
                exit(-1);
            }
            break;
        case '.':
            if(!point_found)
            {
                point_found = TRUE;
                value = Invert(value, point / 10);
                point = 1;
            }
            else
            {
                printf("Input error. Found second point.\n");
                exit(-1);
            }
            break;
        case '0':
            if(point_found && first_zero)
            {
                zero_count++;
            }
            point *= 10;
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if(point_found && first_zero)
            {
                first_zero = FALSE;
            }
            if(point_found)
            {
                after_point_value += (buffer - '0') * point;
                point *= 10;
            }
            else
            {
                value += (buffer - '0') * point;
                point *= 10;
            }
            break;
        case ' ':
            break;
        default:
            printf("Input error. Incorrect input.\n");
            exit(-1);
            break;
        }
        if(point % 10 && point != 1)
        {
            printf("Input error: Input value is hight.\n");
            exit(-1);
        }
    }
    
    if(!point_found)
    {
        
        printf("Input error: Point not found.\n");
        exit(-1);
    }
    
    after_point_value = Invert(after_point_value, point / 10);
    
    if(sign)
    {
        value *= -1;
    }
    
    printf("%li | ", value);
    
    if(after_point_value)
    {
        for(uint8_t z = 0; z < zero_count; z++)
        {
            printf("0");
        }
    }
    printf("%li\n", after_point_value);
    
    exit(0);
}

int64_t Invert(int64_t x, uint64_t exp)
{
    int64_t r_x = 0;
    uint64_t p = 1;
    
    for(uint64_t e = exp; e > 0; e /= 10)
    {
        r_x += GetNumber(x, e) * p;
        p *= 10;
    }
    
    return r_x;
}

uint8_t GetNumber(int64_t x, uint64_t exp)
{
    if(x < 0)
    {
        x *= -1;
    }
    if(exp == 0)
    {
        return 0;
    }
    return (x / exp) % 10;
}































