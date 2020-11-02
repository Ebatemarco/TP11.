/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include "Header.h"

void putchar_d (int num)
{
    if (num < 0)
    {
        putchar ('-');
        num = -num;
    }
    if (num == 0)
    {
        return;
    }
    else 
    {
        putchar_d (num/10);
        putchar ((num%10)+48);
    }
    return;
}

void putchar_x (unsigned int num)
{
    if (num == 0)
    {
        return;
    }
    else 
    {
        putchar_x (num/16);
        switch (num%16)
        {
            case 15:
                putchar ('F');
                break;
            case 14:
                putchar ('E');
                break;
            case 13:
                putchar ('D');
                break;
            case 12:
                putchar ('C');
                break;
            case 11:
                putchar ('B');
                break;
            case 10:
                putchar ('A');
                break;
            default:
                putchar ((num%16)+48);
                break;
        }
    }
    return;
}

void putchar_c (int letra)
{
    putchar ((char)letra);   
}
