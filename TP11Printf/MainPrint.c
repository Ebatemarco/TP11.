/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainPrint.c
 * Author: ebatemarco
 *
 * Created on 29 de octubre de 2020, 15:57
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Header.h"

/*
 * 
 */

void mi_printf(char* string, ...);

int main(int argc, char** argv) 
{
    mi_printf ("Hola mundo: %d %x %c", 97, 97, 97);
    
    return (EXIT_SUCCESS);
}

void mi_printf(char* string, ...)
{
    va_list param_list;
    va_start (param_list, string); 
    
    int i = 0;
    
    while (string[i] != '\0')
    {
        if ((string[i] <= 254)&(string[i]>= 38)|(string[i] <= 36)&(string[i]>= 32))
        {
            putchar (string[i]);
        }
        else if ((string[i] == '%'))
        {
            switch (string[i+1])
            {   
                case 'd':
                    putchar_d (va_arg(param_list,int));
                    break;
                case 'x':
                    putchar_x (va_arg(param_list,unsigned int));
                    break;
                case 'c':
                    putchar_c (va_arg(param_list,int));
                    break;
                default:
                    break;
            }
            i++;
        }
        i++;
    }
    va_end (param_list);
}