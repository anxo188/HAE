
short int x;
short int subida = 1;
unsigned short int cont=0;

// Lcd pinout settings
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

void interrupt(){
     char txt[4];
     if(subida == 1){
          cont++;
          subida=0;
          ByteToStr(cont,txt);
          Lcd_out(1,1,txt);
     }
     else{
          subida=1;
     }
     


     x = PORTB;
     INTCON.RBIF=0;
}

void main() {
     //Configuracion de puertos
     TRISB.B4 = 1;

     
     //Inicializacion del controlador del LCD
     Lcd_Init();

     //Configuracion interrupciones
     INTCON2.RBPU=0;
     x = PORTB;
     INTCON.RBIF=0;
     INTCON.RBIE=1;
     INTCON.GIE=1;

     
     while(1);
}