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

char txt[14];
float aux;
float resultado;
short int modo = 0; //0 Celsius, 1 Kelvin, 2 Farenheit


void representar()
{

      if(modo == 1) resultado = resultado + 273.15; //Le sumo para convertirlo a kelvin
      if(modo == 2) resultado = (resultado* 1.8)+32.0;
      FloatToStr(resultado,txt);
      LCD_cmd(_LCD_CLEAR);//Limpio la pantalla antes de mandar el siguiente valor
      LCD_out(1,1,txt);
      LCD_chr_cp(' ');
      LCD_chr_cp(223);
      if( modo == 0) LCD_chr_cp('C');
      if(modo == 1) LCD_chr_cp('K');
      if(modo == 2) LCD_chr_cp('F');

}
void interrupt()
{
   if(PIR1.ADIF)
   {
        aux = ADRESL +(ADRESH << 8);//Para bit ADFM = 1
      //Fórmula: TºC = V0 * 100;
      resultado = ((aux * 500.0)/1023.0); //Convierto el valor propocionado por el convertidor mediante una regla de 3 sabiendo el valor máximo del convertidor y la tension de referencia

      representar();
      PIR1.ADIF =0 ;
      


  }
  else if(INTCON.TMR0IF)
  {
       INTCON.TMR0IF = 0;//Pongo a 0 el flag de interrupcion
       //Reseteo el valor inicial (alfa) del ‘timer’
       TMR0H =(18661 >>8); //Primero los bits altos
       TMR0L = (18661);//Despues los bits bajos
       ADCON0.B2 = 1; //Pongo el registro GO a 1 para realizar una conversion

  }
  else if(INTCON.INT0IF && INTCON.INT0IE)
  {
       modo++;
       if(modo == 3) modo = 0;
       representar();
       INTCON.INT0IF = 0;
       
  }
}

void main()
{

        //LCD
        Lcd_Init();
        
        //PINES
        TRISE.B0 = 1; //Pin RE0 de entrada
        TRISB.B0 = 1; //Pin RB0 de entrada
        TRISC.B0 = 0;
        
        //Configuracion del convertidor AD
       //Prescaler de 16, CHS = 110; GO = 0; ADON = 1
        ADCON0= 0x71;
        //ADFM = 1, resto de bits a 0, todos los terminales como analógicos y tension de referencia la de alimentación
        ADCON1 = 0x80;
        
        //Configuracion de la interrupcion del convertidor AD
        PIR1.ADIF = 0;
        PIE1.ADIE = 1;
        INTCON.PEIE = 1;
        
        //Configuracion de la interrupcion INT0
        INTCON2.INTEDG0 = 1;
        INTCON.INT0IF = 0;
        INTCON.INT0IE = 1;

        //Configuracion del timer
         T0CON= 0x85;//Prescaler de 64
         INTCON.TMR0IF = 0; // se pone el flag a 0
         INTCON.TMR0IE = 1; // se habilita la interrupción del Timer 0
         //se carga el valor inicial (alfa) del ‘contador’
         TMR0H =(18661 >>8); //Primero los bits altos
         TMR0L = (18661);//Despues los bits bajos
         INTCON.PEIE = 1;
         INTCON.GIE = 1;

         while(1);

}
