/*
 * File:   Laboratorio2.c
 * Author: diegomazariegos
 *
 * Created on February 5, 2021, 6:25 PM
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>
#include "INTERR.h"

//******************************************************************************
//                          CONFIGURACION  
//******************************************************************************

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//******************************************************************************
//                           CONFIGURACION
//******************************************************************************

void Setup (void);
void __interrupt () ISR(void);

void Setup (void) {
    ANSEL  = 0; // indica que los puertos son analogicos 
    ANSELH = 0; 
    
    TRISB = 0b00000011;    //el puerto 2 y 3 son entradas
    PORTB = 0;
    
    TRISA = 0;  // indica que mi puerto es una salida y que limpia dicho puerto
    PORTA = 0; 
}

//******************************************************************************
//                           LISTAS
//******************************************************************************

char conta = 0;
char vadc;
char masadc;
char menadc;
char multplex1;
char multplex2;
char f = 1;

//******************************************************************************
//                         CÓDIGO PRINCIPAL
//******************************************************************************

void __interrupt() ISR(void){
    if (INTCONbits.RBIF == 1 && INTCONbits.RBIE == 1) {
        if (PORTBbits.RB0 == 1) {
            conta++;
        }
        
        if (PORTBbits.RB1 == 1) {
            conta--;
        }
    }
    
    INTCONbits.RBIF = 0;
}

//******************************************************************************
//                           LOOP PRINCIPAL
//******************************************************************************

void main(void) {
    Setup();
    config_INTERR();
    
    while (1) {
        PORTA = conta;
    }
}
