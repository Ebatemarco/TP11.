/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ebatemarco
 *
 * Created on 30 de octubre de 2020, 16:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "emuladordepuertos.h"

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int switchcase (char bit, char puerto);
//cambia el estado del bit al opuesto

int main()
{
    //VARIABLES
    int bitactual;
    int x1=12;
    int x2 = 30;
    
    bool bit_parpadeo[8]={false,false,false,false,false,false,false,false};
    bool estado_parpadeo=false;
    
    //
    
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(258, 128);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    /*must_init(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP* Bitmap = al_load_bitmap("EstadoBase.jpg");
    must_init(Bitmap, "Bitmap");*/
    
    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE ks;

    x1=12;
    x2=30;
    for(bitactual=7; bitactual>=0;bitactual--)
    {
        al_draw_filled_rectangle(x1, 55, x2, 40, al_map_rgba_f(1, 1, 1, 1));
        x1+=31;
        x2+=31;
    } 
    al_flip_display();
    
                    
    al_start_timer(timer);
    while(!done)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            /*case ALLEGRO_EVENT_TIMER:
                // game logic goes here.
                
                redraw = true;
                break;*/
            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_T)
                {
                    x1=12;
                    x2=30;
                    
                    for(bitactual=7; bitactual>=0;bitactual--)
                    {
                        switch(bitGet(PORTA, bitactual))
                        {        
                            case 0: 
                                al_draw_filled_rectangle(x1, 55, x2, 40, al_map_rgba_f(1, 0, 0, 1));
                                break;
                            case 1:
                                al_draw_filled_rectangle(x1, 55, x2, 40, al_map_rgba_f(1, 1, 1, 1));
                                break;
                            default: break;        
                        }   
                        x1+=31;
                        x2+=31;
                    } 
                    al_flip_display();
                    maskToggle(PORTA, 0xFF);
                    led_state (PORTA);
                    
                } 
                if(event.keyboard.keycode == ALLEGRO_KEY_B)
                {
                    if(estado_parpadeo==true)
                    {
                        printf("Estado Parpadeo FALSE\n");
                        estado_parpadeo=false;
                        for(bitactual=0;bitactual<=7;bitactual++)
                        {
                            bit_parpadeo[bitactual]=false;    
                        }
                           
                    }
                    else
                    {
                        estado_parpadeo=true;
                        printf("Estado Parpadeo TRUE\n");
                        for(bitactual=0;bitactual<=7;bitactual++)
                        {
                            if(bitGet(PORTA,bitactual)==true)
                            {
                                bit_parpadeo[bitactual]=true;
                            }    
                        }
                    }
                    
                } 
                if(event.keyboard.keycode == ALLEGRO_KEY_C)
                {
                    maskOff (PORTA, 0xFF);
                    led_state (PORTA);
                    x1=12;
                    x2=30;
                    for(bitactual=7; bitactual>=0;bitactual--)
                    {
                        al_draw_filled_rectangle(x1, 55, x2, 40, al_map_rgba_f(1, 1, 1, 1));
                        x1+=31;
                        x2+=31;
                    } 
                    al_flip_display();
                } 
                if(event.keyboard.keycode == ALLEGRO_KEY_S)
                {
                    maskOn (PORTA, 0xFF);
                    led_state (PORTA);
                    x1=12;
                    x2=30;
                    for(bitactual=7; bitactual>=0;bitactual--)
                    {
                        al_draw_filled_rectangle(x1, 55, x2, 40, al_map_rgba_f(1, 0, 0, 1));
                        x1+=31;
                        x2+=31;
                    }
                    al_flip_display();
                    
                } 
                if(event.keyboard.keycode == ALLEGRO_KEY_0)
                {
                    switchcase (0, PORTA);
                    led_state (PORTA);
                    if(bitGet(PORTA, 0)==1)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(229, 55, 247, 40, al_map_rgba_f(1, 0, 0, 1));
                        al_flip_display();
                    }
                    else if(bitGet(PORTA, 0)==0)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(229, 55, 247, 40, al_map_rgba_f(1, 1, 1, 1));
                        al_flip_display();     
                    }
                    else
                    {
                        led_state (PORTA);
                    }
                }    
                if(event.keyboard.keycode == ALLEGRO_KEY_1)
                {
                    switchcase (1, PORTA);
                    led_state (PORTA);
                    if(bitGet(PORTA, 1)==1)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(198, 55, 216, 40, al_map_rgba_f(1, 0, 0, 1));
                        al_flip_display();
                    }
                    else if(bitGet(PORTA, 1)==0)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(198, 55, 216, 40, al_map_rgba_f(1, 1, 1, 1));
                        al_flip_display();     
                    }
                    else
                    {
                        led_state (PORTA);
                    }
                }    
                if(event.keyboard.keycode == ALLEGRO_KEY_2)
                {
                    switchcase (2, PORTA);
                    led_state (PORTA);
                    if(bitGet(PORTA, 2)==1)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(167, 55, 185, 40, al_map_rgba_f(1, 0, 0, 1));
                        al_flip_display();
                    }
                    else if(bitGet(PORTA, 2)==0)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(167, 55, 185, 40, al_map_rgba_f(1, 1, 1, 1));
                        al_flip_display();     
                    }
                    else
                    {
                        led_state (PORTA);
                    }
                }    
                if(event.keyboard.keycode == ALLEGRO_KEY_3)
                {
                    switchcase (3, PORTA);
                    led_state (PORTA);
                    
                    if(bitGet(PORTA, 3)==1)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(136, 55, 154, 40, al_map_rgba_f(1, 0, 0, 1));
                        al_flip_display();
                    }
                    else if(bitGet(PORTA, 3)==0)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(136, 55, 154, 40, al_map_rgba_f(1, 1, 1, 1));
                        al_flip_display();     
                    }
                    else
                    {
                        led_state (PORTA);
                    }
                }    
                if(event.keyboard.keycode == ALLEGRO_KEY_4)    
                {
                    switchcase (4, PORTA);
                    led_state (PORTA);
                    if(bitGet(PORTA, 4)==1)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(105, 55, 123, 40, al_map_rgba_f(1, 0, 0, 1));
                        al_flip_display();
                    }
                    else if(bitGet(PORTA, 4)==0)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(105, 55, 123, 40, al_map_rgba_f(1, 1, 1, 1));
                        al_flip_display();     
                    }
                    else
                    {
                        led_state (PORTA);
                    }
                }    
                if(event.keyboard.keycode == ALLEGRO_KEY_5)
                {
                    switchcase (5, PORTA);
                    led_state (PORTA);
                    if(bitGet(PORTA, 5)==1)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(74, 55, 92, 40, al_map_rgba_f(1, 0, 0, 1));
                        al_flip_display();
                    }
                    else if(bitGet(PORTA, 5)==0)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(74, 55, 92, 40, al_map_rgba_f(1, 1, 1, 1));
                        al_flip_display();     
                    }
                    else
                    {
                        led_state (PORTA);
                    }
                }    
                if(event.keyboard.keycode == ALLEGRO_KEY_6)
                {
                    switchcase (6, PORTA);
                    led_state (PORTA);
                    if(bitGet(PORTA, 6)==1)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(43, 55, 61, 40, al_map_rgba_f(1, 0, 0, 1));
                        al_flip_display();
                    }
                    else if(bitGet(PORTA, 6)==0)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(43, 55, 61, 40, al_map_rgba_f(1, 1, 1, 1));
                        al_flip_display();     
                    }
                    else
                    {
                        led_state (PORTA);
                    }
                }    
                if(event.keyboard.keycode == ALLEGRO_KEY_7)    
                {
                    switchcase (7, PORTA);
                    led_state (PORTA);
                    if(bitGet(PORTA, 7)==1)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(12, 55, 30, 40, al_map_rgba_f(1, 0, 0, 1));
                        al_flip_display();
                    }
                    else if(bitGet(PORTA, 7)==0)
                    {
                        led_state (PORTA);
                        al_draw_filled_rectangle(12, 55, 30, 40, al_map_rgba_f(1, 1, 1, 1));
                        al_flip_display();     
                    }
                    else
                    {
                        led_state (PORTA);
                    }
                }       
                if(event.keyboard.keycode == ALLEGRO_KEY_Q)    
                {
                    done=true;
                }  
                if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    done=true;
                }    
                    break;
                
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;    
                
        }
        if(redraw && al_is_event_queue_empty(queue))
        {
            x1=12;
            x2=30;
            for(bitactual=7;bitactual>=0;bitactual--)
            {
                
                if(bit_parpadeo[bitactual]==true)
                {
                    switch(bitGet(PORTA, bitactual))
                    {        
                        case 0: 
                        printf("Cambio el estado del bit %d de 0 a 1\n", bitactual);    
                        al_draw_filled_rectangle(x1, 55, x2, 40, al_map_rgba_f(1, 0, 0, 1));
                        bitSet(PORTA, bitactual);
                        break;
                        case 1:
                        printf("Cambio el estado del bit %d de 1 a 0\n", bitactual);
                        al_draw_filled_rectangle(x1, 55, x2, 40, al_map_rgba_f(1, 1, 1, 1));
                        bitClr(PORTA, bitactual);
                        break;
                        default: break;        
                    }   
                    x1+=31;
                    x2+=31;
                }
                else
                {
                    x1+=31;
                    x2+=31;
                }
            }
            al_flip_display();
            al_rest(0.125);
            redraw=true;

        }    

    }

    
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}

int switchcase (char bit , char puerto)
{
     if (bitGet(puerto, bit))
        bitClr (puerto, bit); //lo apago
     else 
        bitSet (puerto, bit); //lo prendo
}