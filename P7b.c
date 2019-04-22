//Recordatorio: A�adir librerias de LCD y Conversiones en Library Manager
//LCD pinout
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;
// Pin direction
sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;

char txt[14];
float aux;
float resultado;
void interrupt()
{
   if(PIR1.ADIF)
   {
      aux = ADRESL +(ADRESH << 8);   //Para bit ADFM = 1
      //T�C = V0 * 100;
      resultado = ((aux * 500.0)/1023.0); //Convierto el valor propocionado por el convertidor mediante una regla de 3 sabiendo el valor m�ximo del convertidor y la tension de referencia

      //Mando el valor proporcionado por el convertidor al LCD
      FloatToStr(resultado,txt);
      LCD_cmd(_LCD_CLEAR);//Limpio la pantalla antes de mandar el siguiente valor
      LCD_out(1,1,txt);
      LCD_chr_cp(' ');
      LCD_chr_cp(223);
      LCD_chr_cp('C');
      PIR1.ADIF = 0;  //Pongo a 0 el bit de la interrupcion
  }
  else  if(INTCON.TMR0IF)
  {
       INTCON.TMR0IF = 0;//Pongo a 0 el flag de interrupcion
       //reseteo el valor inicial (alfa) del �timer�
       TMR0H =(18661 >>8); //Primero los bits altos
       TMR0L = (18661);//Despues los bits bajos
       ADCON0.B2 = 1; //Pongo el registro GO a 1 para realizar una conversion
       PORTC.B0 = !PORTC.B0;

  }
}
void main()
{

        //LCD
        Lcd_Init();

        TRISE.B0 = 1; //Pin RA0 de entrada
         TRISC.B0 = 0; //Pin RA0 de entrada
         PORTC.B0 = 0;
        //Configuracion del convertidor AD
       //Prescaler de 16, CHS = 110; GO = 0; ADON = 1
        ADCON0= 0x71;
        //ADFM = 1, resto de bits a 0, todos los terminales como anal�gicos y tension de referencia la de alimentaci�n
        ADCON1 = 0x80;
        
        //Configuracion de la interrupcion del convertidor AD
        PIR1.ADIF = 0;
        PIE1.ADIE = 1;
        INTCON.PEIE = 1;

        //Configuracion del timer
         T0CON= 0x85;//Prescaler de 64
         INTCON.TMR0IF = 0; // se pone el flag a 0
         INTCON.TMR0IE = 1; // se habilita la interrupci�n del Timer 0
         //se carga el valor inicial (alfa) del �contador�
         TMR0H =(18661 >>8); //Primero los bits altos
         TMR0L = (18661);//Despues los bits bajos
         INTCON.PEIE = 1;
         INTCON.GIE = 1;

         while(1);

}