//Recordatorio: Añadir librerias de LCD y Conversiones en Library Manager
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

void interrupt()
{
   if(PIR1.ADIF)
   {
      float aux = ADRESL +(ADRESH << 8);   //Para bit ADFM = 1
      char txt[14];
      float resultado = (aux * 5.0)/1023.0; //Convierto el valor propocionado por el convertidor mediante una regla de 3 sabiendo el valor máximo del convertidor y la tension de referencia

      //Mando el valor proporcionado por el convertidor al LCD
      FloatToStr(resultado,txt);
      LCD_cmd(_LCD_CLEAR);//Limpio la pantalla antes de mandar el siguiente valor
      LCD_out(1,1,txt);
      PIR1.ADIF = 0;  //Pongo a 0 el bit de la interrupcion
  }
  else  if(INTCON.TMR0IF)
  {
       INTCON.TMR0IF = 0;//Pongo a 0 el flag de interrupcion
       //reseteo el valor inicial (alfa) del ‘timer’
       TMR0H =(3036 >>8); //Primero los bits altos
       TMR0L = (3036);//Despues los bits bajos
       ADCON0.B2 = 1; //Pongo el registro GO a 1 para realizar una conversion

  }
}
void main()
{

        //LCD
        Lcd_Init();

        TRISA.B0 = 1; //Pin RA0 de entrada

        //Configuracion del convertidor AD
       //Prescaler de 16, CHS = 0; GO = 0; ADON = 1
        ADCON0= 0x41;
        //ADFM = 1, resto de bits a 0, todos los terminales como analógicos y tension de referencia la de alimentación
        ADCON1 = 0x80;
        
        //Configuracion de la interrupcion del convertidor AD
        PIR1.ADIF = 0;
        PIE1.ADIE = 1;
        INTCON.PEIE = 1;

        //Configuracion del timer
         T0CON= 0x84;//Prescaler de 32
         INTCON.TMR0IF = 0; // se pone el flag a 0
         INTCON.TMR0IE = 1; // se habilita la interrupción del Timer 0
         //se carga el valor inicial (alfa) del ‘contador’
         TMR0H =(3036 >>8); //Primero los bits altos
         TMR0L = (3036);//Despues los bits bajos
         INTCON.PEIE = 1;
         INTCON.GIE = 1;

         while(1);

}