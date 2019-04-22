
short int contador = 1;

void interrupt(){
      if(INTCON3.INT1IF && INTCON3.INT1IE){//Si entra por la interrupcion del switch
          T0CON = 0x84; //se carga el prescaler elegido 32 en este caso
          //Se carga el valor de alfa en los dos registros numero 0x0BDC en este caso
          TMR0H =(3036 >>8); //Primero los bits altos
          TMR0L = (3036);//Despues los bits bajos
          PORTC.B0 = 1; //Manda una señal hacia el led
          INTCON3.INT1IF = 0;
          INTCON3.INT1IE = 0;
               //Configuracion de TMR0
               INTCON.TMR0IF = 0; // se pone el interruption flag a 0
               INTCON.TMR0IE = 1; // se habilita la interrupción del Timer 0
      }
      
      if(INTCON.TMR0IF && INTCON.TMR0IE){ //Si entra por el timer
        if(contador < 60 ){//Si el contador no ha llegado a 60 Y el contador esta en modo contar
             contador++;  //Cuenta los ciclos pasados
             //Se carga el valor de alfa en los dos registros numero 0x0BDC en este caso
             TMR0H =(3036 >>8); //Primero los bits altos
             TMR0L = (3036);//Despues los bits bajos

         }
        else {//Cuando llega a 60 se resetean las variables
              contador = 0;
              PORTC.B0 = 0;
              INTCON3.INT1IF = 0;
              INTCON3.INT1IE = 1;
              T0CON.B7 = 0;
        }
        INTCON.TMR0IF = 0;
      }
}

void main() {
     //Puertos
     TRISC.B0 = 0;
     TRISB.B1 = 1;
     PORTC.B0 = 0;

    //Configuración de las interrupciones

     //Configuracion de INT1
     INTCON2.INTEDG1 = 1;
     INTCON3.INT1IF = 0;
     INTCON3.INT1IE = 1;




     INTCON.GIE = 1; // se habilitan las interrupciones en general

     while(1);
}