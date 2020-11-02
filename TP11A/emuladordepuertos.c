/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "emuladordepuertos.h"


#define MASCARA 0x01 
#define ERROR -1 //le asigno un valor cualquiera a error

//variable global
static port16b_t puertos;

int bitSet (char puerto, char bit)
{
    int mask=MASCARA; //le asigno un valor inicial a la mascara
    mask<<=bit; //la mascara cambia dependiendo del bit que quiera encenderse
    int val;
    val = valbit (puerto, bit); //compruebo si los paramentros son validos
    if (val!=ERROR)
     {    
       switch (puerto) //con que puerto quiere trabajar
        {   
        case 'A': 
            puertos.registries.portA |= mask; //le aplico la mascara 
            break;
        case 'B':
            puertos.registries.portB |= mask;
            break;
        case 'D':
            puertos.portD |= mask;
            break;
         default: break;
        }   
   }
   return val; //devuelvo si es valido
}

int bitClr (char puerto, char bit)
{
    int mask=MASCARA;
    mask<<=bit;
    mask=~mask; //complemento a1 a la mascara que voy a utilizar
    int val;
    val = valbit (puerto, bit); //valido?
    if (val!=ERROR)
     {    
       switch (puerto)
        {   
        case 'A':
            puertos.registries.portA &= mask; //apago el bit seleccionado
            break;
        case 'B':
            puertos.registries.portB &= mask;
            break;
        case 'D':
            puertos.portD &= mask;
            break;
         default: break;
        }   
   } 
   return val;
}

int bitGet (char puerto, char bit)
{
    int mask=MASCARA; 
    mask<<=bit;
    int val;
    val = valbit (puerto, bit);
    if (val!=ERROR)
     {    
       switch (puerto) //casos con los distintos puertos
        {   
        case 'A':
            //le aplico la mascara al bit y guardo si esta prendido o apagado
            val= (puertos.registries.portA & mask) ? 1:0;
            break;
        case 'B':
            val= (puertos.registries.portB & mask) ? 1:0;
            break;
        case 'D':
            val=(puertos.portD & mask)? 1:0;
            break;
         default: break;
        }   
   }
   return val;
}

int bitToggle (char puerto, char bit)
{
    int mask=MASCARA;
    mask<<=bit;
    int val;
    val = valbit (puerto, bit);
    if (val!=ERROR)
     {    
       switch (puerto)
        {   
        case 'A':
            //cambio el bit al estado opuesto
            puertos.registries.portA |= mask; 
            break; 
        case 'B':
            puertos.registries.portB |= mask;
            break;
        case 'D':
            puertos.portD |= mask;
            break;
         default: break;
        }   
   }
   return val;
}

int maskOn (char puerto, char mask)
{
    int val;
    val = valmask (puerto, mask); //valido la mascara
    if (val!=ERROR)
     {    
       switch (puerto)
        {   
        case 'A':
            //prendo los bits que estan encendidos en la mascara
            puertos.registries.portA |= mask;
            break;
        case 'B':
            puertos.registries.portB |= mask;
            break;
        case 'D':
            puertos.portD |= mask;
            break;
         default: break;
        }   
   }
   return val;
}

int maskOff (char puerto, char mask)
{
    int val;
    val = valmask (puerto, mask);
    mask=~mask;
    if (val!=ERROR)
     {    
       switch (puerto)
        {   
        case 'A':
            //apago los bits prendidos en la mascara
            puertos.registries.portA &= mask;
            break;
        case 'B':
            puertos.registries.portB &= mask;
            break;
        case 'D':
            puertos.portD &= mask;
            break;
         default: break;
        }   
   }
   return val;
}

int maskToggle (char puerto, char mask)
{
    int val;
    val = valmask (puerto, mask);
    if (val!=ERROR)
     {    
       switch (puerto)
        {   
        case 'A':
            //cambio el estado de los bits que estan en la mascara
            puertos.registries.portA ^= mask;
            break;
        case 'B':
            puertos.registries.portB ^= mask;
            break;
        case 'D':
            puertos.portD ^= mask;
            break;
         default: break;
        }   
   }
   return val;
}

void led_state (char puerto)
{
    int i;
    switch (puerto) //dependiendo el puerto que recibe por teclado
    {
        case 'A':
            //imprimo el estado de los 8 bits del puerto A
        for (i=7; i>=0; i--)   
        {
           printf ("LED %d: %d\n", i, bitGet (PORTA, i));
        } 
        break;
        case 'B':
            //imprimo los bits del puerto B
        for (i=7; i>=0; i--)   
        {
           printf ("LED %d: %d\n", i, bitGet (PORTB, i));
        }
        break;
        case 'D':
            //imprimo el estado de los bits del puerto D
        for (i=15; i>=0; i--)   
        {
           printf ("LED %d: %d\n", i, bitGet (PORTD, i));
        }
        break;
        default: break;
    }        
    
    printf ("\n");
}

int valbit (char puerto, char bit)
{
    int val;
    //le asigno las condiciones de los bits y los 3 puertos
    if ((bit>7 || bit<0) || ((puerto != PORTA) && (puerto != PORTB) && (puerto != PORTD)))
    {
        val=-1;
    }
    else 
    {    
        val=1;
    }    
    return val;
    
}

int valmask (char puerto, char mask)
{
    int val;
    //condicion de los puertos
    if ((puerto != PORTA) && (puerto != PORTB) && (puerto != PORTD))
    {
        val=-1;
    }
    else 
    {
        val=1;
    }
    return val;
}
