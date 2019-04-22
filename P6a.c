
void interrupt(){

     if(PORTC.B0 == 0){  //TIMER T2
           T0CON= 0xC1;
          TMR0L =  106;
             PORTC.B0 = 1;

     }
     else{ //TIMER T2
          T0CON=0xC2;
          TMR0L = 81;
              PORTC.B0 =0;

     }
     INTCON.TMR0IF = 0;
}
void main() {
     //Puertos
     TRISC.B0 = 0;

     
    //Configuración de las interrupciones
     T0CON= 0xC1;

     INTCON.TMR0IF = 0; // se pone el flag a 0
     INTCON.TMR0IE = 1; // se habilita la interrupción del Timer 0
     INTCON.GIE = 1; // se habilitan las interrupciones en general
     TMR0L =  81; //se carga el valor inicial (alfa) del ‘contador’
     PORTC.B0=0;
     
     while(1);
}