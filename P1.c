void main() {
     //Variables
     short int x=0;
     
     ADCON1=0x07;
     
     //Configuración terminales de salida
     TRISC = 0; //Terminales de salida
     PORTC = 0;
     

     while(1){
              if(x == 0)
                x = 0x01;

              delay_ms(100);
              PORTC = x;
              delay_ms(200);
              x = x << 1;
     }
}