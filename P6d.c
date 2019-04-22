  short int x;
void interrupt() // rutina de servicio de la interrupcion (MikroC)
{
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

       TMR0H =(3036 >>8); //Primero los bits altos
       TMR0L = (3036);//Despues los bits bajos
        INTCON.TMR0IF = 0;
      }
  x = PORTB; // hay que leer el puerto B antes de borrar el flag
  INTCON.RBIF = 0; // se borra el flag
  }
void main()
{
  TRISB.B4 = 1;
  INTCON.PEIE = 0; // es de tipo core „± no es necesario poner el bit PEIE a cero
  RCON.IPEN = 0; // se deshabilitan las interrupciones con prioridad
  x = PORTB; // x es una variable de 8 bis.
  INTCON.RBIF = 0; // se pone el flag a 0
  INTCON.RBIE = 1; // se habilita la interrupcion por cambio de nivel
  INTCON.GIE = 1; // se habilitan las interrupciones en general

}